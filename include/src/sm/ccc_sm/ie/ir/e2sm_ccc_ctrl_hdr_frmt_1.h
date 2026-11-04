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

#ifndef E2SM_CCC_CTRL_HDR_FRMT_1_E2SM_H
#define E2SM_CCC_CTRL_HDR_FRMT_1_E2SM_H

#include <stdint.h>
#include <stdbool.h>

// 9.2.1.6.1
typedef struct{
  //  RIC Style Type
  //  Mandatory
  //  9.3.3
  //  Defined in common 6.2.2.2.
  uint32_t ric_style_type;
} e2sm_ccc_ctrl_hdr_frmt_1_t;

void free_e2sm_ccc_ctrl_hdr_frmt_1(e2sm_ccc_ctrl_hdr_frmt_1_t* src);

bool eq_e2sm_ccc_ctrl_hdr_frmt_1(e2sm_ccc_ctrl_hdr_frmt_1_t const* m0, e2sm_ccc_ctrl_hdr_frmt_1_t const* m1);

e2sm_ccc_ctrl_hdr_frmt_1_t cp_e2sm_ccc_ctrl_hdr_frmt_1( e2sm_ccc_ctrl_hdr_frmt_1_t const* src);

#endif

