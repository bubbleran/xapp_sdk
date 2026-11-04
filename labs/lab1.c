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

int main(int argc, char** argv)
{
  init_xapp_sdk(argc, argv);

  // Step 1
  // Retrieve information from the nearRT-RIC
  // Don't forget to free it afterwards!!!

  // Possible naming convention! Feel free to use it or discard it!
  // global_e2_node_id_sdk_t const* node = &arr.n[0].node ;
  // ue_id_e2sm_sdk_t const* ue = &arr.n[0].ue_ho[0].ue;

  // Step 2
  // Select monitoring variable
  // e.g., mntr_var_e var = UE_THP_DL;
  mntr_var_e var = END_MNTR_VAR_E;

  // Step 3 
  // Call the function ue_mntr_xapp_sdk with 
  // the appropiate variables and measure the response latency
  int64_t const t0 = time_now_us_sdk();
  // Code Here!!! 
  int64_t const t1 = time_now_us_sdk();
  printf(" elapsed time %ld\n", t1 - t0);

  // Step 4
  // Free the resources

  return EXIT_SUCCESS;
}
