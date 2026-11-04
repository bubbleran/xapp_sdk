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

#ifndef E2SM_CCC_O_RRM_POLICY_RATIO_H
#define E2SM_CCC_O_RRM_POLICY_RATIO_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "e2sm_ccc_rrm_policy_member.h"

typedef enum {
  PRB_UL_RESOURCE_TYPE = 1,
  PRB_DL_RESOURCE_TYPE,
  DRB_RESOURCE_TYPE,
  RRC_RESOURCE_TYPE,

  END_RESOURCE_TYPE,
} resource_type_e;

// 8.8.1.4
typedef struct{
  resource_type_e resource_type;

  // plMNInfoList
  // 9.3.15
  // [1..65536]
  size_t sz_rrm_policy_member_lst;
  e2sm_ccc_rrm_policy_member_t* rrm_policy_member_lst;

  // Integer
  // [0..100]
  uint8_t rrm_policy_max_ratio;

  // Integer
  // [0..100]
  uint8_t rrm_policy_min_ratio;

  // Integer
  // [0..100]
  uint8_t rrm_policy_dedicated_ratio;

} e2sm_ccc_o_rrm_policy_ratio_t;

void free_e2sm_ccc_o_rrm_policy_ratio(e2sm_ccc_o_rrm_policy_ratio_t* src);

bool eq_e2sm_ccc_o_rrm_policy_ratio(e2sm_ccc_o_rrm_policy_ratio_t const* m0, e2sm_ccc_o_rrm_policy_ratio_t const* m1);

e2sm_ccc_o_rrm_policy_ratio_t cp_e2sm_ccc_o_rrm_policy_ratio(e2sm_ccc_o_rrm_policy_ratio_t const* src);

#endif

