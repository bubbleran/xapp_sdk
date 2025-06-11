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

  arr_node_data_t arr = node_data_xapp_sdk(BWP_USE_CASE_e); 

  assert(arr.sz > 0 && "At least one gNB needed for BWP");
  global_e2_node_id_sdk_t const* node = &arr.n[0].node;

  assert(arr.n[0].sz_cell > 0 && "cell global id needed!");
  cell_global_id_sdk_t const* cell = arr.n[0].cell;

  uint32_t const start_rb = 0;
  uint32_t const number_rb = 10;

  bwp_xapp_sdk(node, cell, DL_BWP_CONTEXT_SDK, start_rb, number_rb);

  free_arr_node_data(&arr);

  return EXIT_SUCCESS;
}

