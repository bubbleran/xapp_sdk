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

#ifndef E2SM_LLC_CTRL_HDR_FORMT_1_MIR_H
#define E2SM_LLC_CTRL_HDR_FORMT_1_MIR_H 

#include <stdbool.h>
#include <stdint.h>

// 8.2.1.6.1
typedef struct{
  //8.3.3
  //RIC Style Type 
  //Mandatory
  uint32_t ric_style_type;

  //8.3.6
  //Control Action ID 
  //Mandatory 
  //[1, 65535]
  uint32_t ctrl_act_id;

} e2sm_llc_ctrl_hdr_frmt_1_t ;

e2sm_llc_ctrl_hdr_frmt_1_t cp_e2sm_llc_ctrl_hdr_frmt_1(e2sm_llc_ctrl_hdr_frmt_1_t const* src);

void free_e2sm_llc_ctrl_hdr_frmt_1(e2sm_llc_ctrl_hdr_frmt_1_t* src);

bool eq_e2sm_llc_ctrl_hdr_frmt_1(e2sm_llc_ctrl_hdr_frmt_1_t const* m0, e2sm_llc_ctrl_hdr_frmt_1_t const* m1);

#endif
