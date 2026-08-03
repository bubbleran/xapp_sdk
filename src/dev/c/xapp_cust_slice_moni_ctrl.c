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
uint32_t assoc_ran_ue_id = 0;

static
void sm_cb_slice(sm_ag_if_rd_t const* rd, global_e2_node_id_t const* e2_node)
{
  assert(rd != NULL);
  assert(rd->type == INDICATION_MSG_AGENT_IF_ANS_V0);
  assert(rd->ind.type == SLICE_STATS_V0);

  int64_t now = time_now_us_xapp_api();
  printf("SLICE ind_msg latency = %ld from E2-node type %d ID %u\n",
         now - rd->ind.slice.msg.tstamp, e2_node->type, e2_node->nb_id.nb_id);

  slice_ind_msg_t const* ind_msg = &rd->ind.slice.msg;
  if (ind_msg->slice_conf.dl.len_slices == 0)
    printf("Num of DL slices is 0\n");
  for (uint32_t i = 0; i < ind_msg->slice_conf.dl.len_slices; i++) {
    printf("DL slice idx/total %d/%d, Id %d, slice sched algo %s\n",
           i,
           ind_msg->slice_conf.dl.len_slices,
           ind_msg->slice_conf.dl.slices[i].id,
           ind_msg->slice_conf.dl.sched_name);
  }
  if (ind_msg->slice_conf.ul.len_slices == 0)
    printf("Num of UL slices is 0\n");
  for (uint32_t i = 0; i < ind_msg->slice_conf.ul.len_slices; i++) {
    printf("UL slice idx/total %d/%d, Id %d, slice sched algo %s\n",
           i,
           ind_msg->slice_conf.ul.len_slices,
           ind_msg->slice_conf.ul.slices[i].id,
           ind_msg->slice_conf.ul.sched_name);
  }
  for (uint32_t i = 0; i < rd->ind.slice.msg.ue_slice_conf.len_ue_slice; i++) {
    // get the first rnti for later assoc ctrl
    if (i == 0)
      assoc_ran_ue_id = rd->ind.slice.msg.ue_slice_conf.ues[i].ran_ue_id;
    printf("UE RAN_UE_ID %u, RNTI %4x, Assoc DL Id (", rd->ind.slice.msg.ue_slice_conf.ues[i].ran_ue_id, rd->ind.slice.msg.ue_slice_conf.ues[i].rnti);
    for (uint32_t j = 0; j < rd->ind.slice.msg.ue_slice_conf.ues[i].len_dl; j++) {
      printf("%d,",rd->ind.slice.msg.ue_slice_conf.ues[i].dl_id[j]);
    }
    printf("), Assoc UL Id (");
    for (uint32_t j = 0; j < rd->ind.slice.msg.ue_slice_conf.ues[i].len_ul; j++) {
      printf("%d,",rd->ind.slice.msg.ue_slice_conf.ues[i].ul_id[j]);
    }
    printf(")\n");
  }
}

