/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#include "../include/src/xApp/e42_xapp_api.h"
#include "../include/src/sm/agent_if/write/sm_ag_if_wr.h"
#include "../include/src/util/alg_ds/alg/defer.h"
#include "../include/src/sm/slice_sm/slice_sm_id.h"

#include <stdatomic.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <poll.h>

static uint8_t pr_slice_0_lst[9] = {90, 80, 70, 60, 50, 40, 30, 20, 10};
static bool exit_flag = false;
static void sigint_handler(int sig)
{
  printf("signal %d received !\n", sig);
  exit_flag = true;
}

_Atomic uint16_t assoc_rnti = 0;

static
void sm_cb_slice(sm_ag_if_rd_t const* rd, global_e2_node_id_t const* e2_node)
{
  assert(rd != NULL);
  assert(rd->type == INDICATION_MSG_AGENT_IF_ANS_V0);
  assert(rd->ind.type == SLICE_STATS_V0);

  int64_t now = time_now_us_xapp_api();
  printf("SLICE ind_msg latency = %ld from E2-node type %d ID %d\n",
         now - rd->ind.slice.msg.tstamp, e2_node->type, e2_node->nb_id.nb_id);
  if (rd->ind.slice.msg.ue_slice_conf.len_ue_slice > 0)
    assoc_rnti = rd->ind.slice.msg.ue_slice_conf.ues[0].rnti; 
}

