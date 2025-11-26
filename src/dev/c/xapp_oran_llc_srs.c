#include "../include/src/xApp/e42_xapp_api.h"
#include "../include/src/util/alg_ds/alg/defer.h"
#include "../include/src/sm/llc_sm/llc_sm_id.h"
#include "../include/src/util/alg_ds/ds/latch_cv/latch_cv.h"
#include "../include/src/util/time_now_us.h" 
#include "../include/src/sm/rc_sm/rc_sm_id.h"

#include <assert.h>
#include <poll.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

static
ue_id_e2sm_t ue_id;

static
latch_cv_t latch;

static
global_e2_node_id_t src_e2_node = {0};

// Event Trigger 
static
e2sm_rc_event_trigger_t gen_ev_trig(void)
{
  // On Demand trigger. Snapshot. 
  // No need to send a subscription delete afterwards
  e2sm_rc_event_trigger_t dst = {.format = FORMAT_5_E2SM_RC_EV_TRIGGER_FORMAT};
  dst.frmt_5.on_demand = TRUE_ON_DEMAND_FRMT_5;

  return dst;
}

static
e2sm_rc_act_def_frmt_1_t gen_rc_frmt_1(void)
{
  e2sm_rc_act_def_frmt_1_t dst = {0}; 
  
  dst.sz_param_report_def = 1;
  dst.param_report_def = calloc(dst.sz_param_report_def, sizeof(param_report_def_t));
  assert(dst.param_report_def != NULL && "Memory exhausted");
  dst.param_report_def[0].ran_param_id = UE_CTX_INFO_8_2_5;

  return dst;
}

// Action Definition
e2sm_rc_action_def_t gen_act_def(void)
{
  e2sm_rc_action_def_t dst = {0}; 

  //  RIC Style Type
  //  Mandatory
  //  9.3.3
  // Defined in common 6.2.2.2.

  // 5 - On Demand Report
  // This style is used to report snapshot of UE related information and
  // Cell related information upon request from Near-RT RIC.
  dst.ric_style_type = 5; 

  //9.2.1.2.1
  dst.format = FORMAT_1_E2SM_RC_ACT_DEF;
  dst.frmt_1 = gen_rc_frmt_1();

  return dst;
}

// 7.4.6
// REPORT Service Style 5: On Demand Report
static
rc_sub_data_t on_demand_rc_sub(void)
{
  rc_sub_data_t dst = {0}; 

  // Event Trigger
  dst.et = gen_ev_trig();

  // Action Definition
  dst.sz_ad = 1; 
  dst.ad = calloc(dst.sz_ad, sizeof(e2sm_rc_action_def_t));
  assert(dst.ad != NULL && "Memory exhausted");
  dst.ad[0] = gen_act_def();

  return dst;
}

static
void cb(sm_ag_if_rd_t const *rd, global_e2_node_id_t const *n) 
{
  assert(n != NULL);
  assert(rd != NULL);
  assert(rd->type == INDICATION_MSG_AGENT_IF_ANS_V0);
  assert(rd->ind.type == RAN_CTRL_STATS_V1_03);

  rc_ind_data_t const* ind = &rd->ind.rc.ind;

  // Header
  assert(ind->hdr.format == FORMAT_1_E2SM_RC_IND_HDR);
  // Ignoring the Event trigger condition as it is an
  // on demand message

  // Message
  assert(ind->msg.format == FORMAT_4_E2SM_RC_IND_MSG);
  e2sm_rc_ind_msg_frmt_4_t const* frmt_4 = &ind->msg.frmt_4; // 9.2.1.4.4

  //assert(frmt_4->sz_seq_ue_info > 0 && "At least one UE connected needed for this example!");
  if (frmt_4->sz_seq_ue_info <= 0) {
    printf("No UE connected to E2 Node id %d\n", n->nb_id.nb_id);
    return;
  }

  for (size_t i = 0; i < frmt_4->sz_seq_ue_info; i++) {
    ue_id = cp_ue_id_e2sm(&frmt_4->seq_ue_info[i].ue_id);
    if (ue_id.type == GNB_UE_ID_E2SM)
      printf("Found UE(%lu) ran_ue_id %ld in E2 Node (gNB) id %d\n", i, *frmt_4->seq_ue_info[i].ue_id.gnb.ran_ue_id, n->nb_id.nb_id);
    else if (ue_id.type == GNB_DU_UE_ID_E2SM)
      printf("Found UE(%lu) ran_ue_id %ld in E2 Node (gNB-DU) id %d\n", i, *frmt_4->seq_ue_info[i].ue_id.gnb_du.ran_ue_id, n->nb_id.nb_id);
    else
      assert(0 != 0 && "cannot get ran_ue_id from this unknown ue_id.type");
  }
  // Change this array for getting the SRS from a second UE ID
//  ue_id = cp_ue_id_e2sm(&frmt_4->seq_ue_info[0].ue_id);
  if (ue_id.type == GNB_UE_ID_E2SM)
    printf("Monitor ran_ue_id %ld\n", *ue_id.gnb.ran_ue_id);
  else if (ue_id.type == GNB_DU_UE_ID_E2SM)
    printf("Monitor ran_ue_id %ld\n", *ue_id.gnb_du.ran_ue_id);
  else
    assert(0 != 0 && "cannot get ran_ue_id from this unknown ue_id.type");

  src_e2_node = cp_global_e2_node_id(n);

  // Syncronize. Notify that one message arrived
  count_down_latch_cv(&latch);
}

