#include "../include/src/xApp/e42_xapp_api.h"
#include "../include/src/sm/ccc_sm/ccc_sm_id.h"
#include "../include/src/util/alg_ds/alg/defer.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

typedef struct {
  uint8_t	  sST;
  uint32_t  sD;
} s_nssai_e2sm_plain_t;

typedef struct {
  resource_type_e       resource_type;
  uint8_t               rrm_policy_max_ratio;
  uint8_t               rrm_policy_min_ratio;
  uint8_t               rrm_policy_dedicated_ratio;
  e2sm_plmn_t           plmn_id;
  s_nssai_e2sm_plain_t  nssai;
} ccc_ctrl_rrm_policy_t;


size_t num_dl_slices = 3;
size_t num_ul_slices = 3;
static ccc_ctrl_rrm_policy_t const rrm_policy_dl[3] = {
  {
    .resource_type = PRB_DL_RESOURCE_TYPE,
    .rrm_policy_max_ratio = 10,
    .rrm_policy_min_ratio = 10,
    .rrm_policy_dedicated_ratio = 10,
    .plmn_id = (e2sm_plmn_t){.mcc = 1, .mnc =1, .mnc_digit_len = 2},
    // we assume nssai 0.0 as default slice for SRB
    .nssai.sST = 0,
    .nssai.sD = 0
  },
  {
    .resource_type = PRB_DL_RESOURCE_TYPE,
    .rrm_policy_max_ratio = 40,
    .rrm_policy_min_ratio = 40,
    .rrm_policy_dedicated_ratio = 40,
    .plmn_id = (e2sm_plmn_t){.mcc = 1, .mnc =1, .mnc_digit_len = 2},
    .nssai.sST = 1,
    .nssai.sD = 0xffffff // if sD is NULL, put 0xffffff
  },
  {
    .resource_type = PRB_DL_RESOURCE_TYPE,
    .rrm_policy_max_ratio = 50,
    .rrm_policy_min_ratio = 50,
    .rrm_policy_dedicated_ratio = 50,
    .plmn_id = (e2sm_plmn_t){.mcc = 1, .mnc =1, .mnc_digit_len = 2},
    .nssai.sST = 2,
    .nssai.sD = 0x000001
  }
};

static ccc_ctrl_rrm_policy_t const rrm_policy_ul[3] = {
  {
    .resource_type = PRB_UL_RESOURCE_TYPE,
    .rrm_policy_max_ratio = 10,
    .rrm_policy_min_ratio = 10,
    .rrm_policy_dedicated_ratio = 10,
    .plmn_id = (e2sm_plmn_t){.mcc = 1, .mnc =1, .mnc_digit_len = 2},
    // we assume nssai 0.0 as default slice for SRB
    .nssai.sST = 0,
    .nssai.sD = 0
  },
  {
    .resource_type = PRB_UL_RESOURCE_TYPE,
    .rrm_policy_max_ratio = 30,
    .rrm_policy_min_ratio = 30,
    .rrm_policy_dedicated_ratio = 30,
    .plmn_id = (e2sm_plmn_t){.mcc = 1, .mnc =1, .mnc_digit_len = 2},
    .nssai.sST = 1,
    .nssai.sD = 0xffffff // if sD is NULL, put 0xffffff
  },
  {
    .resource_type = PRB_UL_RESOURCE_TYPE,
    .rrm_policy_max_ratio = 50,
    .rrm_policy_min_ratio = 50,
    .rrm_policy_dedicated_ratio = 50,
    .plmn_id = (e2sm_plmn_t){.mcc = 1, .mnc =1, .mnc_digit_len = 2},
    .nssai.sST = 2,
    .nssai.sD = 0x000001
  }
};

static
e2sm_ccc_event_trigger_t gen_ev_trig(void)
{
  // Periodic event
  e2sm_ccc_event_trigger_t dst = {.format = FORMAT_3_E2SM_CCC_EV_TRIGGER_FORMAT};
  dst.frmt_3.period = 1000;

  return dst;
}