static
void fill_add_mod_slice(slice_conf_t* add)
{
  assert(add != NULL);

  uint32_t dl_len_slices = 2;
  uint32_t dl_slice_id[] = {0, 1};
  char* dl_slice_label[] = {"s1", "s2"};
  slice_algorithm_e dl_type = SLICE_ALG_SM_V0_PR;
  //slice_algorithm_e dl_type = SLICE_ALG_SM_V0_NONE;
  assert(dl_type >= 0);
  char dl_name[10];
  size_t len_dl_name;
  switch (dl_type){
    case SLICE_ALG_SM_V0_PR:
      strcpy(dl_name, "PR");
      len_dl_name = strlen("PR");
      break;
    case SLICE_ALG_SM_V0_NONE:
    default:
      strcpy(dl_name, "NULL");
      len_dl_name = strlen("NULL");
      break;
  }
  
  /// SET DL PR SLICE PARAMETER///
  uint32_t pr_max[] = {pr_slice_0_lst[0], 100 - pr_slice_0_lst[0]};
  uint32_t pr_min[] = {pr_slice_0_lst[0], 100 - pr_slice_0_lst[0]};
  uint32_t pr_ded[] = {pr_slice_0_lst[0], 100 - pr_slice_0_lst[0]};

  /// DL SLICE CONTROL INFO ///
  ul_dl_slice_conf_t* add_dl = &add->dl;
  add_dl->len_sched_name = len_dl_name;
  add_dl->sched_name = malloc(strlen(dl_name));
  assert(add_dl->sched_name != NULL && "memory exhausted");
  memcpy(add_dl->sched_name, dl_name, len_dl_name);


  add_dl->len_slices = dl_len_slices;
  if (add_dl->len_slices > 0) {
    add_dl->slices = calloc(add_dl->len_slices, sizeof(fr_slice_t));
    assert(add_dl->slices != NULL && "memory exhausted");
  }

  for (uint32_t i = 0; i < add_dl->len_slices; ++i) {
    fr_slice_t* s = &add_dl->slices[i];
    s->id = dl_slice_id[i];

    const char* label = dl_slice_label[i];
    s->len_label = strlen(label);
    s->label = malloc(s->len_label);
    assert(s->label != NULL && "Memory exhausted");
    memcpy(s->label, label, s->len_label );

    const char* sched_str = "PF";
    s->len_sched = strlen(sched_str);
    s->sched = malloc(s->len_sched);
    assert(s->sched != NULL && "Memory exhausted");
    memcpy(s->sched, sched_str, s->len_sched);

    s->params.type = SLICE_ALG_SM_V0_PR;
    s->params.u.pr.max_ratio = pr_max[i];
    s->params.u.pr.min_ratio = pr_min[i];
    s->params.u.pr.dedicated_ratio = pr_ded[i];
    printf("ADD PR DL SLICE: id %u, max_ratio %d, min_ratio %d, dedicated_ratio %d\n", s->id, s->params.u.pr.max_ratio, s->params.u.pr.min_ratio, s->params.u.pr.dedicated_ratio);
  }

  uint32_t ul_len_slices = 0;
  uint32_t ul_slice_id[] = {0, 2};
  char* ul_slice_label[] = {"s1", "s2"};

  slice_algorithm_e ul_type = SLICE_ALG_SM_V0_NONE;
  assert(ul_type >= 0);
  if (ul_type != 0)
    ul_len_slices = 2;
  else
    printf("RESET UL SLICE, algo = NONE\n");

  char ul_name[10];
  size_t len_ul_name;
  switch (ul_type){
    case SLICE_ALG_SM_V0_NVS:
      strcpy(ul_name, "NVS");
      len_ul_name = strlen("NVS");
      break;
    case SLICE_ALG_SM_V0_NONE:
    default:
      strcpy(ul_name, "NULL");
      len_ul_name = strlen("NULL");
      break;
  }

  /// SET UL NVS SLICE PARAMETER///
  nvs_slice_conf_e ul_nvs_conf[] = {SLICE_SM_NVS_V0_CAPACITY, SLICE_SM_NVS_V0_CAPACITY};
  float ul_mbps_rsvd = 2;
  float ul_mbps_ref = 10.0;
  float ul_pct_rsvd = 0.5;
  /// UL SLICE CONTROL INFO ///
  ul_dl_slice_conf_t* add_ul = &add->ul;
  add_ul->len_sched_name = len_ul_name;
  add_ul->sched_name = malloc(len_ul_name);
  assert(add_ul->sched_name != NULL && "memory exhausted");
  memcpy(add_ul->sched_name, ul_name, len_ul_name);
  
  add_ul->len_slices = ul_len_slices;
  if (add_ul->len_slices > 0) {
    add_ul->slices = calloc(add_ul->len_slices, sizeof(fr_slice_t));
    assert(add_ul->slices != NULL && "memory exhausted");
  }

  for (uint32_t i = 0; i < add_ul->len_slices; ++i) {
    fr_slice_t* s = &add_ul->slices[i];
    s->id = ul_slice_id[i];

    const char* label = ul_slice_label[i];
    s->len_label = strlen(label);
    s->label = malloc(s->len_label);
    assert(s->label != NULL && "Memory exhausted");
    memcpy(s->label, label, s->len_label );

    const char* sched_str = "PF";
    s->len_sched = strlen(sched_str);
    s->sched = malloc(s->len_sched);
    assert(s->sched != NULL && "Memory exhausted");
    memcpy(s->sched, sched_str, s->len_sched);

    if (ul_type == SLICE_ALG_SM_V0_NVS) {
      s->params.type = SLICE_ALG_SM_V0_NVS;
      if (ul_nvs_conf[i] == SLICE_SM_NVS_V0_RATE) {
        s->params.u.nvs.conf = SLICE_SM_NVS_V0_RATE;
        s->params.u.nvs.u.rate.u1.mbps_required = ul_mbps_rsvd;
        s->params.u.nvs.u.rate.u2.mbps_reference = ul_mbps_ref;
        printf("ADD NVS UL SLICE: id %u, conf %d(rate), mbps_required %f, mbps_reference %f\n", s->id, s->params.u.nvs.conf, s->params.u.nvs.u.rate.u1.mbps_required, s->params.u.nvs.u.rate.u2.mbps_reference);
      } else if (ul_nvs_conf[i] == SLICE_SM_NVS_V0_CAPACITY) {
        s->params.u.nvs.conf = SLICE_SM_NVS_V0_CAPACITY;
        s->params.u.nvs.u.capacity.u.pct_reserved = ul_pct_rsvd;
        printf("ADD NVS UL SLICE: id %u, conf %d(capacity), pct_reserved %f\n", s->id, s->params.u.nvs.conf, s->params.u.nvs.u.capacity.u.pct_reserved);
      } else {
        assert(0 != 0 && "Unkown NVS conf type\n");
      }
    } else {
      assert(0 != 0 && "Unknown type encountered");
    }
  }
}

