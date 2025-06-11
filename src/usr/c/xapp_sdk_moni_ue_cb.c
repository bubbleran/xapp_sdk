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
  printf("RIC_REQ_ID %u UE_THP_UL %f\n", ric_req_id, val);
}

int main(int argc, char** argv)
{
  init_xapp_sdk(argc, argv);

  arr_node_data_t arr = node_data_xapp_sdk(MONITOR_USE_CASE_e); 
  assert(arr.sz > 0 && "No E2 Node connected");

  global_e2_node_id_sdk_t const* node = &arr.n[0].node ;
  ue_id_e2sm_sdk_t const* ue = &arr.n[0].ue_ho[0].ue;

  stop_token_t stop = ue_mntr_cb_xapp_sdk(node, ue, UE_THP_UL, PERIODICITY_1000_MS, cb_fn); 

  sleep(10);

  stop_cb_xapp_sdk(stop);

  free_arr_node_data(&arr);

  return EXIT_SUCCESS;
}