static
void fill_add_mod_slice(slice_conf_t* add, slice_algorithm_e dl_type, slice_algorithm_e ul_type)
{
  assert(add != NULL);
  assert(ul_type >= 0);
  assert(dl_type >= 0);

  uint32_t dl_len_slices = 0;
  uint32_t dl_slice_id[] = {0, 2, 5};
  char* dl_slice_label[] = {"s1", "s2", "s3"};
  /// NVS/EDF slice are only supported by OAI eNB ///
  //slice_algorithm_e dl_type = SLICE_ALG_SM_V0_STATIC;
  //slice_algorithm_e dl_type = SLICE_ALG_SM_V0_NVS;
  //slice_algorithm_e dl_type = SLICE_ALG_SM_V0_EDF;
  //slice_algorithm_e dl_type = SLICE_ALG_SM_V0_EEDF;
  //slice_algorithm_e dl_type = SLICE_ALG_SM_V0_PR;
  //slice_algorithm_e dl_type = SLICE_ALG_SM_V0_EPR;
  //slice_algorithm_e dl_type = SLICE_ALG_SM_V0_NONE;
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
    case SLICE_ALG_SM_V0_EPR:
      strcpy(dl_name, "EPR");
      len_dl_name = strlen("EPR");
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
  float mbps_rsvd = 30;
  float mbps_ref = 180.0;
  float pct_rsvd = 0.5;
  /// SET DL EDF SLICE PARAMETER///
  int deadline[] = {20, 20, 40};
  int guaranteed_prbs[] = {60, 35, 10};
  /// SET DL EEDF SLICE PARAMETER///
  eedf_slice_conf_e eedf_conf[] = {SLICE_SM_EEDF_V0_STATIC, SLICE_SM_EEDF_V0_STATIC, SLICE_SM_EEDF_V0_RATE};
  eedf_static_type_t eedf_static_type[] = {EEDF_STATIC_HARD, EEDF_STATIC_SOFT};
  int16_t eedf_reserved_prbs = 20;
  int32_t eedf_deadline = 10;
  int32_t eedf_guaranteed_rate = 40;
  /// SET DL PR SLICE PARAMETER///
  int pr_max[] = {10, 40, 100};
  int pr_min[] = {10, 20, 50};
  int pr_ded[] = {10, 20, 0};
  /// SET DL EPR SLICE PARAMETER///
  int ePR_max[] = {10, 40, 30};
  int ePR_min[] = {10, 40, 30};
  int ePR_ded[] = {10, 40, 30};
  // Check constraint
  for (size_t i = 0; i < dl_len_slices; i++) {
    if (dl_type == SLICE_ALG_SM_V0_PR)
      assert(100 >= pr_max[i] && pr_max[i] >= pr_min[i] && pr_min[i] >= pr_ded[i] && pr_ded[i] >= 0 && "Failed to meet RRM Policy Constraint");
    else if (dl_type == SLICE_ALG_SM_V0_EPR)
      assert(100 >= ePR_max[i] && ePR_max[i] >= ePR_min[i] && ePR_min[i] >= ePR_ded[i] && ePR_ded[i] >= 0 && "Failed to meet RRM Policy Constraint");
  }

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
    } else if (dl_type == SLICE_ALG_SM_V0_EPR) {
      s->params.type = SLICE_ALG_SM_V0_EPR;
      s->params.u.epr.max_ratio = ePR_max[i];
      s->params.u.epr.min_ratio = ePR_min[i];
      s->params.u.epr.dedicated_ratio = ePR_ded[i];
      printf("ADD ePR DL SLICE: id %u, max_ratio %d, min_ratio %d, dedicated_ratio %d\n", s->id, s->params.u.epr.max_ratio, s->params.u.epr.min_ratio, s->params.u.epr.dedicated_ratio);
    } else {
      assert(0 != 0 && "Unknown type encountered");
    }
  }

  uint32_t ul_len_slices = 0;
  uint32_t ul_slice_id[] = {0, 3, 7};
  char* ul_slice_label[] = {"s1", "s2", "s3"};

  //slice_algorithm_e ul_type = SLICE_ALG_SM_V0_NVS;
  //slice_algorithm_e ul_type = SLICE_ALG_SM_V0_NONE;
  if (ul_type != 0)
    ul_len_slices = 3;
  else
    printf("RESET UL SLICE, algo = NONE\n");

  char ul_name[10];
  size_t len_ul_name;
  switch (ul_type){
    case SLICE_ALG_SM_V0_NVS:
      strcpy(ul_name, "NVS");
      len_ul_name = strlen("NVS");
      break;
    case SLICE_ALG_SM_V0_EPR:
      strcpy(ul_name, "EPR");
      len_ul_name = strlen("EPR");
      break;
    case SLICE_ALG_SM_V0_NONE:
    default:
      strcpy(ul_name, "NULL");
      len_ul_name = strlen("NULL");
      break;
  }

  /// SET UL NVS SLICE PARAMETER///
  nvs_slice_conf_e ul_nvs_conf[] = {SLICE_SM_NVS_V0_RATE, SLICE_SM_NVS_V0_RATE, SLICE_SM_NVS_V0_CAPACITY};
  float ul_mbps_rsvd = 35;
  float ul_mbps_ref = 100.0;
  float ul_pct_rsvd = 0.2;
  /// SET UL EPR SLICE PARAMETER///
  int ul_ePR_max[] = {20, 40, 30};
  int ul_ePR_min[] = {20, 40, 30};
  int ul_ePR_ded[] = {20, 40, 30};
  // Check constraint
  for (size_t i = 0; i < ul_len_slices; i++) {
      assert(100 >= ul_ePR_max[i] && ul_ePR_max[i] >= ul_ePR_min[i] && ul_ePR_min[i] >= ul_ePR_ded[i] && ul_ePR_ded[i] >= 0 && "Failed to meet RRM Policy Constraint");
  }
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
    } else if (ul_type == SLICE_ALG_SM_V0_EPR) {
      s->params.type = SLICE_ALG_SM_V0_EPR;
      s->params.u.epr.max_ratio = ul_ePR_max[i];
      s->params.u.epr.min_ratio = ul_ePR_min[i];
      s->params.u.epr.dedicated_ratio = ul_ePR_ded[i];
      printf("ADD ePR UL SLICE: id %u, max_ratio %d, min_ratio %d, dedicated_ratio %d\n", s->id, s->params.u.epr.max_ratio, s->params.u.epr.min_ratio, s->params.u.epr.dedicated_ratio);
    } else {
      assert(0 != 0 && "Unknown type encountered");
    }
  }
}

