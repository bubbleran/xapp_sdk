/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

// Solution for lab1.c

#include "xapp_sdk_api.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
  init_xapp_sdk(argc, argv);

  // Step 1
  // Retrieve information from the nearRT-RIC
  // Don't forget to free it afterwards!!!
  arr_node_data_t arr = node_data_xapp_sdk(MONITOR_USE_CASE_e);
  assert(arr.sz > 0 && "Needed at least one E2 node to monitor");

  global_e2_node_id_sdk_t const* node = &arr.n[0].node;
  ue_id_e2sm_sdk_t const* ue = &arr.n[0].ue_ho[0].ue;

  // Step 2
  // Select monitoring variable
  mntr_var_e var = UE_THP_DL;

  // Step 3
  // Call the function ue_mntr_xapp_sdk with
  // the appropiate variables and measure the response latency
  int64_t const t0 = time_now_us_sdk();
  float const ue_thp_dl = ue_mntr_xapp_sdk(node, ue, var);
  int64_t const t1 = time_now_us_sdk();
  printf(" UE THP DL = %f, elapsed time %ld\n", ue_thp_dl, t1 - t0);

  // Step 4
  // Free the resources
  free_arr_node_data(&arr);

  return EXIT_SUCCESS;
}
