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

#ifndef CSI_LLC_MIR_H
#define CSI_LLC_MIR_H 

#include "csi_ue_id.h"
#include <stdbool.h>

// 8.3.20
typedef struct{
  // [1, 65535]
  size_t sz_csi_ue_id; 
  csi_ue_id_t* ue_id;
} csi_llc_t;

csi_llc_t cp_csi_llc(csi_llc_t const* src);

void free_csi_llc(csi_llc_t* src);

bool eq_csi_llc(csi_llc_t const* m0, csi_llc_t const* m1);

#endif
