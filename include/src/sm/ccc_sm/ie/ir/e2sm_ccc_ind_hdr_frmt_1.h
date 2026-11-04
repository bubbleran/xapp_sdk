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

#ifndef E2SM_CCC_INDICATION_HEADER_FORMAT_1_H
#define E2SM_CCC_INDICATION_HEADER_FORMAT_1_H

#include <stdbool.h>
#include <stdint.h>

#include "../../../../util/byte_array.h"

typedef enum {
  IND_REASON_UPON_SUB,
  IND_REASON_UPON_CHANGE,
  IND_REASON_PERIODIC,

  END_IND_REASON
} indication_reason_e;

// 9.2.1.3.1
typedef struct{
  // Event time
  // 9.3.10
  // Mandatory
  char* event_time;

  // Indication reason
  // Mandatory
  indication_reason_e ind_reason;

} e2sm_ccc_ind_hdr_frmt_1_t;


e2sm_ccc_ind_hdr_frmt_1_t cp_e2sm_ccc_ind_hdr_frmt_1(e2sm_ccc_ind_hdr_frmt_1_t const* src);

void free_e2sm_ccc_ind_hdr_frmt_1(e2sm_ccc_ind_hdr_frmt_1_t* src);

bool eq_e2sm_ccc_ind_hdr_frmt_1(e2sm_ccc_ind_hdr_frmt_1_t const* m0,e2sm_ccc_ind_hdr_frmt_1_t const* m1);

#endif