static
void fill_del_slice_dl(del_slice_conf_t* del, int del_id)
{
  assert(del != NULL);

  /// SET DL ID ///
  del->len_dl = 1;
  if (del->len_dl > 0)
    del->dl = calloc(del->len_dl, sizeof(uint32_t));
  for (uint32_t i = 0; i < del->len_dl; i++) {
    del->dl[i] = del_id;
    printf("DEL DL SLICE: id %u\n", del->dl[i]);
  }
}

static
void fill_del_slice_ul(del_slice_conf_t* del, int del_id)
{
  assert(del != NULL);

  /// SET UL ID ///
  del->len_ul = 1;
  if (del->len_ul > 0)
    del->ul = calloc(del->len_ul, sizeof(uint32_t));
  for (uint32_t i = 0; i < del->len_ul; i++){
    del->ul[i] = del_id;
    printf("DEL UL SLICE: id %u\n", del->ul[i]);
  }
}

static
void fill_assoc_ue_slice_dl(ue_slice_conf_t* assoc, int ran_ue_id, int dl_id)
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
    assoc->ues[i].ran_ue_id = ran_ue_id;
    /// SET DL ID ///
    assoc->ues[i].len_dl = 1;
    assert(assoc->ues[i].len_dl == 1 && "limited by oai ran func, only do association to one slice in each ctrl msg");
    if (assoc->ues[i].len_dl > 0) {
      assoc->ues[i].dl_id = calloc(assoc->ues[i].len_dl, sizeof(uint32_t));
      assert(assoc->ues[i].dl_id != NULL && "Memory exhausted");
    }
    /// SET DL ID ///
    for (uint32_t j = 0; j < assoc->ues[i].len_dl; ++j) {
      assoc->ues[i].dl_id[j] = dl_id;
      printf("ASSOC DL SLICE: RAN UE ID %u, id %u\n", assoc->ues[i].ran_ue_id, assoc->ues[i].dl_id[j]);
    }
  }
}

static
void fill_assoc_ue_slice_ul(ue_slice_conf_t* assoc, int ran_ue_id, int ul_id)
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
    assoc->ues[i].ran_ue_id = ran_ue_id;
    /// SET UL ID ///
    assoc->ues[i].len_ul = 1;
    assert(assoc->ues[i].len_ul == 1 && "limited by oai ran func, only do association to one slice in each ctrl msg");
    if (assoc->ues[i].len_ul > 0) {
      assoc->ues[i].ul_id = calloc(assoc->ues[i].len_ul, sizeof(uint32_t));
      assert(assoc->ues[i].ul_id != NULL && "Memory exhausted");
    }
    /// SET UL ID ///
    for (uint32_t j = 0; j < assoc->ues[i].len_ul; ++j) {
      assoc->ues[i].ul_id[j] = ul_id;
      printf("ASSOC UL SLICE: RAN UE ID %u, id %u\n", assoc->ues[i].ran_ue_id, assoc->ues[i].ul_id[j]);
    }
  }
}

