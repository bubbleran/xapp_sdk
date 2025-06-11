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

  global_e2_node_id_sdk_t const* node = &arr.n[0].node;

  int64_t now = time_now_us_sdk();
  float const pdcp_sdu_vol_dl = e2_node_mntr_xapp_sdk(node, PDCP_SDU_VOLUME_DL); 
  printf("pdcp_sdu_vol_dl %f elapsed time %ld\n", pdcp_sdu_vol_dl, time_now_us_sdk() - now);

  free_arr_node_data(&arr);

  return EXIT_SUCCESS;
}
