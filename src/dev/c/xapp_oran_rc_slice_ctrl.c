#include "../include/src/xApp/e42_xapp_api.h"
#include "../include/src/sm/rc_sm/ie/ir/ran_param_struct.h"
#include "../include/src/sm/rc_sm/ie/ir/ran_param_list.h"
#include "../include/src/util/alg_ds/ds/lock_guard/lock_guard.h"
#include "../include/src/sm/rc_sm/rc_sm_id.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

typedef struct {
  int           rrm_policy_max_ratio;
  int           rrm_policy_min_ratio;
  int           rrm_policy_dedicated_ratio;
  e2ap_plmn_t   plmn_id;
  const char*   sst;
  const char*   sd; // if sD is NULL, put ""
} rc_ctrl_rrm_policy_t;

// Number of slices to configure. 0 sends a Control Message Format 1 with an
// empty ranP-List (SIZE(0..)), since RANParameter-LIST requires SIZE(1..) and
// the RRM Policy Ratio List therefore cannot be empty.
static const size_t num_slice = 2;
static rc_ctrl_rrm_policy_t const rrm_policy[] = {
  {
    .rrm_policy_max_ratio = 70,
    .rrm_policy_min_ratio = 50,
    .rrm_policy_dedicated_ratio = 30,
    .plmn_id = (e2ap_plmn_t){.mcc = 1, .mnc = 1, .mnc_digit_len = 2},
    .sst = "1",
    .sd = ""
  },
  {
    .rrm_policy_max_ratio = 30,
    .rrm_policy_min_ratio = 20,
    .rrm_policy_dedicated_ratio = 20,
    .plmn_id = (e2ap_plmn_t){.mcc = 1, .mnc = 1, .mnc_digit_len = 2},
    .sst = "2",
    .sd = "1"
  }
};

//static
//void convert_plmn_to_octet(e2ap_plmn_t plmn, uint8_t* octet_str){
//  // MCC
//  uint8_t digit1 = plmn.mcc / 100;
//  uint8_t digit2 = (plmn.mcc / 10) % 10;
//  uint8_t digit3 = plmn.mcc % 10;
//
//  assert(digit1 < 10 && digit2 < 10 && digit3 < 10);
//  // MNC
//  assert(plmn.mnc_digit_len == 3 || plmn.mnc_digit_len == 2);
//  uint8_t digit4 = plmn.mnc_digit_len == 3 ? plmn.mnc / 100 : 0x000f;
//  uint8_t digit5 = (plmn.mnc / 10) % 10;
//  uint8_t digit6 = plmn.mnc % 10;
//
//  assert(digit5 < 10 && digit6 < 10);
//
//  uint8_t octet1 = (digit2 << 4) | digit1; // Octet 1: [digit2|digit1]
//  uint8_t octet2 = (digit4 << 4) | digit3; // Octet 2: [digit4|digit3]
//  uint8_t octet3 = (digit6 << 4) | digit5; // Octet 3: [digit6|digit5]
//
//  memcpy(&octet_str[0], &octet1, sizeof(uint8_t));
//  memcpy(&octet_str[1], &octet2, sizeof(uint8_t));
//  memcpy(&octet_str[2], &octet3, sizeof(uint8_t));
//}
//

static
e2sm_rc_ctrl_hdr_frmt_1_t gen_rc_ctrl_hdr_frmt_1(ue_id_e2sm_t ue_id, uint32_t ric_style_type, uint16_t ctrl_act_id)
{
  e2sm_rc_ctrl_hdr_frmt_1_t dst = {0};

  // 6.2.2.6
  dst.ue_id = cp_ue_id_e2sm(&ue_id);

  dst.ric_style_type = ric_style_type;
  dst.ctrl_act_id = ctrl_act_id;

  return dst;
}

static
e2sm_rc_ctrl_hdr_t gen_rc_ctrl_hdr(e2sm_rc_ctrl_hdr_e hdr_frmt, ue_id_e2sm_t ue_id, uint32_t ric_style_type, uint16_t ctrl_act_id)
{
  e2sm_rc_ctrl_hdr_t dst = {0};

  if (hdr_frmt == FORMAT_1_E2SM_RC_CTRL_HDR) {
    dst.format = FORMAT_1_E2SM_RC_CTRL_HDR;
    dst.frmt_1 = gen_rc_ctrl_hdr_frmt_1(ue_id, ric_style_type, ctrl_act_id);
  } else {
    assert(0!=0 && "not implemented the fill func for this ctrl hdr frmt");
  }

  return dst;
}