static
void fill_del_slice(del_slice_conf_t* del)
{
  assert(del != NULL);

  /// SET DL ID ///
  uint32_t dl_ids[] = {2};
  del->len_dl = sizeof(dl_ids)/sizeof(dl_ids[0]);
  if (del->len_dl > 0)
    del->dl = calloc(del->len_dl, sizeof(uint32_t));
  for (uint32_t i = 0; i < del->len_dl; i++) {
    del->dl[i] = dl_ids[i];
    printf("DEL DL SLICE: id %u\n", dl_ids[i]);
  }

  /// SET UL ID ///
  uint32_t ul_ids[] = {2};
  del->len_ul = sizeof(ul_ids)/sizeof(ul_ids[0]);
  if (del->len_ul > 0)
    del->ul = calloc(del->len_ul, sizeof(uint32_t));
  for (uint32_t i = 0; i < del->len_ul; i++){
    del->ul[i] = ul_ids[i];
    printf("DEL UL SLICE: id %u\n", ul_ids[i]);
  }

}

static
void fill_assoc_ue_slice(ue_slice_conf_t* assoc)
{
  assert(assoc != NULL);

  /// SET ASSOC UE NUMBER ///
  assoc->len_ue_slice = 1;
  if(assoc->len_ue_slice > 0){
    assoc->ues = calloc(assoc->len_ue_slice, sizeof(ue_slice_assoc_t));
    assert(assoc->ues);
  }

  /// SET RNTI ///
  assoc->ues[0].rnti = assoc_rnti;
  /// SET DL ID ///
  assoc->ues[0].dl_id = 1; // dl_id = -1 means UE will not perform DL association
  if ((int32_t)assoc->ues[0].dl_id != -1){
    printf("ASSOC DL SLICE: 0x%x, id %u\n", assoc->ues[0].rnti, assoc->ues[0].dl_id);
  }
  /// SET UL ID ///
  assoc->ues[0].ul_id = -1; // ul_id = -1 means UE will not perform UL association
  if ((int32_t)assoc->ues[0].ul_id != -1){
    printf("ASSOC UL SLICE: 0x%x, id %u\n", assoc->ues[0].rnti, assoc->ues[0].ul_id);
  }
}

static
sm_ag_if_wr_t fill_slice_sm_ctrl_req(uint16_t ran_func_id, slice_ctrl_msg_e type)
{
  assert(ran_func_id == 145);

  sm_ag_if_wr_t wr = {.type =CONTROL_SM_AG_IF_WR };

  if (ran_func_id == 145) {
    wr.ctrl.type = SLICE_CTRL_REQ_V0;
    wr.ctrl.slice_req_ctrl.hdr.dummy = 0;

    if (type == SLICE_CTRL_SM_V0_ADD) {
      /// ADD MOD ///
      wr.ctrl.slice_req_ctrl.msg.type = SLICE_CTRL_SM_V0_ADD;
      fill_add_mod_slice(&wr.ctrl.slice_req_ctrl.msg.u.add_mod_slice);
    } else if (type == SLICE_CTRL_SM_V0_DEL) {
      /// DEL ///
      wr.ctrl.slice_req_ctrl.msg.type = SLICE_CTRL_SM_V0_DEL;
      fill_del_slice(&wr.ctrl.slice_req_ctrl.msg.u.del_slice);
    } else if (type == SLICE_CTRL_SM_V0_UE_SLICE_ASSOC) {
      /// ASSOC SLICE ///
      wr.ctrl.slice_req_ctrl.msg.type = SLICE_CTRL_SM_V0_UE_SLICE_ASSOC;
      fill_assoc_ue_slice(&wr.ctrl.slice_req_ctrl.msg.u.ue_slice);
    } else {
      assert(0 != 0 && "Unknown slice ctrl type");
    }
  } else {
    assert(0 !=0 && "Unknown RAN function id");
  }
  return wr;
}