static
e2sm_ccc_action_def_t gen_act_def(void)
{
  e2sm_ccc_action_def_t dst = {.format = FORMAT_1_E2SM_CCC_ACT_DEF};
  size_t sz_act_def_ran_conf = 1;
  dst.frmt_1.sz_act_def_ran_conf = sz_act_def_ran_conf;
  dst.frmt_1.act_def_ran_conf = calloc(sz_act_def_ran_conf, sizeof(act_def_ran_conf_t));
  assert(dst.frmt_1.act_def_ran_conf != NULL);

  dst.frmt_1.act_def_ran_conf[0].report_type = REPORT_TYPE_ALL;
  dst.frmt_1.act_def_ran_conf[0].ran_conf_name = cp_str_to_ba("O-RRMPolicyRatio");
  dst.frmt_1.act_def_ran_conf[0].sz_attribute = 0;

  return dst;
}

void cb(sm_ag_if_rd_t const *rd, global_e2_node_id_t const *e2_node)
{
  assert(e2_node != NULL);
  assert(rd != NULL);
  assert(rd->type == INDICATION_MSG_AGENT_IF_ANS_V0);
  assert(rd->ind.type == CCC_STATS_V3_0);

  ccc_ind_data_t const* ind = &rd->ind.ccc.ind;

  // Header
  assert(ind->hdr.format == FORMAT_1_E2SM_CCC_IND_HDR);
  uint64_t event_time = strtoull((char*)ind->hdr.frmt_1.event_time, NULL, 10);
  // indication_reason_e ind_reason;
  int64_t now = time_now_us_xapp_api();
  printf("CCC ind_msg latency %ld from E2-Node type %d ID %u\n", now - event_time, e2_node->type, e2_node->nb_id.nb_id);

  // Message
  assert(ind->msg.format == FORMAT_1_E2SM_CCC_IND_MSG);
  e2sm_ccc_ind_msg_frmt_1_t const* frmt_1 = &ind->msg.frmt_1;

  for (size_t i = 0; i < frmt_1->sz_ind_msg_node_conf; i++) {
    ind_msg_ran_conf_t const* ran_conf = &frmt_1->ind_msg_ran_conf[i];
    assert(ran_conf->change_type != END_CHANGE_TYPE);

    char* ran_conf_name = cp_ba_to_str(ran_conf->ran_conf_name);
    defer({free(ran_conf_name);});

    values_of_attributes_t* vals_attributes = &ran_conf->vals_attributes[0];
    assert(vals_attributes->values_of_attributes_type == VALUES_OF_ATTRIBUTES_O_RRMPolicyRatio);
    e2sm_ccc_o_rrm_policy_ratio_t* rrm = &vals_attributes->e2sm_ccc_o_rrm_policy_ratio;
    assert(rrm->sz_rrm_policy_member_lst == 1);
    e2sm_ccc_rrm_policy_member_t* pm = &rrm->rrm_policy_member_lst[0];

    printf("Change Type %d, RAN Configuration Structure Name %s, PLMN %03d.%02d\n", ran_conf->change_type, ran_conf_name, pm->plmn_id.mcc, pm->plmn_id.mnc);
    if (rrm->resource_type == PRB_UL_RESOURCE_TYPE || rrm->resource_type == PRB_DL_RESOURCE_TYPE) {
      printf("RAN Conf %ld: RRM Policy Ratio: Resource Type %d (1:UL,2:DL), Max %d, Min %d, Dedicated %d, NSSAI %d.%06x\n",
            i,
            rrm->resource_type,
            rrm->rrm_policy_max_ratio, rrm->rrm_policy_min_ratio, rrm->rrm_policy_dedicated_ratio,
            pm->s_nssai->sST, *pm->s_nssai->sD);
    } else {
      printf("No slices info from E2-Node\n");
    }

  }
  printf("\n");
}

static
e2sm_ccc_ctrl_hdr_t gen_hdr()
{
  e2sm_ccc_ctrl_hdr_t dst = {.format = FORMAT_1_E2SM_CCC_CTRL_HDR};
  dst.frmt_1.ric_style_type = 1;

  return dst;
}