static
void fill_deassoc_ue_slice_dl(ue_slice_conf_t* deassoc, int ran_ue_id, int dl_id)
{
  assert(deassoc != NULL);

  /// SET ASSOC UE NUMBER ///
  deassoc->len_ue_slice = 1;
  if(deassoc->len_ue_slice > 0){
    deassoc->ues = calloc(deassoc->len_ue_slice, sizeof(ue_slice_assoc_t));
    assert(deassoc->ues);
  }

  for(uint32_t i = 0; i < deassoc->len_ue_slice; ++i) {
    /// SET RNTI ///
    deassoc->ues[i].ran_ue_id = ran_ue_id;
    /// SET DL ID ///
    deassoc->ues[i].len_dl = 1;
    assert(deassoc->ues[i].len_dl == 1 && "limited by oai ran func, only do association to one slice in each ctrl msg");
    if (deassoc->ues[i].len_dl > 0) {
      deassoc->ues[i].dl_id = calloc(deassoc->ues[i].len_dl, sizeof(uint32_t));
      assert(deassoc->ues[i].dl_id != NULL && "Memory exhausted");
    }

    for (uint32_t j = 0; j < deassoc->ues[i].len_dl; ++j) {
      deassoc->ues[i].dl_id[j] = dl_id;
      printf("DEASSOC DL SLICE: RAN UE ID %u, id %u\n", deassoc->ues[i].ran_ue_id, deassoc->ues[i].dl_id[j]);
    }
  }
}

static
void fill_deassoc_ue_slice_ul(ue_slice_conf_t* deassoc, int ran_ue_id, int ul_id)
{
  assert(deassoc != NULL);

  /// SET ASSOC UE NUMBER ///
  deassoc->len_ue_slice = 1;
  if(deassoc->len_ue_slice > 0){
    deassoc->ues = calloc(deassoc->len_ue_slice, sizeof(ue_slice_assoc_t));
    assert(deassoc->ues);
  }

  for(uint32_t i = 0; i < deassoc->len_ue_slice; ++i) {
    /// SET RNTI ///
    deassoc->ues[i].ran_ue_id = ran_ue_id;
    /// SET DL ID ///
    deassoc->ues[i].len_ul = 1;
    assert(deassoc->ues[i].len_ul == 1 && "limited by oai ran func, only do association to one slice in each ctrl msg");
    if (deassoc->ues[i].len_ul > 0) {
      deassoc->ues[i].ul_id = calloc(deassoc->ues[i].len_ul, sizeof(uint32_t));
      assert(deassoc->ues[i].ul_id != NULL && "Memory exhausted");
    }

    for (uint32_t j = 0; j < deassoc->ues[i].len_ul; ++j) {
      deassoc->ues[i].ul_id[j] = ul_id;
      printf("DEASSOC UL SLICE: RAN UE ID %u, id %u\n", deassoc->ues[i].ran_ue_id, deassoc->ues[i].ul_id[j]);
    }
  }
}

static
sm_ag_if_wr_t fill_slice_sm_ctrl_req_addmod(slice_algorithm_e dl_slice_algo, slice_algorithm_e ul_slice_algo)
{
  sm_ag_if_wr_t wr = {.type =CONTROL_SM_AG_IF_WR };

  wr.ctrl.type = SLICE_CTRL_REQ_V0;
  wr.ctrl.slice_req_ctrl.hdr.dummy = 0;

  /// ADD MOD ///
  wr.ctrl.slice_req_ctrl.msg.type = SLICE_CTRL_SM_V0_ADD;
  fill_add_mod_slice(&wr.ctrl.slice_req_ctrl.msg.u.add_mod_slice, dl_slice_algo, ul_slice_algo);
  return wr;
}


