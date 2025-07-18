/*
 * Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The OpenAirInterface Software Alliance licenses this file to You under
 * the OAI Public License, Version 1.1  (the "License"); you may not use this file
 * except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.openairinterface.org/?page_id=698
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------------------
 * For more information about the OpenAirInterface (OAI) Software Alliance:
 *      contact@openairinterface.org
 */

#include "../include/src/xApp/e42_xapp_api.h"
#include "../include/src/util/alg_ds/alg/defer.h"
#include "../include/src/util/e2ap_ngran_types.h"
#include "../include/src/util/alg_ds/ds/lock_guard/lock_guard.h"
#include "../include/src/sm/kpm_sm/kpm_sm_id_wrapper.h"
#include "../include/src/sm/rc_sm/rc_sm_id.h"
#include "../include/src/sm/rc_sm/ie/rc_data_ie.h"
#include "../include/src/util/conf/xapp_sub_oran_sm_conf.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
//#include <signal.h>
#include <pthread.h>

static
pthread_mutex_t mtx;

////////////
// Get RC Indication Messages -> begin
////////////

int32_t const RC_SM_RRC_CONNECTED = 0;
int32_t const RC_SM_RRC_INACTIVE = 1;
int32_t const RC_SM_RRC_IDLE = 2;
int32_t const RC_SM_RRC_ANY = 3;
const char* str_rrc_state[] = {
  "RC_SM_RRC_CONNECTED",
  "RC_SM_RRC_INACTIVE", 
  "RC_SM_RRC_IDLE", 
  "RC_SM_RRC_ANY",
};

static void sm_cb_rc(sm_ag_if_rd_t const *rd, global_e2_node_id_t const* e2_node)
{
  assert(rd != NULL);
  assert(rd->type == INDICATION_MSG_AGENT_IF_ANS_V0);
  assert(rd->ind.type == RAN_CTRL_STATS_V1_03);
  (void)e2_node;

  // Reading Indication Message Format 2
  e2sm_rc_ind_msg_frmt_2_t const *msg_frm_2 = &rd->ind.rc.ind.msg.frmt_2;

  printf("RC REPORT Style 2 - Call Process Outcome\n");

  // Sequence of UE Identifier
  //[1-65535]
  for (size_t i = 0; i < msg_frm_2->sz_seq_ue_id; i++) {
    // UE ID
    // Mandatory
    // 9.3.10
    switch (msg_frm_2->seq_ue_id[i].ue_id.type) {
      case GNB_UE_ID_E2SM: {
          const uint32_t RRC_STATE_CHANGED_TO_E2SM_RC_RAN_PARAM_ID = 202; 
          const uint32_t ran_param_id = msg_frm_2->seq_ue_id[i].seq_ran_param[0].ran_param_id; 
          if(ran_param_id == RRC_STATE_CHANGED_TO_E2SM_RC_RAN_PARAM_ID){
            const int32_t rrc_state = msg_frm_2->seq_ue_id[i].seq_ran_param[0].ran_param_val.flag_false->int_ran;           
            assert(rrc_state == RC_SM_RRC_CONNECTED || rrc_state == RC_SM_RRC_INACTIVE 
              || rrc_state == RC_SM_RRC_IDLE || rrc_state == RC_SM_RRC_ANY);

          printf("gNB UE with amf_ue_ngap_id = %lu %s\n", msg_frm_2->seq_ue_id[i].ue_id.gnb.amf_ue_ngap_id, str_rrc_state[rrc_state]);
          } else {
            printf("Only RRC status changed supported by now, but ran_param_id %d received!\n", ran_param_id);
          }
        break;
      }
      default:
        printf("Not yet implemented UE ID type\n");
    }
  }
}

////////////
// Get RC Indication Messages -> end
////////////

