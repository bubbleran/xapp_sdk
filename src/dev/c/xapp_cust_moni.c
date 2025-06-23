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
#include "../include/src/sm/mac_sm/mac_sm_id.h"
#include "../include/src/sm/rlc_sm/rlc_sm_id.h"
#include "../include/src/sm/pdcp_sm/pdcp_sm_id.h"
#include "../include/src/sm/gtp_sm/gtp_sm_id.h"
#include "../include/src/sm/slice_sm/slice_sm_id.h"
#include "../include/src/sm/tc_sm/tc_sm_id.h"
#include "../include/src/util/conf/xapp_sub_cust_sm_conf.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

static
void sm_cb_mac(sm_ag_if_rd_t const* rd, global_e2_node_id_t const* e2_node)
{
  assert(rd != NULL);
  assert(rd->type ==INDICATION_MSG_AGENT_IF_ANS_V0);
  assert(rd->ind.type == MAC_STATS_V0);

  int64_t now = time_now_us_xapp_api();
  printf("MAC ind_msg latency = %ld from E2-node type %d ID %d\n",
         now - rd->ind.mac.msg.tstamp, e2_node->type, e2_node->nb_id.nb_id);
}

static
void sm_cb_rlc(sm_ag_if_rd_t const* rd, global_e2_node_id_t const* e2_node)
{
  assert(rd != NULL);
  assert(rd->type ==INDICATION_MSG_AGENT_IF_ANS_V0);

  assert(rd->ind.type == RLC_STATS_V0);

  int64_t now = time_now_us_xapp_api();
  printf("RLC ind_msg latency = %ld from E2-node type %d ID %d\n",
         now - rd->ind.rlc.msg.tstamp, e2_node->type, e2_node->nb_id.nb_id);
}

static
void sm_cb_pdcp(sm_ag_if_rd_t const* rd, global_e2_node_id_t const* e2_node)
{
  assert(rd != NULL);
  assert(rd->type == INDICATION_MSG_AGENT_IF_ANS_V0);

  assert(rd->ind.type == PDCP_STATS_V0);

  int64_t now = time_now_us_xapp_api();
  printf("PDCP ind_msg latency = %ld from E2-node type %d ID %d\n",
         now - rd->ind.pdcp.msg.tstamp, e2_node->type, e2_node->nb_id.nb_id);
}

static
void sm_cb_gtp(sm_ag_if_rd_t const* rd, global_e2_node_id_t const* e2_node)
{
  assert(rd != NULL);
  assert(rd->type ==INDICATION_MSG_AGENT_IF_ANS_V0);

  assert(rd->ind.type == GTP_STATS_V0);

  int64_t now = time_now_us_xapp_api();
  printf("GTP ind_msg latency = %ld from E2-node type %d ID %d\n",
         now - rd->ind.gtp.msg.tstamp, e2_node->type, e2_node->nb_id.nb_id);
}

static
void sm_cb_slice(sm_ag_if_rd_t const* rd, global_e2_node_id_t const* e2_node)
{
  assert(rd != NULL);
  assert(rd->type ==INDICATION_MSG_AGENT_IF_ANS_V0);

  assert(rd->ind.type == SLICE_STATS_V0);

  int64_t now = time_now_us_xapp_api();
  printf("SLICE ind_msg latency = %ld from E2-node type %d ID %d\n",
         now - rd->ind.slice.msg.tstamp, e2_node->type, e2_node->nb_id.nb_id);
}

static
void sm_cb_tc(sm_ag_if_rd_t const* rd, global_e2_node_id_t const* e2_node)
{
  assert(rd != NULL);
  assert(rd->type ==INDICATION_MSG_AGENT_IF_ANS_V0);
  assert(rd->ind.type == TC_STATS_V0);
  (void)e2_node;

  int64_t now = time_now_us_xapp_api();
  printf("%ld, TC ind_msg latency = %ld from E2-node type %d ID %d\n",
         time_now_us_xapp_api(), now - rd->ind.tc.msg.tstamp, e2_node->type, e2_node->nb_id.nb_id);

//  tc_ind_msg_t const* ind = &rd->ind.tc.msg;
//  for(size_t i = 0; i < ind->len_tc_stats; i++) {
//    uint16_t const rnti = ind->tc_stats[i].rnti;
//    uint16_t const ue_id = ind->tc_stats[i].ue_id;
//    uint16_t const rb_id = ind->tc_stats[i].rb_id;
//    tc_cls_t const* cls = &ind->tc_stats[i].cls;
//    if (cls->type == TC_CLS_OSI_DPI) {
//      for (size_t j = 0; j < cls->osi_dpi.len_pkt; j++) {
//        tc_cls_osi_dpi_pkt_t const *pkt = &cls->osi_dpi.pkt[j];
//        printf("Packet stats: ind msg lat %ld us from ue_id %hu, rnti %4x, rb_id %hu with pkt idx %ld, nDPI protocol %d %s, category %s, tstamp %ld\n",
//               now - rd->ind.tc.msg.tstamp, ue_id, rnti, rb_id,
//               j, pkt->l7.protocol, pkt->l7.protocol_name, pkt->l7.category_name, pkt->tstamp);
//      }
//    }
//  }
}

