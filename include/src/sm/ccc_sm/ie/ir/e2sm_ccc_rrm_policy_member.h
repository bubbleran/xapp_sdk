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

#ifndef E2SM_CCC_RRM_POLICY_MEMBER_H
#define E2SM_CCC_RRM_POLICY_MEMBER_H

#include <stdint.h>
#include <stdbool.h>
#include "../../../../lib/3gpp/ie/plmn_identity.h"
#include "../../../../lib/3gpp/ie/s_nssai.h"

// 9.3.16
typedef struct{
  // Mandatory
  // 9.3.12
  // E2SM 6.2.3.1
  e2sm_plmn_t plmn_id;

  // Optional
  // 9.3.13
  // E2SM 6.2.3.12
  s_nssai_e2sm_t* s_nssai;
} e2sm_ccc_rrm_policy_member_t;

void free_e2sm_ccc_rrm_policy_member(e2sm_ccc_rrm_policy_member_t* src);

bool eq_e2sm_ccc_rrm_policy_member(e2sm_ccc_rrm_policy_member_t const* m0, e2sm_ccc_rrm_policy_member_t const* m1);

e2sm_ccc_rrm_policy_member_t cp_e2sm_ccc_rrm_policy_member(e2sm_ccc_rrm_policy_member_t const* src);

#endif

