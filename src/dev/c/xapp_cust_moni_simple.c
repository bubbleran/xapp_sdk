/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#include "../include/src/xApp/e42_xapp_api.h"
#include "../include/src/sm/mac_sm/mac_sm_id.h"
#include "../include/src/sm/rlc_sm/rlc_sm_id.h"
#include "../include/src/sm/pdcp_sm/pdcp_sm_id.h"
#include "../include/src/sm/gtp_sm/gtp_sm_id.h"
#include "../include/src/sm/slice_sm/slice_sm_id.h"

#include <stdatomic.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>


static void cb_mac(sm_ag_if_rd_t const* rd, global_e2_node_id_t const* e2_node)
{
  assert(rd != NULL);
  assert(rd->type ==INDICATION_MSG_AGENT_IF_ANS_V0);
  assert(rd->ind.type == MAC_STATS_V0);

  mac_ind_msg_t const* msg = &rd->ind.mac.msg;

  int64_t now = time_now_us_xapp_api();
  printf("MAC ind_msg latency = %ld μs from E2-node type %d ID %d\n", now - msg->tstamp, e2_node->type, e2_node->nb_id.nb_id);
}

static void cb_rlc(sm_ag_if_rd_t const* rd, global_e2_node_id_t const* e2_node)
{
  assert(rd != NULL);
  assert(rd->type ==INDICATION_MSG_AGENT_IF_ANS_V0);

  assert(rd->ind.type == RLC_STATS_V0);

  rlc_ind_msg_t const* msg = &rd->ind.rlc.msg;

  int64_t now = time_now_us_xapp_api();

  printf("RLC ind_msg latency = %ld μs from E2-node type %d ID %d\n", now - msg->tstamp, e2_node->type, e2_node->nb_id.nb_id);
}

static void cb_pdcp(sm_ag_if_rd_t const* rd, global_e2_node_id_t const* e2_node)
{
  assert(rd != NULL);
  assert(rd->type == INDICATION_MSG_AGENT_IF_ANS_V0);

  assert(rd->ind.type == PDCP_STATS_V0);

  pdcp_ind_msg_t const* msg = &rd->ind.pdcp.msg;

  int64_t now = time_now_us_xapp_api();

  printf("PDCP ind_msg latency = %ld μs from E2-node type %d ID %d\n", now - msg->tstamp, e2_node->type, e2_node->nb_id.nb_id);
}

static void cb_gtp(sm_ag_if_rd_t const* rd, global_e2_node_id_t const* e2_node)
{
  assert(rd != NULL);
  assert(rd->type ==INDICATION_MSG_AGENT_IF_ANS_V0);

  assert(rd->ind.type == GTP_STATS_V0);

  gtp_ind_msg_t const* msg = &rd->ind.gtp.msg;

  int64_t now = time_now_us_xapp_api();

  printf("GTP ind_msg latency = %ld μs from E2-node type %d ID %d\n", now - msg->tstamp, e2_node->type, e2_node->nb_id.nb_id);
}

static void cb_slice(sm_ag_if_rd_t const* rd, global_e2_node_id_t const* e2_node)
{
  assert(rd != NULL);
  assert(rd->type ==INDICATION_MSG_AGENT_IF_ANS_V0);

  assert(rd->ind.type == SLICE_STATS_V0);

  slice_ind_msg_t const* msg = &rd->ind.slice.msg;

  int64_t now = time_now_us_xapp_api();

  printf("SLICE ind_msg latency = %ld μs from E2-node type %d ID %d\n", now - msg->tstamp, e2_node->type, e2_node->nb_id.nb_id);
}

int main(int argc, char *argv[])
{
  fr_args_t args = init_fr_args(argc, argv);

  //Init the xApp
  init_xapp_api(&args);
  sleep(1);

  e2_node_arr_xapp_t nodes = e2_nodes_xapp_api();

  assert(nodes.len > 0);

  global_e2_node_id_t* e2_node = &nodes.n[0].id;

  printf("Connected E2 nodes = %d\n", nodes.len);

  // MAC subscribe
  sm_ans_xapp_t mac_hndl = report_sm_xapp_api(e2_node, SM_MAC_ID, "1_ms", cb_mac);
  assert(mac_hndl.success == true);

  // RLC subscribe
  sm_ans_xapp_t rlc_hndl = report_sm_xapp_api(e2_node, SM_RLC_ID, "2_ms", cb_rlc);
  assert(rlc_hndl.success == true);

  // PDCP subscribe
  sm_ans_xapp_t pdcp_hndl = report_sm_xapp_api(e2_node, SM_PDCP_ID, "5_ms", cb_pdcp);
  assert(pdcp_hndl.success == true);

  // GTP subscribe
  sm_ans_xapp_t gtp_hndl = report_sm_xapp_api(e2_node, SM_GTP_ID, "100_ms", cb_gtp);
  assert(gtp_hndl.success == true);

  // SLICE subscribe
  sm_ans_xapp_t slice_hndl = report_sm_xapp_api(e2_node, SM_SLICE_ID, "1000_ms", cb_slice);
  assert(slice_hndl.success == true);

  // Run for 10 seconds
  sleep(10);

  // Unsubscribe
  rm_report_sm_xapp_api(mac_hndl.u.handle);
  rm_report_sm_xapp_api(rlc_hndl.u.handle);
  rm_report_sm_xapp_api(pdcp_hndl.u.handle);
  rm_report_sm_xapp_api(gtp_hndl.u.handle);
  rm_report_sm_xapp_api(slice_hndl.u.handle);

  // Free the memory
  free_e2_node_arr_xapp(&nodes);
  free_fr_args(&args);

  return 0;
}