bool check_node_sm(char const* name, e2_node_connected_xapp_t const* n){
  assert(name != NULL);
  assert(n != NULL);

  if (!strcasecmp(name, "mac")) {
    if (n->id.type == e2ap_ngran_gNB || n->id.type == e2ap_ngran_gNB_DU || n->id.type == e2ap_ngran_eNB)
      return true;
  } else if (!strcasecmp(name, "rlc")) {
    if (n->id.type == e2ap_ngran_gNB || n->id.type == e2ap_ngran_gNB_DU || n->id.type == e2ap_ngran_eNB)
      return true;
  } else if (!strcasecmp(name, "pdcp")) {
    if (n->id.type == e2ap_ngran_gNB || n->id.type == e2ap_ngran_gNB_CU || n->id.type == e2ap_ngran_eNB)
      return true;
  } else if (!strcasecmp(name, "gtp")) {
    if (n->id.type == e2ap_ngran_gNB)
      return true;
  } else if (!strcasecmp(name, "slice")) {
    if (n->id.type == e2ap_ngran_gNB || n->id.type == e2ap_ngran_eNB)
      return true;
  }

   return false;
}

static 
const char* str_periodicity[] = {
  "1_ms", "2_ms", "5_ms", "10_ms", "100_ms", "1000_ms"
};

static
const char* convert_periodicity(size_t v)
{
  if(v == 1){
    return str_periodicity[0];     
  } else if (v == 2){
    return str_periodicity[1];     
  } else if (v == 5){
    return str_periodicity[2];     
  } else if (v == 10){
    return str_periodicity[3];     
  } else if (v == 100){
    return str_periodicity[4];     
  } else if (v == 1000){
    return str_periodicity[5];     
  } else {
    assert(0 != 0 && "Unsupported value!");
  }
  return NULL;
}


