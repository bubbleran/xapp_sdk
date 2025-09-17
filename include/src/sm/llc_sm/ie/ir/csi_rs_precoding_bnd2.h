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
