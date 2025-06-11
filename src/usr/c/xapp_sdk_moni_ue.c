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

int main(int argc, char** argv)
{
  init_xapp_sdk(argc, argv);

  arr_node_data_t arr = node_data_xapp_sdk(MONITOR_USE_CASE_e); 

  assert(arr.sz > 0 && "No E2 Node connected");
  assert(arr.n[0]. sz_ue > 0 && "No UEs connected to first E2 Node");

  global_e2_node_id_sdk_t const* node = &arr.n[0].node ;
  ue_id_e2sm_sdk_t const* ue = &arr.n[0].ue_ho[0].ue;
 
  float thp_dl = ue_mntr_xapp_sdk(node, ue,  UE_THP_DL); 
  printf("UE throughput in downlink %f\n", thp_dl);

  free_arr_node_data (&arr);

  return EXIT_SUCCESS;
}

