#include "../include/src/xApp/e42_xapp_api.h"
#include "../include/src/sm/rc_sm/ie/ir/ran_param_struct.h"
#include "../include/src/util/alg_ds/ds/latch_cv/latch_cv.h"
#include "../include/src/util/alg_ds/alg/defer.h"
#include "../include/src/util/alg_ds/ds/lock_guard/lock_guard.h"
#include "../include/src/sm/rc_sm/rc_sm_id.h"
#include "../include/src/sm/kpm_sm/kpm_sm_id_wrapper.h"

#include <assert.h>
#include <errno.h>
#include <poll.h>
#include <unistd.h>

static
ue_id_e2sm_t ue_id;

static
latch_cv_t latch;

static
uint32_t period_ms_tbl[] = {
  1,
  2,
  5,
  10,
  20,
  50,
  100,
  200,
  500,
  1000,
};

static
char* meas_name_tbl[] = {
    "DRB.PdcpSduVolumeDL",
    "DRB.PdcpSduVolumeUL",
    "DRB.RlcSduDelayDl",
    "DRB.UEThpDl",
    "DRB.UEThpUl",
    "RRU.PrbTotDl",
    "RRU.PrbTotUl",
    "CARR.MUPDSCHMCSDist.BinX", 
};

typedef enum{
  PDCP_SDU_VOLUME_DL,
  PDCP_SDU_VOLUME_UL,
  RLC_SDU_DELAY_DL,
  UE_THP_DL,
  UE_THP_UL,
  PRB_TOT_DL,
  PRB_TOT_UL,
  PDSCH_MCS,

  END_MNTR_VAR_E
} mntr_var_e;

typedef enum {
 PERIODICITY_1_MS,
 PERIODICITY_2_MS,
 PERIODICITY_5_MS,
 PERIODICITY_10_MS,
 PERIODICITY_20_MS,
 PERIODICITY_50_MS,
 PERIODICITY_100_MS,
 PERIODICITY_200_MS,
 PERIODICITY_500_MS,
 PERIODICITY_1000_MS,

 END_PERIODICITY_E,
} periodicity_e ;

////////////
////////////
/// Start KPM Related Code
////////////
////////////

static
kpm_event_trigger_def_t gen_kpm_ev_trig(uint64_t period)
{
  kpm_event_trigger_def_t dst = {0};

  dst.type = FORMAT_1_RIC_EVENT_TRIGGER;
  dst.kpm_ric_event_trigger_format_1.report_period_ms = period;

  return dst;
}

static
meas_info_format_1_lst_t gen_meas_info_format_1(char const* meas_info_name)
{
  meas_info_format_1_lst_t dst = {0};

  dst.meas_type.type = NAME_MEAS_TYPE;
  // ETSI TS 128 552
  dst.meas_type.name = cp_str_to_ba(meas_info_name);

  dst.label_info_lst_len = 1;
  dst.label_info_lst = calloc(1, sizeof(label_info_lst_t));
  assert(dst.label_info_lst != NULL && "Memory exhausted");

  // No Label
  dst.label_info_lst[0].noLabel = calloc(1, sizeof(enum_value_e));
  assert(dst.label_info_lst[0].noLabel != NULL && "Memory exhausted");
  *dst.label_info_lst[0].noLabel = TRUE_ENUM_VALUE;

  return dst;
}

static
kpm_act_def_format_1_t gen_kpm_ad_frmt_1(char const* meas_info_name, uint64_t period_ms)
{
  kpm_act_def_format_1_t dst = {0};

  dst.gran_period_ms = period_ms;

  dst.meas_info_lst_len = 1;
  dst.meas_info_lst = calloc(dst.meas_info_lst_len, sizeof(meas_info_format_1_lst_t));
  assert(dst.meas_info_lst != NULL && "Memory exhausted");
  // Current sdk support 1 measurement info at a time
  dst.meas_info_lst[0] = gen_meas_info_format_1(meas_info_name);

  return dst;
}

