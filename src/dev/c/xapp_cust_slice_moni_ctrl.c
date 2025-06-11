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
#include "../include/src/sm/agent_if/write/sm_ag_if_wr.h"
#include "../include/src/util/alg_ds/alg/defer.h"
#include "../include/src/sm/slice_sm/slice_sm_id.h"

#include <stdatomic.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

static bool exit_flag = false;
static void sigint_handler(int sig)
{
  printf("signal %d received !\n", sig);
  exit_flag = true;
}

_Atomic
uint16_t assoc_rnti = 0;

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
    assoc_rnti = rd->ind.slice.msg.ue_slice_conf.ues->rnti; // TODO: assign the rnti after get the indication msg
}

static
void fill_add_mod_slice(slice_conf_t* add)
{
  assert(add != NULL);

  uint32_t dl_len_slices = 0;
  uint32_t dl_slice_id[] = {0, 2, 5};
  char* dl_slice_label[] = {"s1", "s2", "s3"};
  /// NVS/EDF slice are only supported by OAI eNB ///
  //slice_algorithm_e dl_type = SLICE_ALG_SM_V0_STATIC;
  //slice_algorithm_e dl_type = SLICE_ALG_SM_V0_NVS;
  //slice_algorithm_e dl_type = SLICE_ALG_SM_V0_EDF;
  //slice_algorithm_e dl_type = SLICE_ALG_SM_V0_EEDF;
  slice_algorithm_e dl_type = SLICE_ALG_SM_V0_PR;
  //slice_algorithm_e dl_type = SLICE_ALG_SM_V0_NONE;
  assert(dl_type >= 0);
  if (dl_type != 0)
    dl_len_slices = 3;
  else
    printf("RESET DL SLICE, algo = NONE\n");

  char dl_name[10];
  size_t len_dl_name;
  switch (dl_type){
    case SLICE_ALG_SM_V0_STATIC:
      strcpy(dl_name, "STATIC");
      len_dl_name = strlen("STATIC");
      break;
    case SLICE_ALG_SM_V0_NVS:
      strcpy(dl_name, "NVS");
      len_dl_name = strlen("NVS");
      break;
    case SLICE_ALG_SM_V0_EDF:
      strcpy(dl_name, "EDF");
      len_dl_name = strlen("EDF");
      break;
    case SLICE_ALG_SM_V0_EEDF:
      strcpy(dl_name, "EEDF");
      len_dl_name = strlen("EEDF");
      break;
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
  
  /// SET DL STATIC SLICE PARAMETER ///
  uint32_t set_st_low_high_p[] = {0, 3, 4, 7, 8, 12};
  /// SET DL NVS SLICE PARAMETER///
  nvs_slice_conf_e nvs_conf[] = {SLICE_SM_NVS_V0_RATE, SLICE_SM_NVS_V0_CAPACITY, SLICE_SM_NVS_V0_RATE};
  float mbps_rsvd = 2;
  float mbps_ref = 10.0;
  float pct_rsvd = 0.5;
  /// SET DL EDF SLICE PARAMETER///
  int deadline[] = {20, 20, 40};
  int guaranteed_prbs[] = {10, 4, 10};
  /// SET DL EEDF SLICE PARAMETER///
  eedf_slice_conf_e eedf_conf[] = {SLICE_SM_EEDF_V0_STATIC, SLICE_SM_EEDF_V0_STATIC, SLICE_SM_EEDF_V0_RATE};
  eedf_static_type_t eedf_static_type[] = {EEDF_STATIC_HARD, EEDF_STATIC_SOFT};
  int16_t eedf_reserved_prbs = 20;
  int32_t eedf_deadline = 10;
  int32_t eedf_guaranteed_rate = 40;
  /// SET DL PR SLICE PARAMETER///
  int pr_max[] = {20, 40, 100};
  int pr_min[] = {20, 20, 0};
  int pr_ded[] = {0, 20, 0};

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

    if (dl_type == SLICE_ALG_SM_V0_STATIC) {
      s->params.type = SLICE_ALG_SM_V0_STATIC;
      s->params.u.sta.pos_high = set_st_low_high_p[i * 2 + 1];
      s->params.u.sta.pos_low = set_st_low_high_p[i * 2];
      printf("ADD STATIC DL SLICE: id %u, pos_low %u, pos_high %u\n", s->id, s->params.u.sta.pos_low, s->params.u.sta.pos_high);
    } else if (dl_type == SLICE_ALG_SM_V0_NVS) {
      s->params.type = SLICE_ALG_SM_V0_NVS;
      if (nvs_conf[i] == SLICE_SM_NVS_V0_RATE) {
        s->params.u.nvs.conf = SLICE_SM_NVS_V0_RATE;
        s->params.u.nvs.u.rate.u1.mbps_required = mbps_rsvd;
        s->params.u.nvs.u.rate.u2.mbps_reference = mbps_ref;
        printf("ADD NVS DL SLICE: id %u, conf %d(rate), mbps_required %f, mbps_reference %f\n", s->id, s->params.u.nvs.conf, s->params.u.nvs.u.rate.u1.mbps_required, s->params.u.nvs.u.rate.u2.mbps_reference);
      } else if (nvs_conf[i] == SLICE_SM_NVS_V0_CAPACITY) {
        s->params.u.nvs.conf = SLICE_SM_NVS_V0_CAPACITY;
        s->params.u.nvs.u.capacity.u.pct_reserved = pct_rsvd;
        printf("ADD NVS DL SLICE: id %u, conf %d(capacity), pct_reserved %f\n", s->id, s->params.u.nvs.conf, s->params.u.nvs.u.capacity.u.pct_reserved);
      } else {
        assert(0 != 0 && "Unkown NVS conf type\n");
      }
    } else if (dl_type == SLICE_ALG_SM_V0_EDF) {
      s->params.type = SLICE_ALG_SM_V0_EDF;
      s->params.u.edf.deadline = deadline[i];
      s->params.u.edf.guaranteed_prbs = guaranteed_prbs[i];
      printf("ADD EDF DL SLICE: id %u, deadline %d, guaranteed_prbs %d\n", s->id, s->params.u.edf.deadline, s->params.u.edf.guaranteed_prbs);
    } else if (dl_type == SLICE_ALG_SM_V0_EEDF) {
      s->params.type = SLICE_ALG_SM_V0_EEDF;
      if (eedf_conf[i] == SLICE_SM_EEDF_V0_STATIC){
        s->params.u.eedf.conf = SLICE_SM_EEDF_V0_STATIC;
        s->params.u.eedf.u.fixed.reserved_prbs = eedf_reserved_prbs;
        if (eedf_static_type[i] == EEDF_STATIC_HARD){
          s->params.u.eedf.u.fixed.reserved_type = EEDF_STATIC_HARD;
          printf("ADD EEDF DL SLICE: id %u, conf STATIC, type HARD, reserved_prbs %d\n", s->id, s->params.u.eedf.u.fixed.reserved_prbs);
        }else if (eedf_static_type[i] == EEDF_STATIC_SOFT){
          s->params.u.eedf.u.fixed.reserved_type = EEDF_STATIC_SOFT;
          printf("ADD EEDF DL SLICE: id %u, conf STATIC, type SOFT, reserved_prbs %d\n", s->id, s->params.u.eedf.u.fixed.reserved_prbs);
        } else {
          assert(0 != 0 && "Unkown EEDF static type\n");
        }
      } else if (eedf_conf[i] == SLICE_SM_EEDF_V0_RATE){
        s->params.u.eedf.conf = SLICE_SM_EEDF_V0_RATE;
        s->params.u.eedf.u.rate.guaranteed_rate = eedf_guaranteed_rate;
        s->params.u.eedf.u.rate.deadline = eedf_deadline;
        printf("ADD EEDF DL SLICE: id %u, deadline %d, guaranteed_rate %d\n", s->id, s->params.u.eedf.u.rate.deadline, s->params.u.eedf.u.rate.guaranteed_rate);
      } else {
        assert(0 != 0 && "Unkown EEDF conf type\n");
      }
    } else if (dl_type == SLICE_ALG_SM_V0_PR) {
      s->params.type = SLICE_ALG_SM_V0_PR;
      s->params.u.pr.max_ratio = pr_max[i];
      s->params.u.pr.min_ratio = pr_min[i];
      s->params.u.pr.dedicated_ratio = pr_ded[i];
      printf("ADD PR DL SLICE: id %u, max_ratio %d, min_ratio %d, dedicated_ratio %d\n", s->id, s->params.u.pr.max_ratio, s->params.u.pr.min_ratio, s->params.u.pr.dedicated_ratio);
    } else {
      assert(0 != 0 && "Unknown type encountered");
    }
  }

  uint32_t ul_len_slices = 0;
  uint32_t ul_slice_id[] = {0, 2};
  char* ul_slice_label[] = {"s1", "s2"};

  slice_algorithm_e ul_type = SLICE_ALG_SM_V0_NVS;
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

  for(uint32_t i = 0; i < assoc->len_ue_slice; ++i) {
    /// SET RNTI ///
    assoc->ues[i].rnti = assoc_rnti; // TODO: get rnti from sm_cb_slice()
    /// SET DL ID ///
    assoc->ues[i].dl_id = 2; // dl_id = -1 means UE will not perform DL association
    if ((int32_t)assoc->ues[i].dl_id != -1){
      printf("ASSOC DL SLICE: 0x%x, id %u\n", assoc->ues[i].rnti, assoc->ues[i].dl_id);
    }
    /// SET UL ID ///
    assoc->ues[i].ul_id = 2; // ul_id = -1 means UE will not perform UL association
    if ((int32_t)assoc->ues[i].ul_id != -1){
      printf("ASSOC UL SLICE: 0x%x, id %u\n", assoc->ues[i].rnti, assoc->ues[i].ul_id); 
    }
    
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
  fr_args_t args = init_fr_args(argc, argv);
  defer({ free_fr_args(&args); });

  //Init the xApp
  init_xapp_api(&args);
  signal(SIGINT, sigint_handler); // we override the signal mask set in init_xapp_api()
  signal(SIGTERM, sigint_handler);
  sleep(1);

  e2_node_arr_xapp_t nodes = e2_nodes_xapp_api();
  defer({ free_e2_node_arr_xapp(&nodes); });

  assert(nodes.len > 0);
  printf("Connected E2 nodes len = %d\n", nodes.len);

  // SLICE indication
  const char* inter_t = "5_ms";
  sm_ans_xapp_t* slice_handle = NULL;

  if(nodes.len > 0){
    slice_handle = calloc(nodes.len, sizeof(sm_ans_xapp_t) );
    assert(slice_handle != NULL);
  }

  for(size_t i = 0; i < nodes.len; ++i) {
    e2_node_connected_xapp_t *n = &nodes.n[i];
    for (size_t j = 0; j < n->len_rf; ++j)
      printf("Registered ran func id = %d \n ", n->rf[j].id);

    slice_handle[i] = report_sm_xapp_api(&nodes.n[i].id, SM_SLICE_ID, (void*)inter_t, sm_cb_slice);
    assert(slice_handle[i].success == true);
    sleep(2);

    while(assoc_rnti == 0) {
      sleep(1);
    }

    // Control ADD slice
    sm_ag_if_wr_t ctrl_msg_add = fill_slice_sm_ctrl_req(SM_SLICE_ID, SLICE_CTRL_SM_V0_ADD);
    control_sm_xapp_api(&nodes.n[i].id, SM_SLICE_ID, &ctrl_msg_add);
    free_slice_ctrl_msg(&ctrl_msg_add.ctrl.slice_req_ctrl.msg);

    sleep(5);

    // Control ASSOC slice
    sm_ag_if_wr_t ctrl_msg_assoc = fill_slice_sm_ctrl_req(SM_SLICE_ID, SLICE_CTRL_SM_V0_UE_SLICE_ASSOC);
    control_sm_xapp_api(&nodes.n[i].id, SM_SLICE_ID, &ctrl_msg_assoc);
    free_slice_ctrl_msg(&ctrl_msg_assoc.ctrl.slice_req_ctrl.msg);

    sleep(5);

    // Control DEL slice
    sm_ag_if_wr_t ctrl_msg_del = fill_slice_sm_ctrl_req(SM_SLICE_ID, SLICE_CTRL_SM_V0_DEL);
    control_sm_xapp_api(&nodes.n[i].id, SM_SLICE_ID, &ctrl_msg_del);
    free_slice_ctrl_msg(&ctrl_msg_del.ctrl.slice_req_ctrl.msg);

    sleep(5);
  }

  while(!exit_flag) {
    sleep(1);
  }
  // Remove the handle previously returned
  for(int i = 0; i < nodes.len; ++i)
    rm_report_sm_xapp_api(slice_handle[i].u.handle);

  if(nodes.len > 0){
    free(slice_handle);
  }

  sleep(1);

  //Stop the xApp
  while(try_stop_xapp_api() == false)
    usleep(1000);

  printf("Test xApp run SUCCESSFULLY\n");
}