static
void sm_cb_kpm(sm_ag_if_rd_t const* rd, global_e2_node_id_t const* e2_node)
{
  assert(rd != NULL);
  assert(rd->type == INDICATION_MSG_AGENT_IF_ANS_V0);
  assert(rd->ind.type == KPM_STATS_V3_0);

  kpm_ind_data_t const* kpm = &rd->ind.kpm.ind;
  kpm_ric_ind_hdr_format_1_t const* hdr_frm_1 = &kpm->hdr.kpm_ric_ind_hdr_format_1;

  int64_t now = time_now_us_xapp_api();

  {
    lock_guard(&mtx);

#if defined(KPM_V2_01) || defined (KPM_V2_03)
    // collectStartTime (32bit) unit is second
    printf("KPM-v2 ind_msg latency > %ld s (minimum time unit is in second) from E2-node type %d ID %d\n",
           now/1000000 - hdr_frm_1->collectStartTime,
           e2_node->type, e2_node->nb_id.nb_id);
#elif defined(KPM_V3_00)
    // collectStartTime (64bit) unit is micro-second
    printf("KPM-v3 ind_msg latency = %ld μs from E2-node type %d ID %d\n",
           now - hdr_frm_1->collectStartTime,
           e2_node->type, e2_node->nb_id.nb_id);
#else
    static_assert(0!=0, "Unknown KPM version");
#endif

    if (kpm->msg.type == FORMAT_1_INDICATION_MESSAGE) {
      kpm_ind_msg_format_1_t const* msg_frm_1 = &kpm->msg.frm_1;
      for (size_t i = 0; i < msg_frm_1->meas_data_lst_len; i++) {
        for (size_t j = 0; j < msg_frm_1->meas_data_lst[i].meas_record_len; j++) {
          if (msg_frm_1->meas_data_lst[i].meas_record_lst[j].value == INTEGER_MEAS_VALUE)
            printf("meas record INTEGER_MEAS_VALUE value %d\n",msg_frm_1->meas_data_lst[i].meas_record_lst[j].int_val);
          else if (msg_frm_1->meas_data_lst[i].meas_record_lst[j].value == REAL_MEAS_VALUE)
            printf("meas record REAL_MEAS_VALUE value %f\n", msg_frm_1->meas_data_lst[i].meas_record_lst[j].real_val);
          else
            printf("meas record NO_VALUE_MEAS_VALUE value\n");
        }
      }
    } else if (kpm->msg.type == FORMAT_3_INDICATION_MESSAGE) {
      kpm_ind_msg_format_3_t const* msg_frm_3 = &kpm->msg.frm_3;
      // Reported list of measurements per UE
      for (size_t i = 0; i < msg_frm_3->ue_meas_report_lst_len; i++) {
        switch (msg_frm_3->meas_report_per_ue[i].ue_meas_report_lst.type)
        {
          case GNB_UE_ID_E2SM:
            if (msg_frm_3->meas_report_per_ue[i].ue_meas_report_lst.gnb.gnb_cu_ue_f1ap_lst != NULL) {
              for (size_t j = 0; j < msg_frm_3->meas_report_per_ue[i].ue_meas_report_lst.gnb.gnb_cu_ue_f1ap_lst_len; j++)
                printf("UE ID type = gNB-CU, gnb_cu_ue_f1ap = %u\n", msg_frm_3->meas_report_per_ue[i].ue_meas_report_lst.gnb.gnb_cu_ue_f1ap_lst[j]);
            } else {
              printf("UE ID type = gNB, amf_ue_ngap_id = %lu\n", msg_frm_3->meas_report_per_ue[i].ue_meas_report_lst.gnb.amf_ue_ngap_id);
            }
            break;

          case GNB_DU_UE_ID_E2SM:
            printf("UE ID type = gNB-DU, gnb_cu_ue_f1ap = %u\n", msg_frm_3->meas_report_per_ue[i].ue_meas_report_lst.gnb_du.gnb_cu_ue_f1ap);
            break;
          case GNB_CU_UP_UE_ID_E2SM:
            printf("UE ID type = gNB-CU, gnb_cu_cp_ue_e1ap = %u\n", msg_frm_3->meas_report_per_ue[i].ue_meas_report_lst.gnb_cu_up.gnb_cu_cp_ue_e1ap);
            break;

          default:
            assert(false && "UE ID type not yet implemented");
        }

        kpm_ind_msg_format_1_t const* msg_frm_1 = &msg_frm_3->meas_report_per_ue[i].ind_msg_format_1;

        // UE Measurements per granularity period
        for (size_t j = 0; j<msg_frm_1->meas_data_lst_len; j++) {
          for (size_t z = 0; z<msg_frm_1->meas_data_lst[j].meas_record_len; z++) {
            if (msg_frm_1->meas_info_lst_len > 0) {
              switch (msg_frm_1->meas_info_lst[z].meas_type.type) {
                case NAME_MEAS_TYPE:
                {
                  // Get the Measurement Name
                  char meas_info_name_str[msg_frm_1->meas_info_lst[z].meas_type.name.len + 1];
                  memcpy(meas_info_name_str, msg_frm_1->meas_info_lst[z].meas_type.name.buf, msg_frm_1->meas_info_lst[z].meas_type.name.len);
                  meas_info_name_str[msg_frm_1->meas_info_lst[z].meas_type.name.len] = '\0';

                  // Get the value of the Measurement
                  switch (msg_frm_1->meas_data_lst[j].meas_record_lst[z].value)
                  {
                    case REAL_MEAS_VALUE:
                      printf("%s = %.2f\n", meas_info_name_str, msg_frm_1->meas_data_lst[j].meas_record_lst[z].real_val);
                      break;

                    case INTEGER_MEAS_VALUE:
                      printf("%s = %d\n", meas_info_name_str, msg_frm_1->meas_data_lst[j].meas_record_lst[z].int_val);
                      break;

                    default:
                      assert("Value not recognized");
                  }
                  break;
                }

                default:
                  assert(false && "Measurement Type not yet implemented");
              }
            }


            if (msg_frm_1->meas_data_lst[j].incomplete_flag && *msg_frm_1->meas_data_lst[j].incomplete_flag == TRUE_ENUM_VALUE)
              printf("Measurement Record not reliable\n");
          }
        }
      }
    } else {
      printf("unknown kpm ind format\n");
    }

  }
}