//void write_iq_to_file(const char* filename, const uint8_t* buf, size_t len) {
//  FILE* f = fopen(filename, "wb");
//  if (!f) {
//    perror("fopen");
//    return;
//  }
//  fwrite(buf, 1, len, f);   // write raw bytes
//  fclose(f);
//}

void write_iq_text(const char* filename, const uint8_t* buf, size_t len, int64_t collect_time) {
  FILE* f = fopen(filename, "w");
  if (!f) return;

  // buf = [I_l, I_h, Q_l, Q_h]
  for (size_t i = 0; i < len; i++) {
    size_t o = 4 * i; // offset into buf
    int16_t I = buf[o] | (buf[o+1] << 8);
    int16_t Q = buf[o+2] | (buf[o+3] << 8);
    //printf("%zd: I=%d, Q=%d\n", i, I, Q);
    fprintf(f, "%ld %d %d\n", collect_time, I, Q);
  }

  fclose(f);
}

static void cb_sm_llc(sm_ag_if_rd_t const *rd, global_e2_node_id_t const *n) 
{
  assert(n != NULL);
  assert(rd != NULL);
  assert(rd->type == INDICATION_MSG_AGENT_IF_ANS_V0);
  assert(rd->ind.type == LLC_STATS_V1_0);

  llc_ind_data_t const* ind = &rd->ind.llc.ind;

  assert(ind->msg.format == FORMAT_1_E2SM_LLC_IND_MSG && "Only Aperiodic event supported");
  e2sm_llc_ind_msg_frmt_1_t const* frmt_1 = &ind->msg.frmt_1;
  assert(frmt_1->ll_info_type == SRS_LL_INFO_TYPE_E && "srs samples expected");


  int64_t t0 = 0;
  memcpy(&t0,frmt_1->slot_tstamp.slot_start_time, 8);
  printf("receive ind msg from gnb-du id %u, msg latency %lu us\n", n->nb_id.nb_id, time_now_us() - t0);

  for(size_t i = 0; i < frmt_1->srs.sz_srs_rx_antenna; i++) {
    srs_rx_antenna_t* rx = &frmt_1->srs.rx[i];
    for (size_t j = 0; j < rx->sz_srs_symbols; j++) {
      srs_symbol_t* symbol = &rx->symbol[j];
      byte_array_t raw_iq = symbol->raw_iq;
      // for (size_t i = 0; i < raw_iq.len; i++) {
      //   size_t o = 4 * i; // offset into buf
      //   int16_t I = raw_iq.buf[o] | (raw_iq.buf[o+1] << 8);
      //   int16_t Q = raw_iq.buf[o+2] | (raw_iq.buf[o+3] << 8);
      //   //printf("%zd: I=%d, Q=%d\n", i, I, Q);
      //   //printf("%d %d\n", I, Q);
      // }
      size_t sz = raw_iq.len / 3 / 4; // rx, noise, estimated // sizeof(c16_t) = 4
      // Offsets in bytes
      size_t rx_offset     = 0;
      size_t noise_offset  = 4 * sz;
      size_t est_offset    = 4 * sz * 2;

      char filename_rx[256], filename_noise[256], filename_estimated[256];
      snprintf(filename_rx, sizeof(filename_rx),
               "iq_srs_rx_ant%lu_symbol%lu_nbid%u.txt", i, j, n->nb_id.nb_id);
      write_iq_text(filename_rx, raw_iq.buf + rx_offset, sz, t0);

      snprintf(filename_noise, sizeof(filename_noise),
               "iq_srs_noise_ant%lu_symbol%lu_nbid%u.txt", i, j, n->nb_id.nb_id);
      write_iq_text(filename_noise, raw_iq.buf + noise_offset, sz, t0);

      snprintf(filename_estimated, sizeof(filename_estimated),
               "iq_srs_estimated_ant%lu_symbol%lu_nbid%u.txt", i, j, n->nb_id.nb_id);
      write_iq_text(filename_estimated, raw_iq.buf + est_offset, sz, t0);
//      printf("sz_srs_rx_antenna %lu, rx %lu, sz_srs_symbols %lu, symbol %lu\n",
//             frmt_1->srs.sz_srs_rx_antenna,
//             i,
//             rx->sz_srs_symbols,
//             j);
    }

  }
}