static
test_info_lst_t filter_predicate(test_cond_type_e type, test_cond_e cond, uint32_t value)
{
  test_info_lst_t dst = {0};

  dst.test_cond_type = type;
  // It can only be TRUE_TEST_COND_TYPE so it does not matter the type
  // but ugly ugly...
  dst.S_NSSAI = TRUE_TEST_COND_TYPE;

  dst.test_cond = calloc(1, sizeof(test_cond_e));
  assert(dst.test_cond != NULL && "Memory exhausted");
  *dst.test_cond = cond;

  dst.test_cond_value = calloc(1, sizeof(test_cond_value_t));
  assert(dst.test_cond_value != NULL && "Memory exhausted");
  dst.test_cond_value->type = OCTET_STRING_TEST_COND_VALUE;

  dst.test_cond_value->octet_string_value = calloc(1, sizeof(byte_array_t));
  assert(dst.test_cond_value->octet_string_value != NULL && "Memory exhausted");
  const size_t len_nssai = 4;
  dst.test_cond_value->octet_string_value->len = len_nssai;
  dst.test_cond_value->octet_string_value->buf = calloc(len_nssai, sizeof(uint8_t));
  assert(dst.test_cond_value->octet_string_value->buf != NULL && "Memory exhausted");
  memcpy(dst.test_cond_value->octet_string_value->buf, &value, len_nssai);

  return dst;
}

static
kpm_act_def_t gen_kpm_ad_frmt_4(const char* meas_name, uint32_t period_ms)
{
  assert(meas_name != NULL);
  kpm_act_def_t act_def = {.type = FORMAT_4_ACTION_DEFINITION};

  // Fill matching condition
  // [1, 32768]
  act_def.frm_4.matching_cond_lst_len = 1;
  act_def.frm_4.matching_cond_lst = calloc(act_def.frm_4.matching_cond_lst_len, sizeof(matching_condition_format_4_lst_t));
  assert(act_def.frm_4.matching_cond_lst != NULL && "Memory exhausted");
  // Filter connected UEs by S-NSSAI criteria
  test_cond_type_e const type = S_NSSAI_TEST_COND_TYPE; // CQI_TEST_COND_TYPE
  test_cond_e const condition = GREATERTHAN_TEST_COND; // EQUAL_TEST_COND; 
  // 8.3.11 Measurement label snssai
  //  All zeros should not be allowed in 3gpp
  //  or OAI will crash
  //  We just want to get all the UEs...
  uint32_t nssai = 0; // sst and sd
  ((uint8_t*)&nssai)[0] = 0; // sst
  ((uint8_t*)&nssai)[1] = 0; // sd
  ((uint8_t*)&nssai)[2] = 0; // sd
  ((uint8_t*)&nssai)[3] = 0; // sd
  act_def.frm_4.matching_cond_lst[0].test_info_lst = filter_predicate(type, condition, nssai);

  // Fill Action Definition Format 1
  // 8.2.1.2.1
  act_def.frm_4.action_def_format_1 = gen_kpm_ad_frmt_1(meas_name, period_ms);

  return act_def;
}

static
kpm_sub_data_t gen_kpm_sub_ue(mntr_var_e v, periodicity_e p)
{
  assert(v < (int)END_MNTR_VAR_E);
  assert(p < (int)END_PERIODICITY_E);

  kpm_sub_data_t kpm_sub = {0}; 

  uint32_t const period_ms = period_ms_tbl[p];
  // KPM Event Trigger
  kpm_sub.ev_trg_def = gen_kpm_ev_trig(period_ms);

  // KPM Action Definition
  kpm_sub.sz_ad = 1;
  kpm_sub.ad = calloc(1, sizeof(kpm_act_def_t));
  assert(kpm_sub.ad != NULL && "Memory exhausted");

  char const* meas_name = meas_name_tbl[v];
  kpm_sub.ad[0] = gen_kpm_ad_frmt_4(meas_name, period_ms);

  return kpm_sub;
}

////////////
////////////
/// End KPM Related Code
////////////
////////////

////////////
////////////
/// Start RC Related Code
////////////
////////////


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

////////////
////////////
/// End RC Related Code
////////////
////////////