static
void gen_rrm_policy_ratio_group(lst_ran_param_t* RRM_Policy_Ratio_Group, rc_ctrl_rrm_policy_t const src)
{
  const e2ap_plmn_t plmnid = src.plmn_id;
  const char* sst_str = src.sst;
  const char* sd_str = src.sd;
  int max_ratio = src.rrm_policy_max_ratio;
  int min_ratio = src.rrm_policy_min_ratio;
  int dedicated_ratio = src.rrm_policy_dedicated_ratio;

  // Check constraint
  assert(100 >= max_ratio && max_ratio >= min_ratio && min_ratio >= dedicated_ratio && dedicated_ratio >= 0 && "Failed to meet RRM Policy Constraint");
  // RRM Policy Ratio Group, STRUCTURE (RRM Policy Ratio List -> RRM Policy Ratio Group)
  // lst_ran_param_t* RRM_Policy_Ratio_Group = &RRM_Policy_Ratio_List->ran_param_val.lst->lst_ran_param[0];
  // RRM_Policy_Ratio_Group->ran_param_id = RRM_Policy_Ratio_Group_8_4_3_6;
  RRM_Policy_Ratio_Group->ran_param_struct.sz_ran_param_struct = 4;
  RRM_Policy_Ratio_Group->ran_param_struct.ran_param_struct = calloc(4, sizeof(seq_ran_param_t));
  assert(RRM_Policy_Ratio_Group->ran_param_struct.ran_param_struct != NULL && "Memory exhausted");
  // RRM Policy, STRUCTURE (RRM Policy Ratio Group -> RRM Policy)
  seq_ran_param_t* RRM_Policy = &RRM_Policy_Ratio_Group->ran_param_struct.ran_param_struct[0];
  RRM_Policy->ran_param_id = RRM_Policy_8_4_3_6;
  RRM_Policy->ran_param_val.type = STRUCTURE_RAN_PARAMETER_VAL_TYPE;
  RRM_Policy->ran_param_val.strct = calloc(1, sizeof(ran_param_struct_t));
  assert(RRM_Policy->ran_param_val.strct != NULL && "Memory exhausted");
  RRM_Policy->ran_param_val.strct->sz_ran_param_struct = 1;
  RRM_Policy->ran_param_val.strct->ran_param_struct = calloc(1, sizeof(seq_ran_param_t));
  assert(RRM_Policy->ran_param_val.strct->ran_param_struct != NULL && "Memory exhausted");
  // RRM Policy Member List, LIST (RRM Policy -> RRM Policy Member List)
  seq_ran_param_t* RRM_Policy_Member_List = &RRM_Policy->ran_param_val.strct->ran_param_struct[0];
  RRM_Policy_Member_List->ran_param_id = RRM_Policy_Member_List_8_4_3_6;
  RRM_Policy_Member_List->ran_param_val.type = LIST_RAN_PARAMETER_VAL_TYPE;
  RRM_Policy_Member_List->ran_param_val.lst = calloc(1, sizeof(ran_param_list_t));
  assert(RRM_Policy_Member_List->ran_param_val.lst != NULL && "Memory exhausted");
  RRM_Policy_Member_List->ran_param_val.lst->sz_lst_ran_param = 1;
  RRM_Policy_Member_List->ran_param_val.lst->lst_ran_param = calloc(1, sizeof(lst_ran_param_t));
  assert(RRM_Policy_Member_List->ran_param_val.lst->lst_ran_param != NULL && "Memory exhausted");
  // RRM Policy Member, STRUCTURE (RRM Policy Member List -> RRM Policy Member)
  lst_ran_param_t* RRM_Policy_Member = &RRM_Policy_Member_List->ran_param_val.lst->lst_ran_param[0];
  // RRM_Policy_Member->ran_param_id = RRM_Policy_Member_8_4_3_6;
  RRM_Policy_Member->ran_param_struct.sz_ran_param_struct = 2;
  RRM_Policy_Member->ran_param_struct.ran_param_struct = calloc(2, sizeof(seq_ran_param_t));
  assert(RRM_Policy_Member->ran_param_struct.ran_param_struct != NULL && "Memory exhausted");
  // PLMN Identity, ELEMENT (RRM Policy Member -> PLMN Identity)
  seq_ran_param_t* PLMN_Identity = &RRM_Policy_Member->ran_param_struct.ran_param_struct[0];
  PLMN_Identity->ran_param_id = PLMN_Identity_8_4_3_6;
  PLMN_Identity->ran_param_val.type = ELEMENT_KEY_FLAG_FALSE_RAN_PARAMETER_VAL_TYPE;
  PLMN_Identity->ran_param_val.flag_false = calloc(1, sizeof(ran_parameter_value_t));
  assert(PLMN_Identity->ran_param_val.flag_false != NULL && "Memory exhausted");
  PLMN_Identity->ran_param_val.flag_false->type = OCTET_STRING_RAN_PARAMETER_VALUE;
  PLMN_Identity->ran_param_val.flag_false->octet_str_ran = cp_e2ap_plmn_to_ba(&plmnid);
  // S-NSSAI, STRUCTURE (RRM Policy Member -> S-NSSAI)
  seq_ran_param_t* S_NSSAI = &RRM_Policy_Member->ran_param_struct.ran_param_struct[1];
  S_NSSAI->ran_param_id = S_NSSAI_8_4_3_6;
  S_NSSAI->ran_param_val.type = STRUCTURE_RAN_PARAMETER_VAL_TYPE;
  S_NSSAI->ran_param_val.strct = calloc(1, sizeof(ran_param_struct_t));
  assert(S_NSSAI->ran_param_val.strct != NULL && "Memory exhausted");
  S_NSSAI->ran_param_val.strct->sz_ran_param_struct = 2;
  S_NSSAI->ran_param_val.strct->ran_param_struct = calloc(2, sizeof(seq_ran_param_t));
  // SST, ELEMENT (S-NSSAI -> SST)
  seq_ran_param_t* SST = &S_NSSAI->ran_param_val.strct->ran_param_struct[0];
  SST->ran_param_id = SST_8_4_3_6;
  SST->ran_param_val.type = ELEMENT_KEY_FLAG_FALSE_RAN_PARAMETER_VAL_TYPE;
  SST->ran_param_val.flag_false = calloc(1, sizeof(ran_parameter_value_t));
  assert(SST->ran_param_val.flag_false != NULL && "Memory exhausted");
  SST->ran_param_val.flag_false->type = OCTET_STRING_RAN_PARAMETER_VALUE;
  byte_array_t sst = cp_str_to_ba(sst_str);
  SST->ran_param_val.flag_false->octet_str_ran.len = sst.len;
  SST->ran_param_val.flag_false->octet_str_ran.buf = sst.buf;
  // SD, ELEMENT (S-NSSAI -> SD)
  seq_ran_param_t* SD = &S_NSSAI->ran_param_val.strct->ran_param_struct[1];
  SD->ran_param_id = SD_8_4_3_6;
  SD->ran_param_val.type = ELEMENT_KEY_FLAG_FALSE_RAN_PARAMETER_VAL_TYPE;
  SD->ran_param_val.flag_false = calloc(1, sizeof(ran_parameter_value_t));
  assert(SD->ran_param_val.flag_false != NULL && "Memory exhausted");
  SD->ran_param_val.flag_false->type = OCTET_STRING_RAN_PARAMETER_VALUE;
  byte_array_t sd = cp_str_to_ba(sd_str);
  SD->ran_param_val.flag_false->octet_str_ran.len = sd.len;
  SD->ran_param_val.flag_false->octet_str_ran.buf = sd.buf;
  // Max PRB Policy Ratio, ELEMENT (RRM Policy Ratio Group -> Max PRB Policy Ratio)
  seq_ran_param_t* Max_PRB_Policy_Ratio = &RRM_Policy_Ratio_Group->ran_param_struct.ran_param_struct[2];
  Max_PRB_Policy_Ratio->ran_param_id = Max_PRB_Policy_Ratio_8_4_3_6;
  Max_PRB_Policy_Ratio->ran_param_val.type = ELEMENT_KEY_FLAG_FALSE_RAN_PARAMETER_VAL_TYPE;
  Max_PRB_Policy_Ratio->ran_param_val.flag_false = calloc(1, sizeof(ran_parameter_value_t));
  assert(Max_PRB_Policy_Ratio->ran_param_val.flag_false != NULL && "Memory exhausted");
  Max_PRB_Policy_Ratio->ran_param_val.flag_false->type = INTEGER_RAN_PARAMETER_VALUE;
  Max_PRB_Policy_Ratio->ran_param_val.flag_false->int_ran = max_ratio;
  // Min PRB Policy Ratio, ELEMENT (RRM Policy Ratio Group -> Min PRB Policy Ratio)
  seq_ran_param_t* Min_PRB_Policy_Ratio = &RRM_Policy_Ratio_Group->ran_param_struct.ran_param_struct[1];
  Min_PRB_Policy_Ratio->ran_param_id = Min_PRB_Policy_Ratio_8_4_3_6;
  Min_PRB_Policy_Ratio->ran_param_val.type = ELEMENT_KEY_FLAG_FALSE_RAN_PARAMETER_VAL_TYPE;
  Min_PRB_Policy_Ratio->ran_param_val.flag_false = calloc(1, sizeof(ran_parameter_value_t));
  assert(Min_PRB_Policy_Ratio->ran_param_val.flag_false != NULL && "Memory exhausted");
  Min_PRB_Policy_Ratio->ran_param_val.flag_false->type = INTEGER_RAN_PARAMETER_VALUE;
  Min_PRB_Policy_Ratio->ran_param_val.flag_false->int_ran = min_ratio;
  // Dedicated PRB Policy Ratio, ELEMENT (RRM Policy Ratio Group -> Dedicated PRB Policy Ratio)
  seq_ran_param_t* Dedicated_PRB_Policy_Ratio = &RRM_Policy_Ratio_Group->ran_param_struct.ran_param_struct[3];
  Dedicated_PRB_Policy_Ratio->ran_param_id = Dedicated_PRB_Policy_Ratio_8_4_3_6;
  Dedicated_PRB_Policy_Ratio->ran_param_val.type = ELEMENT_KEY_FLAG_FALSE_RAN_PARAMETER_VAL_TYPE;
  Dedicated_PRB_Policy_Ratio->ran_param_val.flag_false = calloc(1, sizeof(ran_parameter_value_t));
  assert(Dedicated_PRB_Policy_Ratio->ran_param_val.flag_false != NULL && "Memory exhausted");
  Dedicated_PRB_Policy_Ratio->ran_param_val.flag_false->type = INTEGER_RAN_PARAMETER_VALUE;
  Dedicated_PRB_Policy_Ratio->ran_param_val.flag_false->int_ran = dedicated_ratio;

  return;
}

