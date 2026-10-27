#include "../include/src/xApp/e42_xapp_api.h"
#include "../include/src/util/alg_ds/ds/lock_guard/lock_guard.h"
#include "../include/src/sm/rc_sm/rc_sm_id.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

// Delete all slices by sending a Slice-level PRB quota control with an empty
// ranP-List. E2SM-RC Control Message Format 1 allows ranP-List SIZE(0..), while
// the RRM Policy Ratio List (RANParameter-LIST) requires SIZE(1..), so the
// RRM Policy Ratio List is omitted instead of being sent empty.

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
e2sm_rc_ctrl_msg_t gen_rc_ctrl_msg(e2sm_rc_ctrl_msg_e msg_frmt)
{
  e2sm_rc_ctrl_msg_t dst = {0};

  if (msg_frmt == FORMAT_1_E2SM_RC_CTRL_MSG) {
    dst.format = msg_frmt;
    // Empty ranP-List, i.e., no RRM Policy Ratio List
    dst.frmt_1.sz_ran_param = 0;
    dst.frmt_1.ran_param = NULL;
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
  // E2SM-RC Control Message Format 1 (empty ranP-List)
  rc_ctrl_req_data_t rc_ctrl = {0};
  ue_id_e2sm_t ue_id = gen_rc_ue_id(GNB_UE_ID_E2SM);

  rc_ctrl.hdr = gen_rc_ctrl_hdr(FORMAT_1_E2SM_RC_CTRL_HDR, ue_id, 2, Slice_level_PRB_quotal_7_6_3_1);
  rc_ctrl.msg = gen_rc_ctrl_msg(FORMAT_1_E2SM_RC_CTRL_MSG);

  printf("[xApp]: Send Ctrl Msg to delete all slices\n");
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
