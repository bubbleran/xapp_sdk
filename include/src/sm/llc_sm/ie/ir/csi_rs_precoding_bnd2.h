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

#ifndef CSI_RS_PRECODING_BND2_E2SM_LLC_MIR_H
#define CSI_RS_PRECODING_BND2_E2SM_LLC_MIR_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

// From 8.3.27
// List of DL Grants

// 0= Other
// 1= Information arrived too late
// 2= Unrecognized UE ID
// 3= Unrecognized NZP CSI-RS Resource ID
// 4= invalid RB range
// 5= Invalid number of Coef.
// 6= Coef gain is too high

typedef enum{
  OTHER_CAUSE_CSI_RS_PRECODING_BND2_E,
  INFO_TOO_LATE_CAUSE_CSI_RS_PRECODING_BND2_E,
  UNRECOGNIZE_UE_ID_CAUSE_CSI_RS_PRECODING_BND2_E,
  UNRECOGNIZE_NZP_CSI_RS_RES_ID_CAUSE_CSI_RS_PRECODING_BND2_E,
  INVALID_RB_RANGE_CAUSE_CSI_RS_PRECODING_BND2_E,
  INVALID_NUM_COEFF_CAUSE_CSI_RS_PRECODING_BND2_E,
  COEFF_GAIN_TOO_HIGH_CAUSE_CSI_RS_PRECODING_BND2_E,
  END_CAUSE_CSI_RS_PRECODING_BND2_E
} cause_csi_rs_precoding_bnd2_e ;

typedef struct{
  // CSI-RS Precoding Band ID
  // Mandatory
  // [0,63]
  uint32_t csi_rs_precod_bnd_id;

  // Cause
  // Mandatory
  cause_csi_rs_precoding_bnd2_e cause;

} csi_rs_precoding_bnd2_t;

csi_rs_precoding_bnd2_t cp_csi_rs_precoding_bnd2(csi_rs_precoding_bnd2_t const* src);

void free_csi_rs_precoding_bnd2(csi_rs_precoding_bnd2_t* src);

bool eq_csi_rs_precoding_bnd2(csi_rs_precoding_bnd2_t const* m0, csi_rs_precoding_bnd2_t const* m1);

#endif
