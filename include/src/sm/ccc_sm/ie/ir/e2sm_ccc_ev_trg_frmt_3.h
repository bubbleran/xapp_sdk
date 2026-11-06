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

#ifndef E2SM_CCC_EV_TRG_FRMT_3
#define E2SM_CCC_EV_TRG_FRMT_3

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

// 9.2.1.1.3
typedef struct{
  // Mandatory
  uint32_t period; // [1, 4294967295] reporting period in milliseconds
} e2sm_ccc_ev_trg_frmt_3_t;

void free_e2sm_ccc_ev_trg_frmt_3(e2sm_ccc_ev_trg_frmt_3_t* src);

bool eq_e2sm_ccc_ev_trg_frmt_3(e2sm_ccc_ev_trg_frmt_3_t const* m0, e2sm_ccc_ev_trg_frmt_3_t const* m1);

e2sm_ccc_ev_trg_frmt_3_t cp_e2sm_ccc_ev_trg_frmt_3(e2sm_ccc_ev_trg_frmt_3_t const* src);

#endif