void cb_sm_rc(sm_ag_if_rd_t const *rd, global_e2_node_id_t const *n) 
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
  assert(frmt_4->sz_seq_ue_info > 0 && "No UE connected?"); 
  ue_id = cp_ue_id_e2sm(&frmt_4->seq_ue_info[0].ue_id);   

  // Syncronize. Notify that one message arrived
  count_down_latch_cv(&latch);
}

void cb_kpm_sm(sm_ag_if_rd_t const* rd, global_e2_node_id_t const* e2_node)
{
  assert(rd != NULL);
  assert(e2_node != NULL);
  assert(rd->type == INDICATION_MSG_AGENT_IF_ANS_V0);
  assert(rd->ind.type == KPM_STATS_V3_0);

  // Reading Indication Message Format 3
  kpm_ind_data_t const* ind = &rd->ind.kpm.ind;
  //kpm_ric_ind_hdr_format_1_t const* hdr_frm_1 = &ind->hdr.kpm_ric_ind_hdr_format_1;
  assert(ind->msg.type == FORMAT_3_INDICATION_MESSAGE);
  kpm_ind_msg_format_3_t const* msg_frm_3 = &ind->msg.frm_3;

  size_t const sz_ue = msg_frm_3->ue_meas_report_lst_len;
  assert(sz_ue > 0 && "At least one UE connected needed");
  
  // Reported list of measurements per UE
  kpm_ind_msg_format_1_t const* ind_msg_format_1 = &msg_frm_3->meas_report_per_ue[0].ind_msg_format_1;

  assert(ind_msg_format_1->meas_data_lst_len == 1);
  assert(ind_msg_format_1->meas_data_lst[0].meas_record_len == 1);
  assert(ind_msg_format_1->meas_data_lst[0].meas_record_lst[0].value == INTEGER_MEAS_VALUE);

  int const mcs = ind_msg_format_1->meas_data_lst[0].meas_record_lst[0].int_val;
  assert(mcs > -1 && mcs < 29 && "Invalid MCS Range");
  printf("Measured MCS %d\n", mcs);
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
  assert(argc == 2 && "Configuration file needed");

  //Init the xApp
  init_xapp_api(argv[1]);
  poll(NULL, 0, 1000);

  e2_node_arr_xapp_t nodes = e2_nodes_xapp_api();
  defer({ free_e2_node_arr_xapp(&nodes); });

  latch = init_latch_cv(1);
  defer({ free_latch_cv(&latch); } );

  // Generate RAN CONTROL Subscription
  rc_sub_data_t rc_sub = on_demand_rc_sub();
  defer({ free_rc_sub_data(&rc_sub); });

  int const idx = find_idx_gnb_or_du(&nodes);
  assert(idx > -1 && "Not a gNB or DU found!");

  // Retrieve information about the E2 Nodes in the callback func (cb)
  sm_ans_xapp_t hndl = report_sm_xapp_api(&nodes.n[idx].id, SM_RC_ID, &rc_sub, cb_sm_rc);
  assert(hndl.success == true);

  // Syncronize. Wait until all the previous messages arrive using a latch
  int const timeout_sec = 5; 
  int rc = wait_timeout_latch_cv(&latch, timeout_sec);
  if(rc == ETIMEDOUT){
    puts("Timeout while waiting an answer from a RC Control subscription");
    abort();
  }
  // No need to remove subscription, since it is on_demand! 
  
  periodicity_e const p = PERIODICITY_1000_MS;
  mntr_var_e const v = PDSCH_MCS;

  kpm_sub_data_t kpm_sub = gen_kpm_sub_ue(v, p);
  defer({ free_kpm_sub_data(&kpm_sub); });

  printf("Before  report_sm_xapp_api \n");
  hndl = report_sm_xapp_api(&nodes.n[idx].id, SM_KPM_ID, &kpm_sub, cb_kpm_sm);
  assert(hndl.success == true);

  poll(NULL, 0, 10000);

  rm_report_sm_xapp_api(hndl.u.handle);

  printf("Test run successfully!");

  return 0;
}

