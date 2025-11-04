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
global_e2_node_id_t src_e2_node;

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

  assert(frmt_4->sz_seq_ue_info > 0 && "At least one UE connected needed for this example!");
  // Change this array for getting the SRS from a second UE ID
  ue_id = cp_ue_id_e2sm(&frmt_4->seq_ue_info[0].ue_id);
  if (ue_id.type == GNB_UE_ID_E2SM)
    printf("Control ran_ue_id %ld\n", *ue_id.gnb.ran_ue_id);
  else if (ue_id.type == GNB_DU_UE_ID_E2SM)
    printf("Control ran_ue_id %ld\n", *ue_id.gnb_du.ran_ue_id);
  else
    assert(0 != 0 && "cannot get ran_ue_id from this unknown ue_id.type");

  src_e2_node = cp_global_e2_node_id(n);

  // Syncronize. Notify that one message arrived
  count_down_latch_cv(&latch);
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
  printf("sz_srs_rx_antenna %ld\n", frmt_1->srs.sz_srs_rx_antenna);

  int64_t t1 = time_now_us();
  int64_t t0 = 0;
  memcpy(&t0,frmt_1->slot_tstamp.slot_start_time, 8);
  printf("Latency %ld us\n", t1-t0);
  
  srs_rx_antenna_t const* rx = &frmt_1->srs.rx[0];
  assert(rx->sz_srs_symbols == 1); 
  
  size_t sz = rx->symbol[0].raw_iq.len; 
  uint8_t* buf = rx->symbol[0].raw_iq.buf;
  for(size_t i = 0; i < sz; i +=4){
    int16_t im = *(int16_t*)&buf[i];  
    int16_t re = *(int16_t*)&buf[i+2];  
    (void)im;
    (void)re;
  }
  printf("Message of SRS arrived for RIC Request ID %d AMF UE ID %ld \n", rd->ric_req_id, ue_id.gnb.amf_ue_ngap_id);  
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
    int const nb_id = arr.n[i].id.nb_id.nb_id;

    if (type == e2ap_ngran_gNB_CU) {
      printf("We don't collect SRS signal from E2 Node nb_id %d (type gNB-CU)\n", nb_id);
      continue;
    }

    if (type != e2ap_ngran_gNB && type != e2ap_ngran_gNB_DU)
      assert(0 != 0 && "unsupported E2 node type in this xApp");

    global_e2_node_id_t* target_e2node = &arr.n[i].id;

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

    poll(NULL, 0, 100000);

    rm_report_sm_xapp_api(hndl.u.handle);
  }

  return 0;
}
