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

#ifndef E2SM_CCC_O_NR_CELL_CU_H
#define E2SM_CCC_O_NR_CELL_CU_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "e2sm_ccc_plmn_info.h"

// 8.8.2.1
typedef struct{
  // Integer
  uint32_t cell_local_id;

  // plMNInfoList
  // 9.3.15
  // [1..65536]
  size_t sz_plmn_info_lst;
  e2sm_ccc_plmn_info_t* plmn_info_lst;

} e2sm_ccc_o_nr_cell_cu_t;

void free_e2sm_ccc_o_nr_cell_cu(e2sm_ccc_o_nr_cell_cu_t* src);

bool eq_e2sm_ccc_o_nr_cell_cu(e2sm_ccc_o_nr_cell_cu_t const* m0, e2sm_ccc_o_nr_cell_cu_t const* m1);

e2sm_ccc_o_nr_cell_cu_t cp_e2sm_ccc_o_nr_cell_cu(e2sm_ccc_o_nr_cell_cu_t const* src);

#endif

