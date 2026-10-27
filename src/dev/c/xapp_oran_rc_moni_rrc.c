#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <poll.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "../include/src/xApp/e42_xapp_api.h"
#include "../include/src/util/alg_ds/alg/defer.h"
#include "../include/src/util/conf/xapp_sub_oran_sm_conf.h"
#include "../include/src/sm/rc_sm/rc_sm_id.h"

static
int64_t time_now_us(void)
{
  struct timespec tms;

  if (clock_gettime(CLOCK_REALTIME,&tms)) {
    return -1;
  }
  /* seconds, multiplied with 1 million */
  int64_t micros = tms.tv_sec * 1000000;
  /* Add full microseconds */
  micros += tms.tv_nsec/1000;
  /* round up if necessary */
  if (tms.tv_nsec % 1000 >= 500) {
    ++micros;
  }
  return micros;
}

// 9.3.35
static 
rrc_msg_id_t gen_rrc_msg(nr_rrc_class_e type)
{
  assert(type == UL_DCCH_NR_RRC_CLASS || type == DL_DCCH_NR_RRC_CLASS );
  rrc_msg_id_t dst = {.type = NR_RRC_MESSAGE_ID};
  dst.nr = type;
  // I don't like this number...
  dst.rrc_msg_id = 0;

  return dst;
}

static
msg_ev_trg_t gen_msg_ev_trg(nr_rrc_class_e type)
{
  msg_ev_trg_t dst = {0};

  // Event trigger condition ID is an identifier for identifying the Indication message
  // sent back from the E2 Node to the RIC
  dst.ev_trigger_cond_id = type + 512;
  dst.msg_type = RRC_MSG_MSG_TYPE_EV_TRG;
  dst.rrc_msg = gen_rrc_msg(type);

  return dst;
}

static
e2sm_rc_ev_trg_frmt_1_t gen_event_trigger_frmt_1(nr_rrc_class_e type)
{
  e2sm_rc_ev_trg_frmt_1_t dst = {0}; 

  // [1 - 65535]
  dst.sz_msg_ev_trg = 1;
  dst.msg_ev_trg = calloc(1, sizeof(msg_ev_trg_t));
  assert(dst.msg_ev_trg != NULL && "Memory exhausted");

  *dst.msg_ev_trg = gen_msg_ev_trg(type);

  return dst;
}

static
e2sm_rc_event_trigger_t gen_event_trigger(nr_rrc_class_e type) 
{
  e2sm_rc_event_trigger_t dst = {.format = FORMAT_1_E2SM_RC_EV_TRIGGER_FORMAT};
  dst.frmt_1 = gen_event_trigger_frmt_1(type);

  return dst;
}


static
param_report_def_t gen_param_report_def(void)
{
  param_report_def_t dst = {0};

  //8.2.1 RAN Parameters for Report Service Style 1
  // RRC Message = 3
  dst.ran_param_id = E2SM_RC_RS1_RRC_MESSAGE;

  return dst;
}

static
e2sm_rc_act_def_frmt_1_t gen_e2sm_rc_act_def_frmt_1(void)
{
  e2sm_rc_act_def_frmt_1_t dst = {0};

  // Parameters to be Reported List
  // [1-65535]
  dst.sz_param_report_def = 1; 
  dst.param_report_def = calloc(1, sizeof(param_report_def_t));
  assert(dst.param_report_def != NULL && "Memory exhausted");

  *dst.param_report_def = gen_param_report_def();

  return dst;
}

static
e2sm_rc_action_def_t gen_e2sm_rc_action_def(void)
{
  e2sm_rc_action_def_t dst = {.ric_style_type = 1};
  
  dst.format = FORMAT_1_E2SM_RC_ACT_DEF;
  dst.frmt_1 = gen_e2sm_rc_act_def_frmt_1();

  return dst;
}

static
rc_sub_data_t gen_rc_sub(nr_rrc_class_e type)
{
  rc_sub_data_t dst = {0};

  e2sm_rc_event_trigger_t et = gen_event_trigger(type); 
  dst.et = et; 
  // [1-16]
  dst.sz_ad = 1;
  dst.ad = calloc(1, sizeof(e2sm_rc_action_def_t)); 
  assert(dst.ad != NULL && "Memory exhausted");
  
  *dst.ad = gen_e2sm_rc_action_def();

  return dst;
}

static
void fn_cb_ul_dcch(sm_ag_if_rd_t const* rd, global_e2_node_id_t const* e2_node)
{
  assert(rd != NULL);
  assert(rd->type == INDICATION_MSG_AGENT_IF_ANS_V0);
  assert(rd->ind.type == RAN_CTRL_STATS_V1_03);
  assert(e2_node != NULL);
  (void)e2_node; 

  rc_rd_ind_data_t const* rc = &rd->ind.rc;

  int64_t const now = time_now_us();
  printf("Message arrived at %ld\n", now);

  rc_ind_data_t const* ind = &rc->ind;
  assert(ind->hdr.format == FORMAT_1_E2SM_RC_IND_HDR);
  //e2sm_rc_ind_hdr_frmt_1_t const* frmt_1 = &ind->hdr.frmt_1;

  assert(ind->msg.format == FORMAT_1_E2SM_RC_IND_MSG);
  e2sm_rc_ind_msg_frmt_1_t const* frmt_1 = &ind->msg.frmt_1; // 9.2.1.4.1
  assert(frmt_1-> sz_seq_ran_param == 1);
  seq_ran_param_t const* seq_ran_param = &frmt_1->seq_ran_param[0];
  assert(seq_ran_param->ran_param_val.type == ELEMENT_KEY_FLAG_FALSE_RAN_PARAMETER_VAL_TYPE);
  ran_parameter_value_t* flag_false = seq_ran_param->ran_param_val.flag_false;
  assert(flag_false->type == OCTET_STRING_RAN_PARAMETER_VALUE);
  byte_array_t ba = flag_false->octet_str_ran;

  json_xapp_api_t json = asn_to_json_xapp_api(SM_RC_ID, NR_RRC_UL_DCCH_RC_SM_ASN_TO_JSON_E, ba.buf, ba.len);

  printf("UL DCCH:\n %s \n", json.buf);

  free(json.buf);
}