static
e2sm_ccc_rrm_policy_member_t fill_e2sm_ccc_rrm_policy_member(e2sm_plmn_t const plmn, s_nssai_e2sm_plain_t const nssai)
{
  e2sm_ccc_rrm_policy_member_t dst = {0};

  dst.plmn_id = plmn;
  dst.s_nssai = calloc(1, sizeof(s_nssai_e2sm_t));
  assert(dst.s_nssai != NULL);
  dst.s_nssai->sST = nssai.sST;
  dst.s_nssai->sD = calloc(1, sizeof(uint32_t));
  *dst.s_nssai->sD = nssai.sD;

  return dst;
}

static
e2sm_ccc_o_rrm_policy_ratio_t fill_e2sm_ccc_o_rrm_policy_ratio(ccc_ctrl_rrm_policy_t const src)
{
  e2sm_ccc_o_rrm_policy_ratio_t dst = {0};

  dst.resource_type = src.resource_type;
  dst.rrm_policy_max_ratio = src.rrm_policy_max_ratio;
  dst.rrm_policy_min_ratio = src.rrm_policy_min_ratio;
  dst.rrm_policy_dedicated_ratio = src.rrm_policy_dedicated_ratio;

  dst.sz_rrm_policy_member_lst = 1;
  dst.rrm_policy_member_lst = calloc(dst.sz_rrm_policy_member_lst, sizeof(e2sm_ccc_rrm_policy_member_t));
  assert(dst.rrm_policy_member_lst != NULL);
  dst.rrm_policy_member_lst[0] = fill_e2sm_ccc_rrm_policy_member(src.plmn_id, src.nssai);

  return dst;
}

static
ctrl_msg_ran_conf_t fill_ctrl_msg_ran_conf(ccc_ctrl_rrm_policy_t const rrm_policy)
{
  ctrl_msg_ran_conf_t dst = {0};

  dst.ran_conf_name = cp_str_to_ba("O-RRMPolicyRatio");
  dst.vals_attributes = calloc(1, sizeof(values_of_attributes_t));
  assert(dst.vals_attributes != NULL);
  dst.vals_attributes->values_of_attributes_type = VALUES_OF_ATTRIBUTES_O_RRMPolicyRatio;
  dst.vals_attributes->e2sm_ccc_o_rrm_policy_ratio = fill_e2sm_ccc_o_rrm_policy_ratio(rrm_policy);

  // not sure why we need this, fill the same value as previous one
  dst.old_vals_attributes = calloc(1, sizeof(values_of_attributes_t));
  assert(dst.old_vals_attributes != NULL);
  dst.old_vals_attributes->values_of_attributes_type = VALUES_OF_ATTRIBUTES_O_RRMPolicyRatio;
  dst.old_vals_attributes->e2sm_ccc_o_rrm_policy_ratio = fill_e2sm_ccc_o_rrm_policy_ratio(rrm_policy);
  return dst;
}

static
e2sm_ccc_ctrl_msg_t gen_msg()
{
  e2sm_ccc_ctrl_msg_t dst = {0};

  dst.format = FORMAT_1_E2SM_CCC_CTRL_MSG;
  dst.frmt_1.sz_ctrl_msg_ran_conf = num_dl_slices + num_ul_slices;
  dst.frmt_1.ctrl_msg_ran_conf = calloc(dst.frmt_1.sz_ctrl_msg_ran_conf, sizeof(ctrl_msg_ran_conf_t));
  assert(dst.frmt_1.ctrl_msg_ran_conf != NULL && "Memory exhausted");

  printf("\n");
  for (size_t i = 0; i < num_dl_slices; i++) {
    dst.frmt_1.ctrl_msg_ran_conf[i] = fill_ctrl_msg_ran_conf(rrm_policy_dl[i]);
    printf("Send Ctrl Msg RAN Conf %ld: Resource Type %d (1:UL,2:DL), Max %d, Min %d, Dedicated %d, NSSAI %d.%06x\n",
          i, rrm_policy_dl[i].resource_type, rrm_policy_dl[i].rrm_policy_max_ratio, rrm_policy_dl[i].rrm_policy_min_ratio, rrm_policy_dl[i].rrm_policy_dedicated_ratio,
          rrm_policy_dl[i].nssai.sST, rrm_policy_dl[i].nssai.sD);
  }
  for (size_t i = num_dl_slices; i < dst.frmt_1.sz_ctrl_msg_ran_conf; i++) {
    int u_idx = i - num_dl_slices;
    dst.frmt_1.ctrl_msg_ran_conf[i] = fill_ctrl_msg_ran_conf(rrm_policy_ul[u_idx]);
    printf("Send Ctrl Msg RAN Conf %ld: Resource Type %d (1:UL,2:DL), Max %d, Min %d, Dedicated %d, NSSAI %d.%06x\n",
          i, rrm_policy_ul[u_idx].resource_type, rrm_policy_ul[u_idx].rrm_policy_max_ratio, rrm_policy_ul[u_idx].rrm_policy_min_ratio, rrm_policy_ul[u_idx].rrm_policy_dedicated_ratio,
          rrm_policy_ul[u_idx].nssai.sST, rrm_policy_ul[u_idx].nssai.sD);
  }
  printf("\n");


  return dst;
}


