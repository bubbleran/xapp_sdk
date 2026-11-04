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

#ifndef E2SM_CCC_5QI_LST_H
#define E2SM_CCC_5QI_LST_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../../../lib/3gpp/ie/plmn_identity.h"
#include "../../../../lib/3gpp/ie/s_nssai.h"

// 9.3.19
typedef struct{
  // [1..128]
  size_t sz_lst_5qi;
  // Mandatory
  // Intger
  uint32_t* lst_5qi;

} e2sm_ccc_5qi_lst_t;

void free_e2sm_ccc_5qi_lst(e2sm_ccc_5qi_lst_t* src);

bool eq_e2sm_ccc_5qi_lst(e2sm_ccc_5qi_lst_t const* m0, e2sm_ccc_5qi_lst_t const* m1);

e2sm_ccc_5qi_lst_t cp_e2sm_ccc_5qi_lst(e2sm_ccc_5qi_lst_t const* src);

#endif

