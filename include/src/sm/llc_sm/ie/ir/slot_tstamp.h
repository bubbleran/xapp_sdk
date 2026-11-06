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

#ifndef E2SM_LLC_SLOT_TSTAMP_MIR_H
#define E2SM_LLC_SLOT_TSTAMP_MIR_H 

#include "slot_info.h"
#include <stdbool.h>

// 8.3.18
typedef struct{
  // 8.3.17
  // Mandatory
  slot_info_t slot_info;

  // Mandatory
  // Carries UTC time encoded as the
  // 64-bit timestamp format as defined
  // in Clause 6 of IETF RFC 5905
  // [7] containing both seconds
  // and fraction parts. Represents the
  // start time of the slot
  uint8_t slot_start_time[8];

} slot_tstamp_t ;

slot_tstamp_t cp_slot_tstamp(slot_tstamp_t const* src);

bool eq_slot_tstamp( slot_tstamp_t const* m0, slot_tstamp_t const* m1);

void free_slot_tstamp(slot_tstamp_t* src);

#endif