static
sm_ag_if_wr_t fill_slice_sm_ctrl_req_assoc_dl(int assoc_ran_ue_id, int assoc_dl_id)
{
  sm_ag_if_wr_t wr = {.type =CONTROL_SM_AG_IF_WR };

  wr.ctrl.type = SLICE_CTRL_REQ_V0;
  wr.ctrl.slice_req_ctrl.hdr.dummy = 0;

  /// ASSOC SLICE ///
  wr.ctrl.slice_req_ctrl.msg.type = SLICE_CTRL_SM_V0_UE_SLICE_ASSOC;
  fill_assoc_ue_slice_dl(&wr.ctrl.slice_req_ctrl.msg.u.ue_slice, assoc_ran_ue_id, assoc_dl_id);
  return wr;
}

static
sm_ag_if_wr_t fill_slice_sm_ctrl_req_assoc_ul(int assoc_ran_ue_id, int assoc_dl_id)
{
  sm_ag_if_wr_t wr = {.type =CONTROL_SM_AG_IF_WR };

  wr.ctrl.type = SLICE_CTRL_REQ_V0;
  wr.ctrl.slice_req_ctrl.hdr.dummy = 0;

  /// ASSOC SLICE ///
  wr.ctrl.slice_req_ctrl.msg.type = SLICE_CTRL_SM_V0_UE_SLICE_ASSOC;
  fill_assoc_ue_slice_ul(&wr.ctrl.slice_req_ctrl.msg.u.ue_slice, assoc_ran_ue_id, assoc_dl_id);
  return wr;
}

static
sm_ag_if_wr_t fill_slice_sm_ctrl_req_deassoc_dl(int assoc_ran_ue_id, int deassoc_dl_id)
{
  sm_ag_if_wr_t wr = {.type =CONTROL_SM_AG_IF_WR };

  wr.ctrl.type = SLICE_CTRL_REQ_V0;
  wr.ctrl.slice_req_ctrl.hdr.dummy = 0;

  /// DEASSOC SLICE ///
  wr.ctrl.slice_req_ctrl.msg.type = SLICE_CTRL_SM_V0_UE_SLICE_DEASSOC;
  fill_deassoc_ue_slice_dl(&wr.ctrl.slice_req_ctrl.msg.u.ue_slice, assoc_ran_ue_id, deassoc_dl_id);
  return wr;
}

static
sm_ag_if_wr_t fill_slice_sm_ctrl_req_deassoc_ul(int assoc_ran_ue_id, int deassoc_ul_id)
{
  sm_ag_if_wr_t wr = {.type =CONTROL_SM_AG_IF_WR };

  wr.ctrl.type = SLICE_CTRL_REQ_V0;
  wr.ctrl.slice_req_ctrl.hdr.dummy = 0;

  /// DEASSOC SLICE ///
  wr.ctrl.slice_req_ctrl.msg.type = SLICE_CTRL_SM_V0_UE_SLICE_DEASSOC;
  fill_deassoc_ue_slice_ul(&wr.ctrl.slice_req_ctrl.msg.u.ue_slice, assoc_ran_ue_id, deassoc_ul_id);
  return wr;
}

static
sm_ag_if_wr_t fill_slice_sm_ctrl_req_del_dl(int del_id)
{
  sm_ag_if_wr_t wr = {.type =CONTROL_SM_AG_IF_WR };

  wr.ctrl.type = SLICE_CTRL_REQ_V0;
  wr.ctrl.slice_req_ctrl.hdr.dummy = 0;

  /// DEL ///
  wr.ctrl.slice_req_ctrl.msg.type = SLICE_CTRL_SM_V0_DEL;
  fill_del_slice_dl(&wr.ctrl.slice_req_ctrl.msg.u.del_slice, del_id);
  return wr;
}

