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

#ifndef E2SM_CCC_O_GNB_CU_CP_FUNCTION_H
#define E2SM_CCC_O_GNB_CU_CP_FUNCTION_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../../../lib/3gpp/ie/plmn_identity.h"
#include "g_enb_id_lst.h"
#include "g_gnb_id_lst.h"

// 8.8.1.2
typedef struct{
  // Integer
  // [0..4294967295]
  uint32_t gnb_id;

  // Integer
  // [22..32]
  uint8_t gnb_id_len;

  // String
  char* gnb_cu_name;

  // plmn_id
  // 9.3.12
  // E2SM 6.2.3.1
  e2sm_plmn_t plmn_id;

  // Conflict type between json schema and ie
  // Following CCC json schema type
  g_enb_id_lst_t x2_block_list;

  g_enb_id_lst_t x2_allow_list;

  g_gnb_id_lst_t xn_block_list;

  g_gnb_id_lst_t xn_allow_list;

  g_enb_id_lst_t x2_ho_block_list;

  g_gnb_id_lst_t xn_ho_block_list;

} e2sm_ccc_o_gnb_cu_cp_function_t;

void free_e2sm_ccc_o_gnb_cu_cp_function(e2sm_ccc_o_gnb_cu_cp_function_t* src);

bool eq_e2sm_ccc_o_gnb_cu_cp_function(e2sm_ccc_o_gnb_cu_cp_function_t const* m0, e2sm_ccc_o_gnb_cu_cp_function_t const* m1);

e2sm_ccc_o_gnb_cu_cp_function_t cp_e2sm_ccc_o_gnb_cu_cp_function(e2sm_ccc_o_gnb_cu_cp_function_t const* src);

#endif

