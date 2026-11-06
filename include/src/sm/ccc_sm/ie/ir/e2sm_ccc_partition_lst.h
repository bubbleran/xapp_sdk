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

#ifndef E2SM_CCC_PARTITION_LST_H
#define E2SM_CCC_PARTITION_LST_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "e2sm_ccc_partition_flow_lst.h"

typedef struct {
  // Mandatory
  // Integer
  uint32_t p_offset_to_point_A;

  // Mandatory
  // Integer
  uint32_t p_number_of_rbs;

  // Mandatory
  // 9.3.20
  e2sm_ccc_partition_flow_lst_t partition_flow_lst;

} e2sm_ccc_partition_lst_item_t;

// 9.3.21
typedef struct{
  // [1..128]
  size_t sz_partition_lst_item;
  e2sm_ccc_partition_lst_item_t* partition_lst_item;

} e2sm_ccc_partition_lst_t;

void free_e2sm_ccc_partition_lst(e2sm_ccc_partition_lst_t* src);

bool eq_e2sm_ccc_partition_lst(e2sm_ccc_partition_lst_t const* m0, e2sm_ccc_partition_lst_t const* m1);

e2sm_ccc_partition_lst_t cp_e2sm_ccc_partition_lst(e2sm_ccc_partition_lst_t const* src);

#endif