static
sm_ag_if_wr_t fill_slice_sm_ctrl_req_del_ul(int del_id)
{
  sm_ag_if_wr_t wr = {.type =CONTROL_SM_AG_IF_WR };

  wr.ctrl.type = SLICE_CTRL_REQ_V0;
  wr.ctrl.slice_req_ctrl.hdr.dummy = 0;

  /// DEL ///
  wr.ctrl.slice_req_ctrl.msg.type = SLICE_CTRL_SM_V0_DEL;
  fill_del_slice_ul(&wr.ctrl.slice_req_ctrl.msg.u.del_slice, del_id);
  return wr;
}

bool filter_node(e2_node_connected_xapp_t const* n)
{
  assert(n!= NULL);
  return n->id.type == e2ap_ngran_gNB_DU || n->id.type == e2ap_ngran_gNB;
}

slice_algorithm_e dl_type[] = {
  SLICE_ALG_SM_V0_NVS,
  SLICE_ALG_SM_V0_EDF,
  SLICE_ALG_SM_V0_EEDF,
  SLICE_ALG_SM_V0_PR,
  SLICE_ALG_SM_V0_EPR,
  SLICE_ALG_SM_V0_NONE
};

slice_algorithm_e ul_type[] = {
  SLICE_ALG_SM_V0_EPR,
  SLICE_ALG_SM_V0_NVS,
  SLICE_ALG_SM_V0_NONE
};

