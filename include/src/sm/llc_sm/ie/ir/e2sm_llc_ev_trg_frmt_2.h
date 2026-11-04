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

#ifndef E2SM_LLC_EVENT_TRIGGER_FORMAT_2_MIR_H
#define E2SM_LLC_EVENT_TRIGGER_FORMAT_2_MIR_H 

#include "assoc_ue_info_llc.h"
#include "ev_trg_ue_info.h"

// 8.2.1.1.2
typedef struct{
  // Reporting Period 
  // Mandatory
  // [1, 65535]
  uint32_t period_ms;

  // 8.3.12
  // Associated UE Info
  // Optional
   ev_trg_ue_info_t* assoc_ue_info;

} e2sm_llc_ev_trg_frmt_2_t;

void free_e2sm_llc_ev_trg_frmt_2(e2sm_llc_ev_trg_frmt_2_t const* src); 

bool eq_e2sm_llc_ev_trg_frmt_2(e2sm_llc_ev_trg_frmt_2_t const* m0, e2sm_llc_ev_trg_frmt_2_t const* m1); 

e2sm_llc_ev_trg_frmt_2_t cp_e2sm_llc_ev_trg_frmt_2(e2sm_llc_ev_trg_frmt_2_t const* src);

#endif
