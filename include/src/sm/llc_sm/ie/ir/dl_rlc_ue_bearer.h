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

#ifndef DL_RLC_UE_BEARER_MIR_H
#define DL_RLC_UE_BEARER_MIR_H 

#include <stdbool.h>
#include <stdint.h>

// From  8.3.21
typedef struct{

  // Mandatory
  // [1, 32]
  uint32_t lcid;

  // Mandatory
  uint32_t buf_occ_bytes;

  // RLC HOL Time To Live
  // Mandatory
  // Time in units of
  // 0.5ms. The time available for the
  // PDU at the head of the line in the
  // RLC buffer to be transmitted
  // without violating the PDB
  // associated with this LCID.
  // [0,1023] 
  uint32_t hol_05_ms_unit;

} dl_rlc_ue_bearer_t;

dl_rlc_ue_bearer_t cp_dl_rlc_ue_bearer( dl_rlc_ue_bearer_t const* src);

void free_dl_rlc_ue_bearer(dl_rlc_ue_bearer_t* src);

bool eq_dl_rlc_ue_bearer(dl_rlc_ue_bearer_t const* m0, dl_rlc_ue_bearer_t const* m1);

#endif
