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

#include "xapp_sdk_api.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void cb_fn(float val, uint32_t ric_req_id)
{
  printf("ric_req_id %u ue_thp_dl %f\n", ric_req_id, val);
}

int main(int argc, char** argv)
{
  init_xapp_sdk(argc, argv);

  arr_node_data_t arr = node_data_xapp_sdk(MONITOR_USE_CASE_e); 
  assert(arr.sz > 0 && "No E2 Node connected");

  global_e2_node_id_sdk_t const* node = &arr.n[0].node ;

  stop_token_t stop = e2_node_mntr_cb_xapp_sdk(node, UE_THP_DL, PERIODICITY_1_MS, cb_fn);

  sleep(1);

  printf("Stopping ric_req_id %u\n", stop.ric_req_id);
  stop_cb_xapp_sdk(stop);
  sleep(1);

  free_arr_node_data(&arr);

  return EXIT_SUCCESS;
}