static
void gen_rrm_policy_ratio_list(seq_ran_param_t* RRM_Policy_Ratio_List)
{
  assert(num_slice > 0 && "RRM Policy Ratio List needs at least 1 slice");
  assert(num_slice <= sizeof(rrm_policy) / sizeof(rrm_policy[0]) && "num_slice exceeds rrm_policy entries");
  // seq_ran_param_t* RRM_Policy_Ratio_List =  &dst.ran_param[0];
  RRM_Policy_Ratio_List->ran_param_id = RRM_Policy_Ratio_List_8_4_3_6;
  RRM_Policy_Ratio_List->ran_param_val.type = LIST_RAN_PARAMETER_VAL_TYPE;
  RRM_Policy_Ratio_List->ran_param_val.lst = calloc(1, sizeof(ran_param_list_t));
  assert(RRM_Policy_Ratio_List->ran_param_val.lst != NULL && "Memory exhausted");
  RRM_Policy_Ratio_List->ran_param_val.lst->sz_lst_ran_param = num_slice;
  RRM_Policy_Ratio_List->ran_param_val.lst->lst_ran_param = calloc(num_slice, sizeof(lst_ran_param_t));
  assert(RRM_Policy_Ratio_List->ran_param_val.lst->lst_ran_param != NULL && "Memory exhausted");

  // Note: we consider SD is always presented
  printf("\n");
  for (size_t i = 0; i < num_slice; i++) {
    gen_rrm_policy_ratio_group(&RRM_Policy_Ratio_List->ran_param_val.lst->lst_ran_param[i], rrm_policy[i]);
    printf("Send Ctrl Msg RRM Policy Ratio Group %zu: Max %d, Min %d, Dedicated %d, PLMN %03d.%02d, SST \"%s\", SD \"%s\"\n",
          i, rrm_policy[i].rrm_policy_max_ratio, rrm_policy[i].rrm_policy_min_ratio, rrm_policy[i].rrm_policy_dedicated_ratio,
          rrm_policy[i].plmn_id.mcc, rrm_policy[i].plmn_id.mnc, rrm_policy[i].sst, rrm_policy[i].sd);
  }
  printf("\n");

  return;
}