static 
llc_sub_data_t gen_llc_sub(ue_id_e2sm_t* ue_id)
{
  assert(ue_id != NULL);

  llc_sub_data_t dst = {0};

  // Aperiodic event
  dst.et.format = FORMAT_1_E2SM_LLC_EV_TRIGGER_FORMAT;
  // List of LLI for Event Trigger
  // [1,63]
  dst.et.frmt_1.sz_lst_lli_ev_trg = 1; 
  dst.et.frmt_1.lst_lli_ev_trg = calloc(dst.et.frmt_1.sz_lst_lli_ev_trg, sizeof(lst_lli_ev_trg_t));
  assert(dst.et.frmt_1.lst_lli_ev_trg != NULL && "Memory exhausted");

  // For each message event configured, Event Trigger Condition ID 
  // is assigned so that E2 Node can reply to Near-RT RIC in the 
  // RIC INDICATION message to inform which event(s) are the cause for triggering.
  // O-RAN E2SM-LLC pag. 11
  dst.et.frmt_1.lst_lli_ev_trg[0].ev_trg_cond_id = 1; 
  dst.et.frmt_1.lst_lli_ev_trg[0].lower_layer_info = SRS_LOWER_LAYER_INFO_E; 

  dst.et.frmt_1.ev_trg_ue_info = calloc(1, sizeof(ev_trg_ue_info_t));
  assert(dst.et.frmt_1.ev_trg_ue_info != NULL && "Memory exhausted");


  // subscribe to specifc UE
  dst.et.frmt_1.ev_trg_ue_info->sz_assoc_ue_info = 1;
  dst.et.frmt_1.ev_trg_ue_info->assoc_ue_info = calloc(1, sizeof(assoc_ue_info_llc_t));
  assert(dst.et.frmt_1.ev_trg_ue_info->assoc_ue_info != NULL && "Memory exhausted" );
  dst.et.frmt_1.ev_trg_ue_info->assoc_ue_info[0].ev_trg_id_ue = 1; 
  dst.et.frmt_1.ev_trg_ue_info->assoc_ue_info[0].ue_type = INDIVIDUAL_UE_UE_TYPE_E;
  dst.et.frmt_1.ev_trg_ue_info->assoc_ue_info[0].ue = cp_ue_id_e2sm(ue_id);
 
  // [1-16]
  dst.sz_ad = 1;
  dst.ad = calloc(dst.sz_ad, sizeof(e2sm_llc_action_def_t)); 
  assert(dst.ad != NULL && "Memory exhausted");

  // RIC Style Type Style Name Style Description
  // 1-LLI copy: This style is used to report a copy of LLI received from UE.
  // 2-Periodic: This style is used to report the lower layers measurements collected
  //by the E2 Node
  dst.ad[0].ric_style_type = 1;
  dst.ad[0].format = FORMAT_1_E2SM_LLC_ACT_DEF; 
  dst.ad[0].frmt_1.lower_layer_info = SRS_LOWER_LAYER_INFO_E;

  return dst;
}

int main(int argc, char *argv[])
{
  assert(argc == 2 && "Configuration file needed");

  //Init the xApp
  init_xapp_api(argv[1]);
  poll(NULL, 0, 1000);

  e2_node_arr_xapp_t arr = e2_nodes_xapp_api();
  defer({ free_e2_node_arr_xapp(&arr); });


  for (size_t i = 0; i < arr.len; i++) {
    e2ap_ngran_node_t const type = arr.n[i].id.type;
    uint32_t const nb_id = arr.n[i].id.nb_id.nb_id;

    if (type == e2ap_ngran_gNB_CU) {
      printf("We don't collect SRS signal from E2 Node nb_id %d (type gNB-CU)\n", nb_id);
      continue;
    }

    if (type != e2ap_ngran_gNB && type != e2ap_ngran_gNB_DU)
      assert(0 != 0 && "unsupported E2 node type in this xApp");

    // WARNING: This xAPP ONLY can support subscription to one E2 node which connects to at least one UE
    global_e2_node_id_t* target_e2node = &arr.n[i].id;
    printf("Send RC and LLC subscriptions to target_nb_id %d\n", target_e2node->nb_id.nb_id);

    // Init latch to syncronize threads
    latch = init_latch_cv(1);
    defer({ free_latch_cv(&latch); } );

    // Generate RAN CONTROL Subscription
    rc_sub_data_t rc_sub = on_demand_rc_sub();
    defer({ free_rc_sub_data(&rc_sub); });

    // Retrieve information about the E2 Nodes in the callback func (cb)
    sm_ans_xapp_t hndl = report_sm_xapp_api(target_e2node, SM_RC_ID, &rc_sub, cb);
    assert(hndl.success == true);

    // Syncronize. Wait until all the previous messages arrive using a latch
    wait_latch_cv(&latch);

    llc_sub_data_t llc_sub = gen_llc_sub(&ue_id);

    // Retrieve information about the E2 Nodes in the callback func (cb)
    hndl = report_sm_xapp_api(target_e2node, SM_LLC_ID, &llc_sub, cb_sm_llc);
    assert(hndl.success == true);

    // sleep for 180 seconds
    sleep(180);

    rm_report_sm_xapp_api(hndl.u.handle);
    break;
  }

  return 0;
}
