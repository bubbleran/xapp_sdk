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

#ifndef DL_SCHD_PARAM_E2SM_LLC_MIR_H
#define DL_SCHD_PARAM_E2SM_LLC_MIR_H 

#include "slot_llc.h"
#include <stdbool.h>

// 8.3.27
typedef struct{

  // Received Timestamp 
  // Mandatory
  // 8.3.24
  uint8_t tstamp[8];

  // Processing Time Margin 
  // Mandatory 
  // INTEGER [-32767,32767]
  int32_t proc_time_margin;

  // List of Slots
  // [1, 63]
  size_t sz_slots;
  slot_llc_t* slot;

} dl_schd_param_t ;

dl_schd_param_t cp_dl_schd_param( dl_schd_param_t const* src);

void free_dl_schd_param( dl_schd_param_t* src);

bool eq_dl_schd_param(dl_schd_param_t const* m0, dl_schd_param_t const* m1 );




#endif