static
e2sm_rc_ctrl_msg_frmt_1_t gen_rc_ctrl_msg_frmt_1_slice_level_PRB_quota()
{
  e2sm_rc_ctrl_msg_frmt_1_t dst = {0};

  // 8.4.3.6
  // RRM Policy Ratio List, LIST (len 1)
  // > RRM Policy Ratio Group, STRUCTURE (len 4)
  // >>  RRM Policy, STRUCTURE (len 1)
  // >>> RRM Policy Member List, LIST (len 1)
  // >>>> RRM Policy Member, STRUCTURE (len 2)
  // >>>>> PLMN Identity, ELEMENT
  // >>>>> S-NSSAI, STRUCTURE (len 2)
  // >>>>>> SST, ELEMENT
  // >>>>>> SD, ELEMENT
  // >> Min PRB Policy Ratio, ELEMENT
  // >> Max PRB Policy Ratio, ELEMENT
  // >> Dedicated PRB Policy Ratio, ELEMENT


  // No slice: empty ranP-List, i.e., no RRM Policy Ratio List
  if (num_slice == 0)
    return dst;

  // RRM Policy Ratio List, LIST
  dst.sz_ran_param = 1;
  dst.ran_param = calloc(1, sizeof(seq_ran_param_t));
  assert(dst.ran_param != NULL && "Memory exhausted");
  gen_rrm_policy_ratio_list(&dst.ran_param[0]);

  return dst;
}

