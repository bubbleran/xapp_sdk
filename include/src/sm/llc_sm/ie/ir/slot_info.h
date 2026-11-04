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

#ifndef E2SM_LLC_SLOT_INFO_MIR_H
#define E2SM_LLC_SLOT_INFO_MIR_H 

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum{
  SCS_15_SLOT_IDX_LLC_E,
  SCS_30_SLOT_IDX_LLC_E,
  SCS_60_SLOT_IDX_LLC_E,
  SCS_120_SLOT_IDX_LLC_E,
  END_SLOT_IDX_LLC_E
} slot_idx_llc_e;

// 8.3.17
typedef struct{

  // System Frame Number 
  // Mandatory
  // [0,1023]
  uint32_t frame_num;

  // Mandatory
  slot_idx_llc_e slot_idx;
  union{
    uint32_t scs_15;
    uint32_t scs_30;
    uint32_t scs_60;
    uint32_t scs_120;
  };

} slot_info_t;

slot_info_t cp_slot_info( slot_info_t const* src);

bool eq_slot_info(slot_info_t const* m0, slot_info_t const* m1);

void free_slot_info(slot_info_t* src);

#endif
