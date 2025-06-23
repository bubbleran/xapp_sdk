#include "../include/src/xApp/e42_xapp_api.h"
#include "../include/src/sm/rc_sm/ie/ir/ran_param_struct.h"
#include "../include/src/sm/rc_sm/ie/ir/ran_param_list.h"
#include "../include/src/util/alg_ds/ds/lock_guard/lock_guard.h"
#include "../include/src/util/alg_ds/ds/latch_cv/latch_cv.h"
#include "../include/src/sm/rc_sm/rc_sm_id.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

static
ue_id_e2sm_t ue_id;

static
latch_cv_t latch;

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
 
  // Assume that the RAN with the UE is the one
  // to perform the handover. It should not be 
  // a data race as only one RAN is supposed to 
  // have UEs
  assert(frmt_4->sz_seq_ue_info > 0 && "No UEs connected");
  ue_id = cp_ue_id_e2sm(&frmt_4->seq_ue_info[0].ue_id);   

  // Syncronize. Notify that one message arrived
  count_down_latch_cv(&latch);
}

static
e2sm_rc_ctrl_hdr_frmt_1_t gen_rc_ctrl_hdr_frmt_1(ue_id_e2sm_t const* ue_id, uint32_t ric_style_type, uint16_t ctrl_act_id)
{
  e2sm_rc_ctrl_hdr_frmt_1_t dst = {0};

  // 6.2.2.6
  dst.ue_id = cp_ue_id_e2sm(ue_id);

  dst.ric_style_type = ric_style_type;
  dst.ctrl_act_id = ctrl_act_id;

  return dst;
}

static
e2sm_rc_ctrl_hdr_t gen_rc_ctrl_hdr(ue_id_e2sm_t const* ue_id, rc_ctrl_service_style_2_act_id_e ctrl_act_id)
{
  e2sm_rc_ctrl_hdr_t dst = {0};

  dst.format = FORMAT_1_E2SM_RC_CTRL_HDR;
  const uint32_t ric_style_type = 10; // Abusing hte standard. 7.6.XXX 
  dst.frmt_1 = gen_rc_ctrl_hdr_frmt_1(ue_id, ric_style_type, ctrl_act_id);

  return dst;
}

static
e2sm_rc_ctrl_msg_frmt_1_t gen_rc_ctrl_msg_frmt_1_mcs(int mcs)
{
//  assert((dl_ul == 1 || dl_ul == 2) && "1 for Downlink, 2 for Uplink");
  assert((mcs > -1 && mcs < 29) && "MCS valid range [0,28]");

  e2sm_rc_ctrl_msg_frmt_1_t dst = {0};

  // 8.4.3.6
  // This is NOT O-RAN compliant code. 
  dst.sz_ran_param = 1;
  dst.ran_param = calloc(1, sizeof(seq_ran_param_t));
  assert(dst.ran_param != NULL && "Memory exhausted");
  dst.ran_param[0].ran_param_id = 1; //ul_dl; // Downlink: 1 , Uplink: 2
  dst.ran_param[0].ran_param_val.type = ELEMENT_KEY_FLAG_FALSE_RAN_PARAMETER_VAL_TYPE;
  dst.ran_param[0].ran_param_val.flag_false = calloc(1, sizeof(ran_parameter_value_t));
  assert(dst.ran_param[0].ran_param_val.flag_false != NULL && "Memory exhausted");
  dst.ran_param[0].ran_param_val.flag_false->type = INTEGER_RAN_PARAMETER_VALUE;
  dst.ran_param[0].ran_param_val.flag_false->int_ran = mcs;

  return dst;
}

static
e2sm_rc_ctrl_msg_t gen_rc_ctrl_msg(int mcs)
{
  //assert((dl_ul == 1 || dl_ul == 2) && "0 for Downlink, 1 for Uplink");
  assert((mcs > -1 && mcs < 29) && "MCS valid range [0,28]");

  e2sm_rc_ctrl_msg_t dst = {0}; 

  dst.format = FORMAT_1_E2SM_RC_CTRL_MSG;
  dst.frmt_1 = gen_rc_ctrl_msg_frmt_1_mcs(mcs);

  return dst;
}

int find_idx_gnb_or_du(e2_node_arr_xapp_t const* arr)
{
  assert(arr != NULL);
  for(size_t i = 0; i < arr->len; ++i){
    global_e2_node_id_t* n = &arr->n[i].id;
    if(n->type == e2ap_ngran_gNB_DU || n->type == e2ap_ngran_gNB){
      return i;
    }
  }
  return -1;
}

int main(int argc, char *argv[])
{
  assert(argc == 4 && "Usage needs the values: [0,1] Downlink/Uplink + MCS e.g., donwlink ./mcs xapp.yaml 0 10");
  //int const dl_ul = atoi(argv[1]);
  //assert((dl_ul == 1 || dl_ul == 2) && "0 for Downlink, 1 for Uplink");
  int const mcs = atoi(argv[2]);
  assert((mcs > -1 && mcs < 29) && "MCS valid range [0,28]");

  //Init the xApp
  init_xapp_api(argv[1]);
  sleep(1);

  e2_node_arr_xapp_t arr = e2_nodes_xapp_api();
  defer({ free_e2_node_arr_xapp(&arr); });
  assert(arr.len > 0);

  printf("Connected E2 nodes = %d\n", arr.len);

  sm_ans_xapp_t hndl = {0};

  // Init latch to syncronize threads
  // Support gNB or DU
  latch = init_latch_cv(1);
  defer({ free_latch_cv(&latch); } );

  // Generate RAN CONTROL Subscription
  rc_sub_data_t rc_sub = on_demand_rc_sub();
  defer({ free_rc_sub_data(&rc_sub); });

  int const idx = find_idx_gnb_or_du(&arr);
  assert(idx > -1 && "Not a gNB or DU found!");

  // Retrieve information about the E2 Nodes in the callback func (cb)
  hndl = report_sm_xapp_api(&arr.n[idx].id, SM_RC_ID, &rc_sub, cb);
  assert(hndl.success == true);

  // Syncronize. Wait until all the previous messages arrive using a latch
  wait_latch_cv(&latch);
  
  rc_ctrl_req_data_t rc_ctrl = {0};
  rc_ctrl.hdr = gen_rc_ctrl_hdr(&ue_id, MCS_value_7_6_3_1);
  rc_ctrl.msg = gen_rc_ctrl_msg(mcs);
  defer({ free_rc_ctrl_req_data(&rc_ctrl); });

  control_sm_xapp_api(&arr.n[idx].id, SM_RC_ID, &rc_ctrl);

  //Stop the xApp
  while(try_stop_xapp_api() == false)
    usleep(1000);

  printf("Test xApp run SUCCESSFULLY\n");

  return 0;
}

