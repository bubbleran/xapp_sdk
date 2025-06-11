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
  // Step 1
  // Subscribe to RLC with a periodicity of 2 ms

  // PDCP subscribe
  // Step 2
  // Subscribe to PDCP with a periodicity of 2 ms

  // GTP subscribe
  // Step 3
  // Subscribe to GTP with a periodicity of 1000 ms

  // SLICE subscribe
  // Step 4
  // Subscribe to SLICE with a periodicity of 100 ms

  // Run for 10 seconds
  sleep(10);

  // Unsubscribe
  rm_report_sm_xapp_api(mac_hndl.u.handle);
  // Step 5
  // Unsubscribe/Remove report from previous subscriptions

  // Free the memory
  // Step 6

  return 0;
}