int main(int argc, char *argv[])
{
  assert(argc == 2 && "Configuration file needed");

  //Init the xApp
  init_xapp_api(argv[1]);
  sleep(1);

  e2_node_arr_xapp_t nodes = e2_nodes_xapp_api();
  defer({ free_e2_node_arr_xapp(&nodes); });

  assert(nodes.len > 0);

  printf("Connected E2 nodes = %d\n", nodes.len);

  //Init SM handler
  sm_ans_xapp_t* mac_handle = NULL;
  sm_ans_xapp_t* rlc_handle = NULL;
  sm_ans_xapp_t* pdcp_handle = NULL;
  sm_ans_xapp_t* gtp_handle = NULL;
  sm_ans_xapp_t* slice_handle = NULL;
  sm_ans_xapp_t* tc_handle = NULL;

  if(nodes.len > 0){
    mac_handle = calloc( nodes.len, sizeof(sm_ans_xapp_t) ); 
    assert(mac_handle  != NULL);
    rlc_handle = calloc( nodes.len, sizeof(sm_ans_xapp_t) ); 
    assert(rlc_handle  != NULL);
    pdcp_handle = calloc( nodes.len, sizeof(sm_ans_xapp_t) ); 
    assert(pdcp_handle  != NULL);
    gtp_handle = calloc( nodes.len, sizeof(sm_ans_xapp_t) );
    assert(gtp_handle  != NULL);
    slice_handle = calloc( nodes.len, sizeof(sm_ans_xapp_t) );
    assert(slice_handle  != NULL);
    tc_handle = calloc( nodes.len, sizeof(sm_ans_xapp_t) );
    assert(tc_handle  != NULL);
  }

  sub_cust_sm_conf_t conf = init_sub_cust_sm_conf(argv[1]);

  //Subscribe SMs for all the E2-nodes
  for (int i = 0; i < nodes.len; i++) {
    e2_node_connected_xapp_t* n = &nodes.n[i];
    for (size_t j = 0; j < n->len_rf; j++)
      printf("Registered node %d ran func id = %d \n ", i, n->rf[j].id);

    for (size_t j = 0; j < conf.sz_sub_cust_sm; j++) {
      if (check_node_sm(conf.sub_cust_sm[j].name, n) == false){
        continue;
      }

      const char* period = convert_periodicity(conf.sub_cust_sm[j].periodicity_ms);
      if (!strcasecmp(conf.sub_cust_sm[j].name, "mac")) {
        printf("xApp subscribes RAN Func ID %d in E2 node idx %d, nb_id %d\n", SM_MAC_ID, i, n->id.nb_id.nb_id);
        mac_handle[i] = report_sm_xapp_api(&nodes.n[i].id, SM_MAC_ID, (void*)period, sm_cb_mac);
        assert(mac_handle[i].success == true);

      } else if (!strcasecmp(conf.sub_cust_sm[j].name, "rlc")) {
        printf("xApp subscribes RAN Func ID %d in E2 node idx %d, nb_id %d\n", SM_RLC_ID, i, n->id.nb_id.nb_id);
        rlc_handle[i] = report_sm_xapp_api(&nodes.n[i].id, SM_RLC_ID, (void*)period, sm_cb_rlc);
        assert(rlc_handle[i].success == true);

      } else if (!strcasecmp(conf.sub_cust_sm[j].name, "pdcp")) {
        printf("xApp subscribes RAN Func ID %d in E2 node idx %d, nb_id %d\n", SM_PDCP_ID, i, n->id.nb_id.nb_id);
        pdcp_handle[i] = report_sm_xapp_api(&nodes.n[i].id, SM_PDCP_ID, (void*)period, sm_cb_pdcp);
        assert(pdcp_handle[i].success == true);

      } else if (!strcasecmp(conf.sub_cust_sm[j].name, "gtp")) {
        printf("xApp subscribes RAN Func ID %d in E2 node idx %d, nb_id %d\n", SM_GTP_ID, i, n->id.nb_id.nb_id);
        gtp_handle[i] = report_sm_xapp_api(&nodes.n[i].id, SM_GTP_ID, (void*)period, sm_cb_gtp);
        assert(gtp_handle[i].success == true);

      } else if (!strcasecmp(conf.sub_cust_sm[j].name, "slice")) {
        printf("xApp subscribes RAN Func ID %d in E2 node idx %d, nb_id %d\n", SM_SLICE_ID, i, n->id.nb_id.nb_id);
        slice_handle[i] = report_sm_xapp_api(&nodes.n[i].id, SM_SLICE_ID, (void*)period, sm_cb_slice);
        assert(slice_handle[i].success == true);

      } else if (!strcasecmp(conf.sub_cust_sm[j].name, "tc")) {
        printf("xApp subscribes RAN Func ID %d in E2 node idx %d, nb_id %d\n", SM_TC_ID, i, n->id.nb_id.nb_id);
        tc_handle[i] = report_sm_xapp_api(&nodes.n[i].id, SM_TC_ID, (void*)period, sm_cb_tc);
        assert(tc_handle[i].success == true);

      } else {
        assert(0!=0 && "unknown SM in .conf");
      }
    }

    sleep(1);
  }

  sleep(conf.runtime_sec);


  for(int i = 0; i < nodes.len; ++i) {
    e2_node_connected_xapp_t* n = &nodes.n[i];
    // Remove the handle previously returned
    for (size_t j = 0; j < conf.sz_sub_cust_sm; j++) {
      if (check_node_sm(conf.sub_cust_sm[j].name, n) == false){
        continue;
      }

      if (!strcasecmp(conf.sub_cust_sm[j].name, "mac")) {
        rm_report_sm_xapp_api(mac_handle[i].u.handle);

      } else if (!strcasecmp(conf.sub_cust_sm[j].name, "rlc")) {
        rm_report_sm_xapp_api(rlc_handle[i].u.handle);

      } else if (!strcasecmp(conf.sub_cust_sm[j].name, "pdcp")) {
        rm_report_sm_xapp_api(pdcp_handle[i].u.handle);

      } else if (!strcasecmp(conf.sub_cust_sm[j].name, "gtp")) {
        rm_report_sm_xapp_api(gtp_handle[i].u.handle);

      } else if (!strcasecmp(conf.sub_cust_sm[j].name, "slice")) {
        rm_report_sm_xapp_api(slice_handle[i].u.handle);

      } else if (!strcasecmp(conf.sub_cust_sm[j].name, "tc")) {
        rm_report_sm_xapp_api(tc_handle[i].u.handle);

      } else {
        assert(0 != 0 && "unknown SM");
      }
    }

    sleep(1);
  }

  if(nodes.len > 0){
    free(mac_handle);
    free(rlc_handle);
    free(pdcp_handle);
    free(gtp_handle);
    free(slice_handle);
    free(tc_handle);
  }

  free_sub_cust_sm_conf(&conf);

  //Stop the xApp
  while(try_stop_xapp_api() == false)
    usleep(1000);

  printf("Test xApp run SUCCESSFULLY\n");
}