static
void fn_cb_dl_dcch(sm_ag_if_rd_t const* rd, global_e2_node_id_t const* e2_node)
{
  assert(rd != NULL);
  assert(rd->type == INDICATION_MSG_AGENT_IF_ANS_V0);
  assert(rd->ind.type == RAN_CTRL_STATS_V1_03);
  assert(e2_node != NULL);
  (void)e2_node; 

  rc_rd_ind_data_t const* rc = &rd->ind.rc;

  int64_t const now = time_now_us();
  printf("Message arrived at %ld\n", now);

  rc_ind_data_t const* ind = &rc->ind;
  assert(ind->hdr.format == FORMAT_1_E2SM_RC_IND_HDR);
  //e2sm_rc_ind_hdr_frmt_1_t const* frmt_1 = &ind->hdr.frmt_1;

  assert(ind->msg.format == FORMAT_1_E2SM_RC_IND_MSG);
  e2sm_rc_ind_msg_frmt_1_t const* frmt_1 = &ind->msg.frmt_1; // 9.2.1.4.1
  assert(frmt_1-> sz_seq_ran_param == 1);
  seq_ran_param_t const* seq_ran_param = &frmt_1->seq_ran_param[0];
  assert(seq_ran_param->ran_param_val.type == ELEMENT_KEY_FLAG_FALSE_RAN_PARAMETER_VAL_TYPE);
  ran_parameter_value_t* flag_false = seq_ran_param->ran_param_val.flag_false;
  assert(flag_false->type == OCTET_STRING_RAN_PARAMETER_VALUE);
  byte_array_t ba = flag_false->octet_str_ran;

  for(size_t i = 0; i < ba.len; ++i){
    printf("%x ", ba.buf[i]);
  }
  fflush(stdout);

  json_xapp_api_t json = asn_to_json_xapp_api(SM_RC_ID, NR_RRC_DL_DCCH_RC_SM_ASN_TO_JSON_E, ba.buf, ba.len);

  printf("DL DCCH:\n %s \n", json.buf);

  free(json.buf);
}

static
int find_arr_idx(e2_node_arr_xapp_t const* arr)
{
  for(size_t i = 0; i < arr->len; ++i){
    e2ap_ngran_node_t type = arr->n[i].id.type;
    if(type == e2ap_ngran_gNB || type == e2ap_ngran_gNB_CU){
      return i;
    }
  }
  assert(0!=0 && "Not a capable E2 node for RRC detected i.e., gNG or CU (Note: This example xApp only works for one E2 node.)");
  return -1;
}

int main(int argc, char *argv[])
{
  assert(argc == 2 && "Configuraiton file needed!");
  (void)argc;

  //Init the xApp
  init_xapp_api(argv[1]);

  poll(NULL, 0, 1000);

  e2_node_arr_xapp_t arr = e2_nodes_xapp_api();
  defer{ free_e2_node_arr_xapp(&arr); };

  assert(arr.len > 0 && "No E2 Node detected!");

  printf("Connected E2 nodes = %d\n", arr.len);

  int idx_arr = find_arr_idx(&arr);

  // Generate RAN CONTROL Subscription
  rc_sub_data_t ul_dcch_rc_sub = gen_rc_sub(UL_DCCH_NR_RRC_CLASS);
  defer{ free_rc_sub_data(&ul_dcch_rc_sub); };

  sm_ans_xapp_t hndl_ul_dcch = report_sm_xapp_api(&arr.n[idx_arr].id, SM_RC_ID, &ul_dcch_rc_sub, fn_cb_ul_dcch);
  assert(hndl_ul_dcch.success == true);
  defer{ rm_report_sm_xapp_api(hndl_ul_dcch.u.handle); };

  // Generate RAN CONTROL Subscription
  rc_sub_data_t dl_dcch_rc_sub = gen_rc_sub(DL_DCCH_NR_RRC_CLASS);
  defer{ free_rc_sub_data(&dl_dcch_rc_sub); };

  sm_ans_xapp_t hndl_dl_dcch = report_sm_xapp_api(&arr.n[idx_arr].id, SM_RC_ID, &dl_dcch_rc_sub, fn_cb_dl_dcch);
  assert(hndl_dl_dcch.success == true);
  defer{ rm_report_sm_xapp_api(hndl_dl_dcch.u.handle); };

  // Rune for 10 sec
  sleep(10);

  printf("Test xApp run SUCCESSFULLY\n");
  return EXIT_SUCCESS;
}

