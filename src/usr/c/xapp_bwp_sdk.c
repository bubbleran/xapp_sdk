/*

Copyright (C) 2026 BubbleRAN

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see http://www.gnu.org/licenses/.
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