static e2sm_rc_ev_trg_frmt_2_t gen_rc_ev_trig_frm_2(void)
{
  e2sm_rc_ev_trg_frmt_2_t ev_trigger = {0};

  //  Call Process Type ID
  //  Mandatory
  //  9.3.15
  ev_trigger.call_proc_type_id = 3; // Mobility Management

  // Call Breakpoint ID
  // Mandatory
  // 9.3.49
  ev_trigger.call_break_id = 1; // Handover Preparation

  // Associated E2 Node Info
  // Optional
  // 9.3.29
  ev_trigger.assoc_e2_node_info = NULL;

  // Associated UE Info
  // Optional
  // 9.3.26
  ev_trigger.assoc_ue_info = NULL;

  return ev_trigger;
}

static
e2sm_rc_event_trigger_t gen_rc_ev_trig(e2sm_rc_ev_trigger_format_e act_frm)
{
  assert(act_frm == FORMAT_2_E2SM_RC_EV_TRIGGER_FORMAT && "Not supported format");

  e2sm_rc_event_trigger_t dst = {0};

  dst.format = FORMAT_2_E2SM_RC_EV_TRIGGER_FORMAT;
  dst.frmt_2 = gen_rc_ev_trig_frm_2();

  return dst;
}

static
kpm_event_trigger_def_t gen_kpm_ev_trig(uint64_t period)
{
  kpm_event_trigger_def_t dst = {0};

  dst.type = FORMAT_1_RIC_EVENT_TRIGGER;
  dst.kpm_ric_event_trigger_format_1.report_period_ms = period;

  return dst;
}

static
meas_info_format_1_lst_t gen_meas_info_format_1_lst(act_name_id_t const* act)
{
  meas_info_format_1_lst_t dst = {0};

  // use id
  if (act->type == INT32_ACT_NAME_ID_E) {
    dst.meas_type.type = ID_MEAS_TYPE;
    dst.meas_type.id = act->id;
  } else if(act->type == STRING_ACT_NAME_ID_E) { // use name
    dst.meas_type.type = NAME_MEAS_TYPE;
    // ETSI TS 128 552
    dst.meas_type.name = cp_str_to_ba(act->name);
  } else {
    assert(0!=0 && "Unknown action type");
  }

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
kpm_act_def_format_1_t gen_kpm_act_def_frmt_1(elm_oran_sm_conf_t const* elm , uint32_t period_ms)
{
  kpm_act_def_format_1_t dst = {0};

  dst.gran_period_ms = period_ms;

  dst.meas_info_lst_len = elm->sz_act;
  dst.meas_info_lst = calloc(dst.meas_info_lst_len, sizeof(meas_info_format_1_lst_t));
  assert(dst.meas_info_lst != NULL && "Memory exhausted");

  for(size_t i = 0; i < dst.meas_info_lst_len; i++) {
    dst.meas_info_lst[i] = gen_meas_info_format_1_lst(&elm->actions[i]);
  }

  return dst;
}

static
test_info_lst_t filter_predicate(test_cond_type_e type, test_cond_e cond, const int value[])
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
  dst.test_cond_value->octet_string_value->buf[0] = value[0];
  dst.test_cond_value->octet_string_value->buf[1] = value[1];
  dst.test_cond_value->octet_string_value->buf[2] = value[2];
  dst.test_cond_value->octet_string_value->buf[3] = value[3];

  return dst;
}

