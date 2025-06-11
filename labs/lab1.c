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

  // Step 1
  // Retrieve information from the nearRT-RIC
  // Don't forget to free it afterwards!!!

  // Step 2
  // Select monitoring variable
  // e.g., mntr_var_e var = PDCP_SDU_VOLUME_DL;
  mntr_var_e var = END_MNTR_VAR_E;

  // Step 3 
  // Call the function e2_node_mntr_xapp_sdk with 
  // the appropiate variables and measure the response latency
  int64_t const t0 = time_now_us_sdk();
  // Code Here!!! 
  int64_t const t1 = time_now_us_sdk();
  printf(" elapsed time %ld\n", t1 - t0);

  // Step 4
  // Free the resources

  return EXIT_SUCCESS;
}
