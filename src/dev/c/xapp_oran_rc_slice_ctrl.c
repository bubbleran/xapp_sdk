/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

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
#include "../include/src/sm/rc_sm/ie/ir/ran_param_struct.h"
#include "../include/src/sm/rc_sm/ie/ir/ran_param_list.h"
#include "../include/src/util/alg_ds/ds/lock_guard/lock_guard.h"
#include "../include/src/sm/rc_sm/rc_sm_id.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

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
void gen_rrm_policy_ratio_group(lst_ran_param_t* RRM_Policy_Ratio_Group,
                                const e2ap_plmn_t plmnid,
                                const char* sst_str,
                                const char* sd_str,
                                int max_ratio,
                                int min_ratio,
                                int dedicated_ratio)
{
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
  byte_array_t sst = cp_str_to_ba(sst_str); //TODO
  SST->ran_param_val.flag_false->octet_str_ran.len = sst.len;
  SST->ran_param_val.flag_false->octet_str_ran.buf = sst.buf;
  // SD, ELEMENT (S-NSSAI -> SD)
  seq_ran_param_t* SD = &S_NSSAI->ran_param_val.strct->ran_param_struct[1];
  SD->ran_param_id = SD_8_4_3_6;
  SD->ran_param_val.type = ELEMENT_KEY_FLAG_FALSE_RAN_PARAMETER_VAL_TYPE;
  SD->ran_param_val.flag_false = calloc(1, sizeof(ran_parameter_value_t));
  assert(SD->ran_param_val.flag_false != NULL && "Memory exhausted");
  SD->ran_param_val.flag_false->type = OCTET_STRING_RAN_PARAMETER_VALUE;
  byte_array_t sd = cp_str_to_ba(sd_str); //TODO
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
  int num_slice = 3;
  // seq_ran_param_t* RRM_Policy_Ratio_List =  &dst.ran_param[0];
  RRM_Policy_Ratio_List->ran_param_id = RRM_Policy_Ratio_List_8_4_3_6;
  RRM_Policy_Ratio_List->ran_param_val.type = LIST_RAN_PARAMETER_VAL_TYPE;
  RRM_Policy_Ratio_List->ran_param_val.lst = calloc(1, sizeof(ran_param_list_t));
  assert(RRM_Policy_Ratio_List->ran_param_val.lst != NULL && "Memory exhausted");
  RRM_Policy_Ratio_List->ran_param_val.lst->sz_lst_ran_param = num_slice;
  RRM_Policy_Ratio_List->ran_param_val.lst->lst_ran_param = calloc(num_slice, sizeof(lst_ran_param_t));
  assert(RRM_Policy_Ratio_List->ran_param_val.lst->lst_ran_param != NULL && "Memory exhausted");

  e2ap_plmn_t plmnid = {
      .mcc = 1,
      .mnc = 1,
      .mnc_digit_len = 2
  };
  const char* sst_str[] = {"0", "1", "1"};
  // Note: we consider SD is always presented
  const char* sd_str[] = {"0", "0", "1"};
  assert(!strcmp(sst_str[0], "0") && !strcmp(sd_str[0], "0") && "Default slice should be set to sst = 0, sd = 0");
  int max_ratio[] = {100, 60, 80};
  int min_ratio[] = {0, 60, 40};
  int dedicated_ratio[] = {0, 30, 0};
  for (int i = 0; i < num_slice; i++) {
    gen_rrm_policy_ratio_group(&RRM_Policy_Ratio_List->ran_param_val.lst->lst_ran_param[i],
                               plmnid,
                               sst_str[i],
                               sd_str[i],
                               max_ratio[i],
                               min_ratio[i],
                               dedicated_ratio[i]);
  }

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

int main(int argc, char *argv[])
{
  fr_args_t args = init_fr_args(argc, argv);
  defer({ free_fr_args(&args); });

  //Init the xApp
  init_xapp_api(&args);
  sleep(1);

  e2_node_arr_xapp_t nodes = e2_nodes_xapp_api();
  defer({ free_e2_node_arr_xapp(&nodes); });
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
    control_sm_xapp_api(&nodes.n[i].id, SM_RC_ID, &rc_ctrl);
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