static
kpm_act_def_format_4_t gen_kpm_act_def_frmt_4(elm_oran_sm_conf_t const* elm, uint32_t period_ms)
{
  kpm_act_def_format_4_t dst = {0};

  // [1, 32768]
  dst.matching_cond_lst_len = 1;

  dst.matching_cond_lst = calloc(dst.matching_cond_lst_len, sizeof(matching_condition_format_4_lst_t));
  assert(dst.matching_cond_lst != NULL && "Memory exhausted");
  test_info_lst_t* test_info_lst = &dst.matching_cond_lst[0].test_info_lst;

  // Filter connected UEs by S-NSSAI criteria
  test_cond_type_e const type = S_NSSAI_TEST_COND_TYPE;
  test_cond_e const condition = GREATERTHAN_TEST_COND; // EQUAL_TEST_COND
  // 8.3.11 Measurement label snssai
  //  All zeros should not be allowed in 3gpp
  //  or OAI will crash
  //  We just want to get all the UEs...
  int const nssai[] = {0,0,0,0}; // sst, sd16, sd8, sd0
  *test_info_lst = filter_predicate(type, condition, nssai);

  // Action definition Format 1
  dst.action_def_format_1 = gen_kpm_act_def_frmt_1(elm, period_ms);  // 8.2.1.2.1

  return dst;
}

static
e2sm_rc_act_def_frmt_1_t gen_rc_act_def_frm_1(elm_oran_sm_conf_t const* elm)
{
  e2sm_rc_act_def_frmt_1_t act_def_frm_1 = {0};

  // Parameters to be Reported List
  // [1-65535]
  // 8.2.2
  act_def_frm_1.sz_param_report_def = elm->sz_act;  
  act_def_frm_1.param_report_def = calloc(act_def_frm_1.sz_param_report_def, sizeof(param_report_def_t));
  assert(act_def_frm_1.param_report_def != NULL && "Memory exhausted");

  // Current UE ID RAN Parameter
  for (size_t i = 0; i < act_def_frm_1.sz_param_report_def; i++) {
    // use id
    assert(elm->actions[i].type == INT32_ACT_NAME_ID_E); 
    act_def_frm_1.param_report_def[i].ran_param_id = elm->actions[i].id;
  }

  return act_def_frm_1;
}

static
e2sm_rc_action_def_t gen_rc_act_def(elm_oran_sm_conf_t const* elm, uint32_t ric_style_type, e2sm_rc_act_def_format_e act_frmt)
{
  e2sm_rc_action_def_t dst = {0};
  dst.ric_style_type = ric_style_type;
  dst.format = act_frmt;
  if (act_frmt == FORMAT_1_E2SM_RC_ACT_DEF) {
    dst.frmt_1 = gen_rc_act_def_frm_1(elm);
  } else {
    assert(0!=0 && "not supported RC action definition\n");
  }

  return dst;
}

static
kpm_act_def_t gen_kpm_act_def(elm_oran_sm_conf_t const* elm, format_action_def_e act_frm, uint32_t period_ms)
{
  kpm_act_def_t dst = {0};

  if (act_frm == FORMAT_1_ACTION_DEFINITION) {
    dst.type = FORMAT_1_ACTION_DEFINITION;
    dst.frm_1 = gen_kpm_act_def_frmt_1(elm, period_ms);
  } else if (act_frm == FORMAT_4_ACTION_DEFINITION) {
    dst.type = FORMAT_4_ACTION_DEFINITION;
    dst.frm_4 = gen_kpm_act_def_frmt_4(elm, period_ms);
  } else {
    assert(0!=0 && "not support action definition type");
  }

  return dst;
}