int main(int argc, char *argv[])
{
  assert(argc == 2 && "Configuraiton file needed!");

  //Init the xApp
  init_xapp_api(argv[1]);
  void (*fp_rc)(int) = signal(SIGINT, sigint_handler); // we override the signal mask set in init_xapp_ap  
  assert(fp_rc != SIG_ERR);
  fp_rc = signal(SIGTERM, sigint_handler);
  assert(fp_rc != SIG_ERR);
  sleep(1);

  e2_node_arr_xapp_t nodes = e2_nodes_xapp_api();
  defer({ free_e2_node_arr_xapp(&nodes); });

  assert(nodes.len > 0);
  printf("Connected E2 nodes len = %d\n", nodes.len);

  // SLICE indication
  const char* inter_t = "1000_ms";
  for(size_t i = 0; i < nodes.len; ++i) {
    e2_node_connected_xapp_t *n = &nodes.n[i];
    if (filter_node(n) == false){
      continue;
    }
    for (size_t j = 0; j < n->len_rf; ++j)
      printf("Registered ran func id = %d \n ", n->rf[j].id);
  }

  // Assuming this xApp only support 1 node
  int nidx = 0;
  sm_ans_xapp_t slice_handle = report_sm_xapp_api(&nodes.n[nidx].id, SM_SLICE_ID, (void*)inter_t, sm_cb_slice);
  assert(slice_handle.success == true);
  sleep(2);

  // Downlink slice with diff algos and uplink slice is None
  int num_dl_type = sizeof(dl_type) / sizeof(dl_type[0]);
  for (int i = 0; i < num_dl_type; i++) {
    // Control ADD slice
    sm_ag_if_wr_t ctrl_msg_add = fill_slice_sm_ctrl_req_addmod(dl_type[i], SLICE_ALG_SM_V0_NONE);
    control_sm_xapp_api(&nodes.n[nidx].id, SM_SLICE_ID, &ctrl_msg_add);
    free_slice_ctrl_msg(&ctrl_msg_add.ctrl.slice_req_ctrl.msg);
    sleep(10);

    int assoc_ran_ue_id = 1;
    int assoc_dl_id = 2;
    // Control ASSOC slice
    sm_ag_if_wr_t ctrl_msg_assoc = fill_slice_sm_ctrl_req_assoc_dl(assoc_ran_ue_id, assoc_dl_id);
    control_sm_xapp_api(&nodes.n[nidx].id, SM_SLICE_ID, &ctrl_msg_assoc);
    free_slice_ctrl_msg(&ctrl_msg_assoc.ctrl.slice_req_ctrl.msg);
    sleep(5);

    assoc_dl_id = 5;
    // Control ASSOC slice
    sm_ag_if_wr_t ctrl_msg_assoc2 = fill_slice_sm_ctrl_req_assoc_dl(assoc_ran_ue_id, assoc_dl_id);
    control_sm_xapp_api(&nodes.n[nidx].id, SM_SLICE_ID, &ctrl_msg_assoc2);
    free_slice_ctrl_msg(&ctrl_msg_assoc2.ctrl.slice_req_ctrl.msg);
    sleep(5);

    int deassoc_dl_id = 2;
    // Control DEASSOC slice
    sm_ag_if_wr_t ctrl_msg_deassoc = fill_slice_sm_ctrl_req_deassoc_dl(assoc_ran_ue_id, deassoc_dl_id);
    control_sm_xapp_api(&nodes.n[nidx].id, SM_SLICE_ID, &ctrl_msg_deassoc);
    free_slice_ctrl_msg(&ctrl_msg_deassoc.ctrl.slice_req_ctrl.msg);
    sleep(5);

    int del_id = 5;
    // Control DEL slice
    sm_ag_if_wr_t ctrl_msg_del = fill_slice_sm_ctrl_req_del_dl(del_id);
    control_sm_xapp_api(&nodes.n[nidx].id, SM_SLICE_ID, &ctrl_msg_del);
    free_slice_ctrl_msg(&ctrl_msg_del.ctrl.slice_req_ctrl.msg);
    sleep(5);
  }


  // Uplink slice with diff algos and downlink slice is None
  int num_ul_type = sizeof(ul_type) / sizeof(ul_type[0]);
  for (int i = 0; i < num_ul_type; i++) {
    // Control ADD slice
    sm_ag_if_wr_t ctrl_msg_add = fill_slice_sm_ctrl_req_addmod(SLICE_ALG_SM_V0_NONE, ul_type[i]);
    control_sm_xapp_api(&nodes.n[nidx].id, SM_SLICE_ID, &ctrl_msg_add);
    free_slice_ctrl_msg(&ctrl_msg_add.ctrl.slice_req_ctrl.msg);
    sleep(5);

    int assoc_ran_ue_id = 1;
    int assoc_ul_id = 3;
    // Control ASSOC slice
    sm_ag_if_wr_t ctrl_msg_assoc = fill_slice_sm_ctrl_req_assoc_ul(assoc_ran_ue_id, assoc_ul_id);
    control_sm_xapp_api(&nodes.n[nidx].id, SM_SLICE_ID, &ctrl_msg_assoc);
    free_slice_ctrl_msg(&ctrl_msg_assoc.ctrl.slice_req_ctrl.msg);
    sleep(5);

    assoc_ul_id = 7;
    // Control ASSOC slice
    sm_ag_if_wr_t ctrl_msg_assoc2 = fill_slice_sm_ctrl_req_assoc_ul(assoc_ran_ue_id, assoc_ul_id);
    control_sm_xapp_api(&nodes.n[nidx].id, SM_SLICE_ID, &ctrl_msg_assoc2);
    free_slice_ctrl_msg(&ctrl_msg_assoc2.ctrl.slice_req_ctrl.msg);
    sleep(5);

    int deassoc_dl_id = 3;
    // Control DEASSOC slice
    sm_ag_if_wr_t ctrl_msg_deassoc = fill_slice_sm_ctrl_req_deassoc_ul(assoc_ran_ue_id, deassoc_dl_id);
    control_sm_xapp_api(&nodes.n[nidx].id, SM_SLICE_ID, &ctrl_msg_deassoc);
    free_slice_ctrl_msg(&ctrl_msg_deassoc.ctrl.slice_req_ctrl.msg);
    sleep(5);

    int del_id = 7;
    // Control DEL slice
    sm_ag_if_wr_t ctrl_msg_del = fill_slice_sm_ctrl_req_del_ul(del_id);
    control_sm_xapp_api(&nodes.n[nidx].id, SM_SLICE_ID, &ctrl_msg_del);
    free_slice_ctrl_msg(&ctrl_msg_del.ctrl.slice_req_ctrl.msg);
    sleep(5);
  }


  // Remove the handle previously returned
  rm_report_sm_xapp_api(slice_handle.u.handle);
  sleep(1);

  //Stop the xApp
  while(try_stop_xapp_api() == false)
    usleep(1000);

  printf("Test xApp run SUCCESSFULLY\n");
}


