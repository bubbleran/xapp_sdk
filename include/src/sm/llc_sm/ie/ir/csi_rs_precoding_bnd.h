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

#ifndef CSI_RS_PRECODING_BND_E2SM_LLC_MIR_H
#define CSI_RS_PRECODING_BND_E2SM_LLC_MIR_H

#include <stdbool.h>

#include "../../../../lib/sm/ie/ue_id.h"

// From 8.3.26    
typedef struct{

  // Precoder ID
  // Mandatory
  // [0,63]
  uint32_t precoder_id;

  // 8.3.8
  // UE ID
  // Mandatory
  ue_id_e2sm_t ue_id;

  // NZP CSI-RS Resource ID
  // Mandatory
  // [0.191]
  uint32_t nzp_csi_rs_res_id;

  // Start RB
  // Mandatory
  uint32_t start_rb;

  // Number of RB
  // Mandatory
  uint32_t num_rb;

} csi_rs_precoding_bnd_t;

csi_rs_precoding_bnd_t cp_csi_rs_precoding_bnd(csi_rs_precoding_bnd_t const* src);

void free_csi_rs_precoding_bnd(csi_rs_precoding_bnd_t* src);

bool eq_csi_rs_precoding_bnd(csi_rs_precoding_bnd_t const* m0, csi_rs_precoding_bnd_t const* m1);

#endif
