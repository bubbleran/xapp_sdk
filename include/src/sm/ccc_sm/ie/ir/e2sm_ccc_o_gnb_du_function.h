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

#ifndef E2SM_CCC_O_GNB_DU_FUNCTION_H
#define E2SM_CCC_O_GNB_DU_FUNCTION_H

#include <stdint.h>
#include <stdbool.h>

// 8.8.1.1
typedef struct{
  // Integer
  // [0..(2^36 - 1)]
  uint64_t gnb_du_id:36;

  // String
  char * gnb_du_name;

  // Integer
  // [0..4294967295]
  uint32_t gnb_id;

  // Integer
  // [22..32]
  uint8_t gnb_id_len;

} e2sm_ccc_o_gnb_du_function_t;

void free_e2sm_ccc_o_gnb_du_function(e2sm_ccc_o_gnb_du_function_t* src);

bool eq_e2sm_ccc_o_gnb_du_function(e2sm_ccc_o_gnb_du_function_t const* m0, e2sm_ccc_o_gnb_du_function_t const* m1);

e2sm_ccc_o_gnb_du_function_t cp_e2sm_ccc_o_gnb_du_function(e2sm_ccc_o_gnb_du_function_t const* src);

#endif

