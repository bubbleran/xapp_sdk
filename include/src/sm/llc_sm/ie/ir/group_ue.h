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

#ifndef GROUP_UE_E2SM_LLC_MIR_H
#define GROUP_UE_E2SM_LLC_MIR_H 

#include "../../../../lib/sm/ie/cell_global_id.h"
#include "../../../../lib/sm/ie/ue_id.h"

#include <stdbool.h>

// 8.3.13 
typedef struct{
  // 8.3.14
  // Optional
  cell_global_id_t* cell_global_id;

  // 8.3.8
  // [0, 65535]
  size_t sz_ue;
  ue_id_e2sm_t* ue;

} group_ue_t; 

group_ue_t cp_group_ue(group_ue_t const* src);

void free_group_ue(group_ue_t* src); 

bool eq_group_ue(group_ue_t const* m0, group_ue_t const* m1);  

#endif
