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
#include <string.h>

#include "xapp_sdk_api.h"

int find_idx_gnb_or_du(arr_node_data_t const* arr)
{
  assert(arr != NULL);
  for(size_t i = 0; i < arr->sz; ++i){
   global_e2_node_id_sdk_t* n = &arr->n[i].node;
   if(n->type == e2ap_ngran_gNB_DU_SDK || n->type == e2ap_ngran_gNB_SDK){
    return i;
   }
  }
  return -1;
}

int main(int argc, char** argv)
{
  init_xapp_sdk(argc, argv);

  arr_node_data_t arr = node_data_xapp_sdk(SLICE_USE_CASE_e);

  assert(arr.sz > 0 && "At least one gNB needed for slicing");

  int const idx = find_idx_gnb_or_du(&arr);
  assert(idx > -1 && "Not a gNB or DU found!");

  global_e2_node_id_sdk_t const* node = &arr.n[idx].node; 

  char const sst[] = "1";
  char const sd[] = "";

  int const dedicated_prb = 10;
  slice_xapp_sdk(node, sst, sd, dedicated_prb);

  free_arr_node_data(&arr);

  return EXIT_SUCCESS;
}