int main(int argc, char *argv[])
{
  assert(argc == 2 && "Configuraiton file needed!");

  //Init the xApp
  init_xapp_api(argv[1]);

  signal(SIGINT, sigint_handler); // we override the signal mask set in init_xapp_api()
  signal(SIGTERM, sigint_handler);
  sleep(1);

  e2_node_arr_xapp_t nodes = e2_nodes_xapp_api();
  defer({ free_e2_node_arr_xapp(&nodes); });

  assert(nodes.len > 0);
  printf("Connected E2 nodes len = %d\n", nodes.len);

  // SLICE indication
  const char* inter_t = "1000_ms";

  size_t node_idx = 0;
  for (size_t j = 0; j < nodes.n[node_idx].len_rf; ++j)
    printf("Registered ran func id = %d \n ", nodes.n[node_idx].rf[j].id);

  sm_ans_xapp_t* slice_handle = NULL;
  slice_handle = calloc(1, sizeof(sm_ans_xapp_t));
  assert(slice_handle != NULL);

  slice_handle[0] = report_sm_xapp_api(&nodes.n[node_idx].id, SM_SLICE_ID, (void*)inter_t, sm_cb_slice);
  assert(slice_handle[0].success == true);
  sleep(5);

  // Control ADD slice
  sm_ag_if_wr_t ctrl_msg_add = fill_slice_sm_ctrl_req(SM_SLICE_ID, SLICE_CTRL_SM_V0_ADD);
  defer({ free_slice_ctrl_msg(&ctrl_msg_add.ctrl.slice_req_ctrl.msg); });
  control_sm_xapp_api(&nodes.n[node_idx].id, SM_SLICE_ID, &ctrl_msg_add);

  sleep(5);

  // Control ASSOC slice
  sm_ag_if_wr_t ctrl_msg_assoc = fill_slice_sm_ctrl_req(SM_SLICE_ID, SLICE_CTRL_SM_V0_UE_SLICE_ASSOC);
  defer({ free_slice_ctrl_msg(&ctrl_msg_assoc.ctrl.slice_req_ctrl.msg); });
  control_sm_xapp_api(&nodes.n[node_idx].id, SM_SLICE_ID, &ctrl_msg_assoc);

  sleep(5);

  size_t pr_list_idx = 0;
  while(!exit_flag) {
    // Control ADD slice
    assert(ctrl_msg_add.ctrl.slice_req_ctrl.msg.type == SLICE_CTRL_SM_V0_ADD);
    pr_slice_t* pr_slice_0 = &ctrl_msg_add.ctrl.slice_req_ctrl.msg.u.add_mod_slice.dl.slices[0].params.u.pr;
    pr_slice_t* pr_slice_1 = &ctrl_msg_add.ctrl.slice_req_ctrl.msg.u.add_mod_slice.dl.slices[1].params.u.pr;

    pr_slice_0->max_ratio = pr_slice_0_lst[pr_list_idx];
    pr_slice_0->min_ratio = pr_slice_0_lst[pr_list_idx];
    pr_slice_0->dedicated_ratio = pr_slice_0_lst[pr_list_idx];
    printf("Slice 0 ratio is : %d \n", ctrl_msg_add.ctrl.slice_req_ctrl.msg.u.add_mod_slice.dl.slices[0].params.u.pr.dedicated_ratio);

    pr_slice_1->max_ratio = 100 - pr_slice_0_lst[pr_list_idx];
    pr_slice_1->min_ratio = 100 - pr_slice_0_lst[pr_list_idx];
    pr_slice_1->dedicated_ratio = 100 - pr_slice_0_lst[pr_list_idx];
    printf("Slice 1 ratio is : %d \n", ctrl_msg_add.ctrl.slice_req_ctrl.msg.u.add_mod_slice.dl.slices[1].params.u.pr.dedicated_ratio);

    if (pr_slice_0_lst[pr_list_idx] == 10){
      pr_list_idx = 0;
    } else {
      pr_list_idx += 1;
    }

    control_sm_xapp_api(&nodes.n[node_idx].id, SM_SLICE_ID, &ctrl_msg_add);
    //sleep(5);

    // Control ASSOC slice
    assert(ctrl_msg_assoc.ctrl.slice_req_ctrl.msg.type == SLICE_CTRL_SM_V0_UE_SLICE_ASSOC);
    control_sm_xapp_api(&nodes.n[node_idx].id, SM_SLICE_ID, &ctrl_msg_assoc);
    sleep(5);
  }

  // Remove the handle previously returned
  rm_report_sm_xapp_api(slice_handle[0].u.handle);

  free(slice_handle);

  //Stop the xApp
  while(try_stop_xapp_api() == false)
    poll(NULL, 0, 1000);

  printf("Test xApp run SUCCESSFULLY\n");
}

