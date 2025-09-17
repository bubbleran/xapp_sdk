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
