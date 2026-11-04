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

#ifndef SLOT_LLC_E2SM_MIR_H
#define SLOT_LLC_E2SM_MIR_H 

#include "add_dl_alloc.h"
#include "csi_rs_precoding_bnd2.h"
#include "dl_grant2.h"
#include "slot_info.h"

#include <stdbool.h>


// From 8.3.27
typedef struct{

  // Slot Information 
  // Mandatory 
  // 8.3.17
  slot_info_t slot_info;

  // List of DL Grants
  // [1, 63]
  size_t sz_dl_grant2;
  dl_grant2_t* dl_grant2;

  // List of Additional DL Allocations
  // [0, 63]
  size_t sz_add_dl_alloc;
  add_dl_alloc_t* add_dl_alloc;

  // List of CSI-RS Precoding
  // Bands Not Executed
  // [0,63]
  size_t sz_csi_rs_precoding_bnd2;
  csi_rs_precoding_bnd2_t* csi_rs_precoding_bnd2;

} slot_llc_t;

slot_llc_t cp_slot_llc(slot_llc_t const* src); 

void free_slot_llc(slot_llc_t* src);

bool eq_slot_llc(slot_llc_t const* m0, slot_llc_t const* m1);

#endif