static
e2sm_rc_ctrl_msg_t gen_rc_ctrl_msg(e2sm_rc_ctrl_msg_e msg_frmt)
{
  e2sm_rc_ctrl_msg_t dst = {0}; 

  if (msg_frmt == FORMAT_1_E2SM_RC_CTRL_MSG) {
    dst.format = msg_frmt;
    dst.frmt_1 = gen_rc_ctrl_msg_frmt_1_slice_level_PRB_quota();
  } else {
    assert(0!=0 && "not implemented the fill func for this ctrl msg frmt");
  }

  return dst;
}

static
ue_id_e2sm_t gen_rc_ue_id(ue_id_e2sm_e type)
{
  ue_id_e2sm_t ue_id = {0};
  if (type == GNB_UE_ID_E2SM) {
    ue_id.type = GNB_UE_ID_E2SM;
    // TODO
    ue_id.gnb.amf_ue_ngap_id = 0;
    ue_id.gnb.guami.plmn_id.mcc = 1;
    ue_id.gnb.guami.plmn_id.mnc = 1;
    ue_id.gnb.guami.plmn_id.mnc_digit_len = 2;
    ue_id.gnb.guami.amf_region_id = 0;
    ue_id.gnb.guami.amf_set_id = 0;
    ue_id.gnb.guami.amf_ptr = 0;
  } else {
    assert(0!=0 && "not supported UE ID type");
  }
  return ue_id;
}

bool filter_node(e2_node_connected_xapp_t const* n)
{
  assert(n!= NULL);
  return n->id.type == e2ap_ngran_gNB_DU || n->id.type == e2ap_ngran_gNB;
}

int main(int argc, char *argv[])
{
  assert(argc == 2 && "Configuraiton file needed!");
  (void)argc;

  //Init the xApp
  init_xapp_api(argv[1]);
  sleep(1);

  e2_node_arr_xapp_t nodes = e2_nodes_xapp_api();
  defer { free_e2_node_arr_xapp(&nodes); } ;
  assert(nodes.len > 0);
  printf("Connected E2 nodes = %d\n", nodes.len);

  //////////// 
  // START RC 
  ////////////
  
  // RC Control
  // CONTROL Service Style 2: Radio Resource Allocation Control
  // Action ID 6: Slice-level PRB quota
  // E2SM-RC Control Header Format 1
  // E2SM-RC Control Message Format 1
  rc_ctrl_req_data_t rc_ctrl = {0};
  ue_id_e2sm_t ue_id = gen_rc_ue_id(GNB_UE_ID_E2SM);

  rc_ctrl.hdr = gen_rc_ctrl_hdr(FORMAT_1_E2SM_RC_CTRL_HDR, ue_id, 2, Slice_level_PRB_quotal_7_6_3_1);
  rc_ctrl.msg = gen_rc_ctrl_msg(FORMAT_1_E2SM_RC_CTRL_MSG);

  int64_t st = time_now_us_xapp_api();
  for(size_t i =0; i < nodes.len; ++i){ 
    if (filter_node(&nodes.n[i]) == false){
      continue;
    }

    sm_ans_xapp_t ans = control_sm_xapp_api(&nodes.n[i].id, SM_RC_ID, &rc_ctrl);
    if(ans.success == false)
      printf("Error sending the control message!\n");
  }
  printf("[xApp]: Control Loop Latency: %ld us\n", time_now_us_xapp_api() - st);
  free_rc_ctrl_req_data(&rc_ctrl);

  //////////// 
  // END RC 
  //////////// 

  sleep(5);


  //Stop the xApp
  while(try_stop_xapp_api() == false)
    usleep(1000);

  printf("Test xApp run SUCCESSFULLY\n");

}