bool filter_node(e2_node_connected_xapp_t const* n)
{
  assert(n!= NULL);
  return n->id.type == e2ap_ngran_gNB_DU || n->id.type == e2ap_ngran_gNB;
}

int main(int argc, char *argv[])
{
  assert(argc == 2 && "Configuraiton file needed!");

  //Init the xApp
  init_xapp_api(argv[1]);
  sleep(1);

  e2_node_arr_xapp_t nodes = e2_nodes_xapp_api();
  defer({ free_e2_node_arr_xapp(&nodes); });
  assert(nodes.len > 0);
  printf("Connected E2 nodes = %d\n", nodes.len);

  //Check connected e2-nodes
  for (size_t i = 0; i < nodes.len; ++i) {
    e2_node_connected_xapp_t *n = &nodes.n[i];
    if (filter_node(n) == false) {
      continue;
    }
    for (size_t j = 0; j < n->len_rf; ++j)
      printf("Registered ran func id = %d \n ", n->rf[j].id);
  }

  ////////////
  // START CCC
  ////////////
  
  // CCC Monitor
  // REPORT Service Style 1: Node-Level Configuration
  // RIC Action Definition IE Format 1
  // RIC Indication Header IE Format 1
  // RIC Indication Message IE Format 1
  ccc_sub_data_t ccc_sub = {0};
  ccc_sub.et = gen_ev_trig();
  ccc_sub.sz_ad = 1;
  ccc_sub.ad = calloc(ccc_sub.sz_ad, sizeof(e2sm_ccc_action_def_t));
  defer({free_ccc_sub_data(&ccc_sub);});
  assert(ccc_sub.ad != NULL);
  ccc_sub.ad[0] = gen_act_def();

  // Assuming this xApp only support 1 node
  int nidx = 0;
  sm_ans_xapp_t hndl = report_sm_xapp_api(&nodes.n[nidx].id, SM_CCC_ID, &ccc_sub, cb);
  assert(hndl.success == true);
  sleep(2);

  // CCC Control
  // CONTROL Service Style 2: Node Configuration and Control
  // RIC Control Header IE Format 1
  // RIC Control Message IE Format 1
  ccc_ctrl_req_data_t ctrl_req = {0};
  ctrl_req.hdr = gen_hdr();
  ctrl_req.msg = gen_msg();
  int64_t const t0 = time_now_us_xapp_api();
  control_sm_xapp_api(&nodes.n[nidx].id, SM_CCC_ID, &ctrl_req);
  printf("[xApp]: Control Loop Latency: %ld us\n", time_now_us_xapp_api() - t0);
  free_ccc_ctrl_req_data(&ctrl_req);

  sleep(5);

  rm_report_sm_xapp_api(hndl.u.handle);
  sleep(1);

  ////////////
  // END CCC
  ////////////

  //Stop the xApp
  while(try_stop_xapp_api() == false)
    usleep(1000);

  printf("Test xApp run SUCCESSFULLY\n");

}

