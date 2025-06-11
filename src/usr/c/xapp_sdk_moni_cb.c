/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#include "xapp_sdk_api.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void cb_fn(float val, uint32_t ric_req_id)
{
  printf("ric_req_id %u pdcp_sdu_volume_dl %f\n", ric_req_id, val);
}

int main(int argc, char** argv)
{
  init_xapp_sdk(argc, argv);

  arr_node_data_t arr = node_data_xapp_sdk(MONITOR_USE_CASE_e); 
  assert(arr.sz > 0 && "No E2 Node connected");

  global_e2_node_id_sdk_t const* node = &arr.n[0].node ;

  stop_token_t stop = e2_node_mntr_cb_xapp_sdk(node, PDCP_SDU_VOLUME_DL, PERIODICITY_1_MS, cb_fn); 

  sleep(1);

  printf("Stopping ric_req_id %u\n", stop.ric_req_id);
  stop_cb_xapp_sdk(stop);

  free_arr_node_data(&arr);

  return EXIT_SUCCESS;
}

