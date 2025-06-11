/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#include "../include/src/xApp/e42_xapp_api.h"
#include "../include/src/util/alg_ds/alg/defer.h"
#include "../include/src/sm/mac_sm/mac_sm_id.h"
#include "../include/src/sm/rlc_sm/rlc_sm_id.h"
#include "../include/src/sm/pdcp_sm/pdcp_sm_id.h"
#include "../include/src/sm/gtp_sm/gtp_sm_id.h"
#include "../include/src/sm/slice_sm/slice_sm_id.h"
#include "../include/src/sm/kpm_sm/kpm_sm_id_wrapper.h"
#include "../include/src/sm/rc_sm/rc_sm_id.h"
#include "../include/src/util/e2ap_ngran_types.h"
#include "../include/src/util/alg_ds/ds/lock_guard/lock_guard.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

static bool exit_flag = false;
static void sigint_handler(int sig)
{
  printf("signal %d received !\n", sig);
  exit_flag = true;
}

static
pthread_mutex_t mtx;

static
void sm_cb_all(sm_ag_if_rd_t const* rd, global_e2_node_id_t const* e2_node)
{
  assert(rd != NULL);

  int64_t now = time_now_us_xapp_api();
  if (rd->ind.type == MAC_STATS_V0) {
    printf("MAC ind_msg latency = %lu from E2-node type %d ID %d\n",
           now - rd->ind.mac.msg.tstamp, e2_node->type, e2_node->nb_id.nb_id);
  } else if (rd->ind.type == RLC_STATS_V0) {
    printf("RLC ind_msg latency = %lu from E2-node type %d ID %d\n",
           now - rd->ind.rlc.msg.tstamp, e2_node->type, e2_node->nb_id.nb_id);
  } else if (rd->ind.type == PDCP_STATS_V0) {
    printf("PDCP ind_msg latency = %lu from E2-node type %d ID %d\n",
           now - rd->ind.pdcp.msg.tstamp, e2_node->type, e2_node->nb_id.nb_id);
  } else if (rd->ind.type == GTP_STATS_V0) {
    printf("GTP ind_msg latency = %ld from E2-node type %d ID %d\n",
           now - rd->ind.gtp.msg.tstamp, e2_node->type, e2_node->nb_id.nb_id);
  } else if (rd->ind.type == SLICE_STATS_V0) {
    printf("SLICE ind_msg latency = %ld from E2-node type %d ID %d\n",
           now - rd->ind.slice.msg.tstamp, e2_node->type, e2_node->nb_id.nb_id);
  } else if (rd->ind.type == KPM_STATS_V3_0) {
    if (rd->ind.kpm.ind.hdr.kpm_ric_ind_hdr_format_1.collectStartTime) {
      kpm_ind_data_t const* kpm = &rd->ind.kpm.ind;
      kpm_ric_ind_hdr_format_1_t const* hdr_frm_1 = &kpm->hdr.kpm_ric_ind_hdr_format_1;
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

        if (hdr_frm_1->fileformat_version)
          printf("FileFormat Version {%s} ", hdr_frm_1->fileformat_version->buf);
        if (hdr_frm_1->sender_name)
          printf("Sender Name {%s} ", hdr_frm_1->sender_name->buf);
        if (hdr_frm_1->sender_type)
          printf("Sender Type {%s} ", hdr_frm_1->sender_type->buf);
        if (hdr_frm_1->vendor_name)
          printf("Vendor Name {%s} ", hdr_frm_1->vendor_name->buf);
        printf("\n");

        if (kpm->msg.type == FORMAT_1_INDICATION_MESSAGE) {
          kpm_ind_msg_format_1_t const* msg_frm_1 = &kpm->msg.frm_1;
          for (size_t i = 0; i < msg_frm_1->meas_data_lst_len; i++) {
            for (size_t j = 0; j < msg_frm_1->meas_data_lst[i].meas_record_len; j++) {
              if (msg_frm_1->meas_info_lst_len > 0) {
                switch (msg_frm_1->meas_info_lst[j].meas_type.type) {
                  case NAME_MEAS_TYPE:
                  {
                    // Get the Measurement Name
                    char meas_info_name_str[msg_frm_1->meas_info_lst[j].meas_type.name.len + 1];
                    memcpy(meas_info_name_str, msg_frm_1->meas_info_lst[j].meas_type.name.buf,
                           msg_frm_1->meas_info_lst[j].meas_type.name.len);
                    meas_info_name_str[msg_frm_1->meas_info_lst[j].meas_type.name.len] = '\0';
                    // Get the value of the Measurement
                    switch (msg_frm_1->meas_data_lst[i].meas_record_lst[j].value)
                    {
                      case INTEGER_MEAS_VALUE: {
                        //printf("meas record INTEGER_MEAS_VALUE value %d\n",msg_frm_1->meas_data_lst[i].meas_record_lst[j].int_val);
                        printf("%s = %d\n", meas_info_name_str, msg_frm_1->meas_data_lst[i].meas_record_lst[j].int_val);
                        break;
                      }

                      case REAL_MEAS_VALUE: {
                        //printf("meas record REAL_MEAS_VALUE value %f\n", msg_frm_1->meas_data_lst[i].meas_record_lst[j].real_val);
                        printf("%s = %.2f\n", meas_info_name_str, msg_frm_1->meas_data_lst[i].meas_record_lst[j].real_val);
                        break;
                      }

                      case NO_VALUE_MEAS_VALUE: {
                        printf("meas record NO_VALUE_MEAS_VALUE value\n");
                        break;
                      }

                      default:
                        assert("Value not recognized");
                    }
                    break;
                  }

                  default:
                    assert(false && "Measurement Type not yet implemented");
                }
              }
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
                  if (msg_frm_3->meas_report_per_ue[i].ue_meas_report_lst.gnb.ran_ue_id != NULL) {
                    printf("UE ID type = gNB, RAN UE ID = %lu, AMF UE NGAP ID = %lu\n",
                           *msg_frm_3->meas_report_per_ue[i].ue_meas_report_lst.gnb.ran_ue_id,
                           msg_frm_3->meas_report_per_ue[i].ue_meas_report_lst.gnb.amf_ue_ngap_id);
                  }
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
  } else if (rd->ind.type == RAN_CTRL_STATS_V1_03) {
    // Reading Indication Message Format 2
    e2sm_rc_ind_msg_frmt_2_t const *msg_frm_2 = &rd->ind.rc.ind.msg.frmt_2;
    printf("RC REPORT Style 2 - Call Process Outcome\n");
    for (size_t i = 0; i < msg_frm_2->sz_seq_ue_id; i++)
    {
      switch (msg_frm_2->seq_ue_id[i].ue_id.type)
      {
        case GNB_UE_ID_E2SM:
          printf("UE connected to gNB with amf_ue_ngap_id = %lu\n", msg_frm_2->seq_ue_id[i].ue_id.gnb.amf_ue_ngap_id);
          break;
        default:
          printf("Not yet implemented UE ID type\n");
      }
    }
  } else {
    assert(0 != 0 && "Unknown SM\n");
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
  e2sm_rc_event_trigger_t dst = {0};

  if (act_frm == FORMAT_2_E2SM_RC_EV_TRIGGER_FORMAT) {
    dst.format = FORMAT_2_E2SM_RC_EV_TRIGGER_FORMAT;
    dst.frmt_2 = gen_rc_ev_trig_frm_2();
  } else {
    assert(0!=0 && "not support event trigger type");
  }

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
meas_info_format_1_lst_t gen_meas_info_format_1_lst(const act_name_id_t act)
{
  meas_info_format_1_lst_t dst = {0};

  // use id
  if (!strcasecmp(act.name, "null")) {
    dst.meas_type.type = ID_MEAS_TYPE;
    dst.meas_type.id = act.id;
  } else { // use name
    dst.meas_type.type = NAME_MEAS_TYPE;
    // ETSI TS 128 552
    dst.meas_type.name = cp_str_to_ba(act.name);
  }

  dst.label_info_lst_len = 1;
  dst.label_info_lst = calloc(1, sizeof(label_info_lst_t));
  assert(dst.label_info_lst != NULL && "Memory exhausted");
  dst.label_info_lst[0].noLabel = calloc(1, sizeof(enum_value_e));
  assert(dst.label_info_lst[0].noLabel != NULL && "Memory exhausted");
  *dst.label_info_lst[0].noLabel = TRUE_ENUM_VALUE;

  return dst;
}

static
kpm_act_def_format_1_t gen_kpm_act_def_frmt_1(const sub_oran_sm_t sub_sm, uint32_t period_ms, e2_node_connected_xapp_t* n)
{
  (void) n;
  kpm_act_def_format_1_t dst = {0};

  dst.gran_period_ms = period_ms;

  dst.meas_info_lst_len = sub_sm.act_len;
  dst.meas_info_lst = calloc(dst.meas_info_lst_len, sizeof(meas_info_format_1_lst_t));
  assert(dst.meas_info_lst != NULL && "Memory exhausted");

  for(size_t i = 0; i < dst.meas_info_lst_len; i++) {
    dst.meas_info_lst[i] = gen_meas_info_format_1_lst(sub_sm.actions[i]);
  }

  return dst;
}

static
test_info_lst_t filter_predicate(test_cond_type_e type, test_cond_e cond, int value)
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
  const size_t len_nssai = 1;
  dst.test_cond_value->octet_string_value->len = len_nssai;
  dst.test_cond_value->octet_string_value->buf = calloc(len_nssai, sizeof(uint8_t));
  assert(dst.test_cond_value->octet_string_value->buf != NULL && "Memory exhausted");
  dst.test_cond_value->octet_string_value->buf[0] = value;

  return dst;
}

static
kpm_act_def_format_4_t gen_kpm_act_def_frmt_4(const sub_oran_sm_t sub_sm, uint32_t period_ms, e2_node_connected_xapp_t* n)
{
  kpm_act_def_format_4_t dst = {0};

  // [1, 32768]
  dst.matching_cond_lst_len = 1;

  dst.matching_cond_lst = calloc(dst.matching_cond_lst_len, sizeof(matching_condition_format_4_lst_t));
  assert(dst.matching_cond_lst != NULL && "Memory exhausted");
  test_info_lst_t* test_info_lst = &dst.matching_cond_lst[0].test_info_lst;

  // Filter connected UEs by S-NSSAI criteria
  test_cond_type_e const type = S_NSSAI_TEST_COND_TYPE;
  test_cond_e const condition = EQUAL_TEST_COND;
  int const value = 1;
  *test_info_lst = filter_predicate(type, condition, value);

  // Action definition Format 1
  dst.action_def_format_1 = gen_kpm_act_def_frmt_1(sub_sm, period_ms, n);  // 8.2.1.2.1

  return dst;
}

static
e2sm_rc_act_def_frmt_1_t gen_rc_act_def_frm_1(const sub_oran_sm_t sub_sm)
{
  e2sm_rc_act_def_frmt_1_t act_def_frm_1 = {0};

  // Parameters to be Reported List
  // [1-65535]
  // 8.2.2
  act_def_frm_1.sz_param_report_def = sub_sm.act_len;
  act_def_frm_1.param_report_def = calloc(act_def_frm_1.sz_param_report_def, sizeof(param_report_def_t));
  assert(act_def_frm_1.param_report_def != NULL && "Memory exhausted");

  // Current UE ID RAN Parameter
  for (size_t i = 0; i < act_def_frm_1.sz_param_report_def; i++) {
    // use id
    if (!strcasecmp(sub_sm.actions[i].name, "null")) {
      act_def_frm_1.param_report_def[i].ran_param_id = sub_sm.actions[i].id;
    } else { // use name
      assert(0!=0 && "not supported Name for RC action definition\n");
    }
  }

  return act_def_frm_1;
}

static
e2sm_rc_action_def_t gen_rc_act_def(const sub_oran_sm_t sub_sm, uint32_t ric_style_type, e2sm_rc_act_def_format_e act_frmt)
{
  e2sm_rc_action_def_t dst = {0};
  dst.ric_style_type = ric_style_type;
  dst.format = act_frmt;
  if (act_frmt == FORMAT_1_E2SM_RC_ACT_DEF) {
    dst.frmt_1 = gen_rc_act_def_frm_1(sub_sm);
  } else {
    assert(0!=0 && "not supported RC action definition\n");
  }

  return dst;
}

static
kpm_act_def_t gen_kpm_act_def(const sub_oran_sm_t sub_sm, format_action_def_e act_frm, uint32_t period_ms, e2_node_connected_xapp_t* n)
{
  kpm_act_def_t dst = {0};

  if (act_frm == FORMAT_1_ACTION_DEFINITION) {
    dst.type = FORMAT_1_ACTION_DEFINITION;
    dst.frm_1 = gen_kpm_act_def_frmt_1(sub_sm, period_ms, n);
  } else if (act_frm == FORMAT_4_ACTION_DEFINITION) {
    dst.type = FORMAT_4_ACTION_DEFINITION;
    dst.frm_4 = gen_kpm_act_def_frmt_4(sub_sm, period_ms, n);
  } else {
    assert(0!=0 && "not support action definition type");
  }

  return dst;
}

size_t max_handle = 256;
size_t c_handle = 0;

static
void send_subscription_req(e2_node_connected_xapp_t* n, size_t n_idx, sm_ans_xapp_t* handle, fr_args_t args) {
  // send subscription request to each e2 nodes
  if (E2AP_NODE_IS_MONOLITHIC(n->id.type))
    printf("E2 node idx %ld info: nb_id %d, mcc %d, mnc %d, mnc_digit_len %d, ran_type %s\n",
           n_idx,
           n->id.nb_id.nb_id,
           n->id.plmn.mcc,
           n->id.plmn.mnc,
           n->id.plmn.mnc_digit_len,
           get_e2ap_ngran_name(n->id.type));
  else
    printf("E2 node idx %ld info: nb_id %d, mcc %d, mnc %d, mnc_digit_len %d, ran_type %s, cu_du_id %lu\n",
           n_idx,
           n->id.nb_id.nb_id,
           n->id.plmn.mcc,
           n->id.plmn.mnc,
           n->id.plmn.mnc_digit_len,
           get_e2ap_ngran_name(n->id.type),
           *n->id.cu_du_id);
  for (size_t j = 0; j < n->len_rf; j++)
    printf("Registered E2 node idx %ld, supported RAN Func ID = %d\n ", n_idx, n->rf[j].id);

  uint16_t num_cust_sm = args.sub_cust_sm_len;
  for (int32_t i = 0; i < num_cust_sm; i++) {
    uint16_t sm_id;
    bool do_sub = false;
    if (!strcasecmp(args.sub_cust_sm[i].name, "mac")) {
      sm_id = SM_MAC_ID;
      if (n->id.type == e2ap_ngran_gNB || n->id.type == e2ap_ngran_gNB_DU || n->id.type == e2ap_ngran_eNB)
        do_sub = true;
    } else if (!strcasecmp(args.sub_cust_sm[i].name, "rlc")) {
      sm_id = SM_RLC_ID;
      if (n->id.type == e2ap_ngran_gNB || n->id.type == e2ap_ngran_gNB_DU || n->id.type == e2ap_ngran_eNB)
        do_sub = true;
    } else if (!strcasecmp(args.sub_cust_sm[i].name, "pdcp")) {
      sm_id = SM_PDCP_ID;
      if (n->id.type == e2ap_ngran_gNB || n->id.type == e2ap_ngran_gNB_CU || n->id.type == e2ap_ngran_eNB)
        do_sub = true;
    } else if (!strcasecmp(args.sub_cust_sm[i].name, "gtp")) {
      sm_id = SM_GTP_ID;
      if (n->id.type == e2ap_ngran_gNB)
        do_sub = true;
    } else if (!strcasecmp(args.sub_cust_sm[i].name, "slice")) {
      sm_id = SM_SLICE_ID;
      if (n->id.type == e2ap_ngran_gNB || n->id.type == e2ap_ngran_eNB)
        do_sub = true;
    } else {
      assert(0!=0 && "unknown SM in .conf");
    }

    if (!do_sub)
      continue;
    printf("xApp subscribes RAN Func ID %d in E2 node idx %ld, nb_id %d\n", sm_id, n_idx, n->id.nb_id.nb_id);
    handle[c_handle] = report_sm_xapp_api(&n->id, sm_id, (void*)args.sub_cust_sm[i].time, sm_cb_all);
    assert(handle[c_handle].success == true);
    c_handle+=1;
  }

  uint16_t num_oran_sm = args.sub_oran_sm_len;
  for (int32_t i = 0; i < num_oran_sm; i++) {
    uint16_t sm_id;
    if (!strcasecmp(args.sub_oran_sm[i].name, "kpm")) {
      sm_id = SM_KPM_ID;
      kpm_sub_data_t kpm_sub = {0};
      defer({ free_kpm_sub_data(&kpm_sub); });

      // KPM Event Trigger
      uint64_t period_ms = args.sub_oran_sm[i].time;
      kpm_sub.ev_trg_def = gen_kpm_ev_trig(period_ms);
      printf("[xApp]: reporting period = %lu [ms]\n", period_ms);

      // KPM Action Definition
      kpm_sub.sz_ad = 1;
      kpm_sub.ad = calloc(1, sizeof(kpm_act_def_t));
      assert(kpm_sub.ad != NULL && "Memory exhausted");
      format_action_def_e act_type = FORMAT_1_ACTION_DEFINITION;
      if (args.sub_oran_sm[i].format == 1)
        act_type = FORMAT_1_ACTION_DEFINITION;
      else if (args.sub_oran_sm[i].format == 4)
        act_type = FORMAT_4_ACTION_DEFINITION;
      else
        assert(0!=0 && "not supported action definition format");

      *kpm_sub.ad = gen_kpm_act_def((const sub_oran_sm_t)args.sub_oran_sm[i], act_type, period_ms, n);

      // TODO: implement e2ap_ngran_eNB
      if (n->id.type == e2ap_ngran_eNB)
        continue;
      if (strcasecmp(args.sub_oran_sm[i].ran_type, get_e2ap_ngran_name(n->id.type)))
        continue;
      printf("xApp subscribes RAN Func ID %d in E2 node idx %ld, nb_id %d\n", sm_id, n_idx, n->id.nb_id.nb_id);
      handle[c_handle] = report_sm_xapp_api(&n->id, sm_id, &kpm_sub, sm_cb_all);
      assert(handle[c_handle].success == true);
      c_handle+=1;
    } else if (!strcasecmp(args.sub_oran_sm[i].name, "rc")) {
      sm_id = SM_RC_ID;
      rc_sub_data_t rc_sub = {0};
      defer({ free_rc_sub_data(&rc_sub); });

      // RC Event Trigger
      rc_sub.et = gen_rc_ev_trig(FORMAT_2_E2SM_RC_EV_TRIGGER_FORMAT);

      // RC Action Definition
      rc_sub.sz_ad = 1;
      rc_sub.ad = calloc(rc_sub.sz_ad, sizeof(e2sm_rc_action_def_t));
      assert(rc_sub.ad != NULL && "Memory exhausted");
      assert(args.sub_oran_sm[i].format == 1);
      e2sm_rc_act_def_format_e act_type = FORMAT_1_E2SM_RC_ACT_DEF;

      // use RIC style 2 by default
      *rc_sub.ad = gen_rc_act_def((const sub_oran_sm_t)args.sub_oran_sm[i], 2, act_type);

      // RC HO only supports for e2ap_ngran_gNB
      if (n->id.type == e2ap_ngran_eNB || n->id.type == e2ap_ngran_gNB_CU || n->id.type == e2ap_ngran_gNB_DU)
        continue;
      if (strcasecmp(args.sub_oran_sm[i].ran_type, get_e2ap_ngran_name(n->id.type)))
        continue;
      printf("xApp subscribes RAN Func ID %d in E2 node idx %ld, nb_id %d\n", sm_id, n_idx, n->id.nb_id.nb_id);
      handle[c_handle] = report_sm_xapp_api(&n->id, sm_id, &rc_sub, sm_cb_all);
      assert(handle[c_handle].success == true);
      c_handle+=1;
    } else {
      assert(0!=0 && "unknown SM in .conf");
    }
  }
}

int main(int argc, char *argv[])
{
  srand(time(0));
  fr_args_t args = init_fr_args(argc, argv);
  defer({ free_fr_args(&args); });

  //Init the xApp
  init_xapp_api(&args);
  signal(SIGINT, sigint_handler); // we override the signal mask set in init_xapp_api()
  signal(SIGTERM, sigint_handler);
  sleep(1);

  sm_ans_xapp_t *handle = NULL;
  if (max_handle > 0) {
    handle = calloc(max_handle, sizeof(sm_ans_xapp_t *));
    assert(handle != NULL);
  }

  size_t nodes_len = e2_nodes_len_xapp_api();
  // start the xApp subscription procedure until detect connected E2 nodes
  while (nodes_len <= 0) {
    // get the original connected e2 nodes info
    size_t tmp_len = e2_nodes_len_xapp_api();
    if (tmp_len > nodes_len) {
      printf("Update connected E2 nodes len = %ld\n", tmp_len);
      nodes_len = tmp_len;
    } else {
      printf("No E2 node connects\n");
      sleep(1);
    }
  }

  // case1: send subscription req to the original connected e2 node
  // get original e2 nodes info
  e2_node_arr_xapp_t nodes = e2_nodes_xapp_api();
  defer({ free_e2_node_arr_xapp(&nodes); });
  for (size_t i = 0; i < nodes.len; i++) {
    printf("Sending subscription \n");
    send_subscription_req(&nodes.n[i], i, handle, args);
  }

  // case2: send subscription req to the new connected e2 node
  while(!exit_flag) {
    size_t cur_nodes_len = e2_nodes_len_xapp_api();

    if (cur_nodes_len != nodes_len) {
      printf("/////// detect E2 nodes len update, new len = %ld, old len = %ld ///////\n", cur_nodes_len, nodes_len);

      if (cur_nodes_len != 0) {
        // get the new e2 nodes info
        e2_node_arr_xapp_t cur_nodes = e2_nodes_xapp_api();
        defer({ free_e2_node_arr_xapp(&nodes); });

        // TODO: send subscription request to new e2 node
        for (size_t i = 0; i < cur_nodes_len; i++) {
          //printf("/////////////// new E2 node list, idx %ld, nb_id %d, type %s //////////////\n", i,
          //       cur_nodes.n[i].id.nb_id.nb_id, get_e2ap_ngran_name(cur_nodes.n[i].id.type));
          e2ap_ngran_node_t cur_type = cur_nodes.n[i].id.type;
          uint32_t cur_nb_id = cur_nodes.n[i].id.nb_id.nb_id;
          bool new_type = 1;
          bool new_nb_id = 1;
          // compare the type between old and new e2 nodes list
          for (size_t j = 0; j < nodes_len; j++) {
            //printf("/////////////// old E2 node list, idx %ld, nb_id %d, type %s //////////////\n", j,
            //       nodes.n[j].id.nb_id.nb_id, get_ngran_name(nodes.n[j].id.type));
            if (nodes.n[j].id.type == cur_type) new_type = 0;
            if (nodes.n[j].id.nb_id.nb_id == cur_nb_id) new_nb_id = 0;
          }
          if (new_type || new_nb_id) {
            printf("/////////////// send sub req to new E2 node, nb_id %d, type %s //////////////\n", cur_nodes.n[i].id.nb_id.nb_id, get_e2ap_ngran_name(cur_nodes.n[i].id.type));
            send_subscription_req(&cur_nodes.n[i], i, handle, args);
          }
        }
      }
      nodes_len = cur_nodes_len;
      nodes = e2_nodes_xapp_api();

      if (nodes_len == 0)
        c_handle = 0;
    }
    sleep(1);
  }

  printf("CTRL+C detect\n");
  // TODO: send subscription request delete
  for(size_t i = 0; i < c_handle; ++i)
    rm_report_sm_xapp_api(handle[i].u.handle);

  // free sm handel
  // TODO: free handle
  free(handle);

  // stop the xApp
  while(try_stop_xapp_api() == false)
    usleep(1000);


  printf("Test xApp run SUCCESSFULLY\n");
}