int main(int argc, char *argv[])
{
  assert(argc == 2 && "Configuraiton file needed!");

  //Init the xApp
  init_xapp_api(argv[1]);
  sub_oran_sm_conf_t conf = init_sub_oran_sm_conf(argv[1]);
  defer({ free_sub_oran_sm_conf(&conf); });
  sleep(1);

  e2_node_arr_xapp_t nodes = e2_nodes_xapp_api();
  defer({ free_e2_node_arr_xapp(&nodes); });

  assert(nodes.len > 0);

  printf("Connected E2 nodes = %d\n", nodes.len);

  //Init SM handler
  sm_ans_xapp_t* kpm_handle = NULL;
  sm_ans_xapp_t* rc_handle = NULL;

  if(nodes.len > 0){
    kpm_handle = calloc( nodes.len, sizeof(sm_ans_xapp_t) );
    assert(kpm_handle  != NULL);
    rc_handle = calloc( nodes.len, sizeof(sm_ans_xapp_t) );
    assert(rc_handle  != NULL);
  }

  int n_kpm_handle = 0;
  int n_rc_handle = 0;
  //Subscribe SMs for all the E2-nodes
  for (int i = 0; i < nodes.len; i++) {
    e2_node_connected_xapp_t* n = &nodes.n[i];
    for (size_t j = 0; j < n->len_rf; j++)
      printf("Registered node %d ran func id = %d \n ", i, n->rf[j].id);

    for (size_t j = 0; j < conf.sz_elm; j++) {
      if (!strcasecmp(conf.elm[j].name, "kpm")) {
        kpm_sub_data_t kpm_sub = {0};
        defer({ free_kpm_sub_data(&kpm_sub); });

        // KPM Event Trigger
        uint64_t period_ms = conf.elm[j].periodicity_ms;
        kpm_sub.ev_trg_def = gen_kpm_ev_trig(period_ms);
        printf("[xApp]: reporting period = %lu [ms]\n", period_ms);

        // KPM Action Definition
        kpm_sub.sz_ad = 1;
        kpm_sub.ad = calloc(1, sizeof(kpm_act_def_t));
        assert(kpm_sub.ad != NULL && "Memory exhausted");
        format_action_def_e act_type = END_ACTION_DEFINITION;
        if (conf.elm[j].format == 1)
          act_type = FORMAT_1_ACTION_DEFINITION;
        else if (conf.elm[j].format == 4)
          act_type = FORMAT_4_ACTION_DEFINITION;
        else
          assert(0!=0 && "not supported action definition format");

        *kpm_sub.ad = gen_kpm_act_def(&conf.elm[j], act_type, period_ms);
        // TODO: implement e2ap_ngran_eNB
        if (n->id.type == e2ap_ngran_eNB)
          continue;
        if (strcasecmp(conf.elm[j].ran_type, get_e2ap_ngran_name(n->id.type)))
          continue;
        printf("xApp subscribes RAN Func ID %d in E2 node idx %d, nb_id %d\n", SM_KPM_ID, i, n->id.nb_id.nb_id);
        kpm_handle[i] = report_sm_xapp_api(&nodes.n[i].id, SM_KPM_ID, &kpm_sub, sm_cb_kpm);
        assert(kpm_handle[i].success == true);
        n_kpm_handle += 1;

      } else if (!strcasecmp(conf.elm[j].name, "rc")) {
        rc_sub_data_t rc_sub = {0};

        // RC Event Trigger
        rc_sub.et = gen_rc_ev_trig(FORMAT_2_E2SM_RC_EV_TRIGGER_FORMAT);

        // RC Action Definition
        rc_sub.sz_ad = 1;
        rc_sub.ad = calloc(rc_sub.sz_ad, sizeof(e2sm_rc_action_def_t));
        assert(rc_sub.ad != NULL && "Memory exhausted");
        assert(conf.elm[j].format == 1 && "Only Format 1 supported");
        e2sm_rc_act_def_format_e act_type =  FORMAT_1_E2SM_RC_ACT_DEF;

        // use RIC style 2 by default
        *rc_sub.ad = gen_rc_act_def(&conf.elm[j], 2, act_type);
        defer({ free_rc_sub_data(&rc_sub); });

        // RC HO only supports for e2ap_ngran_gNB
        if (n->id.type == e2ap_ngran_eNB || n->id.type == e2ap_ngran_gNB_CU || n->id.type == e2ap_ngran_gNB_DU)
          continue;
        if (strcasecmp(conf.elm[j].ran_type, get_e2ap_ngran_name(n->id.type)))
          continue;
        printf("xApp subscribes RAN Func ID %d in E2 node idx %d, nb_id %d\n", SM_RC_ID, i, n->id.nb_id.nb_id);
        rc_handle[i] = report_sm_xapp_api(&nodes.n[i].id, SM_RC_ID, &rc_sub, sm_cb_rc);
        assert(rc_handle[i].success == true);
        n_rc_handle += 1;

      } else {
        assert(0!=0 && "unknown SM in .ymal");
      }
    }

    sleep(1);
  }

  sleep(conf.runtime_sec);

  for(int i = 0; i < n_kpm_handle; ++i) {
    rm_report_sm_xapp_api(kpm_handle[i].u.handle);
    sleep(1);
  }

  for(int i = 0; i < n_rc_handle; ++i) {
    rm_report_sm_xapp_api(rc_handle[i].u.handle);
    sleep(1);
  }

  // free sm handel
  free(kpm_handle);
  free(rc_handle);


  //Stop the xApp
  while(try_stop_xapp_api() == false)
    usleep(1000);

  printf("Test xApp run SUCCESSFULLY\n");
}
