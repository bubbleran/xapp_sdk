/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#include <assert.h>
#include <stdlib.h>

#include "xapp_sdk_api.h"

int main(int argc, char** argv)
{
  init_xapp_sdk(argc, argv);

  arr_node_data_t arr = node_data_xapp_sdk(SLICE_USE_CASE_e);

  assert(arr.sz > 0 && "At least one gNB needed for slicing");
  global_e2_node_id_sdk_t const* node = &arr.n[0].node;

  char* const sst = "0";
  char* const sd = "1";
  int const dedicated_prb = 10;
  slice_xapp_sdk(node, sst, sd, dedicated_prb);

  free_arr_node_data(&arr);

  return EXIT_SUCCESS;
}

