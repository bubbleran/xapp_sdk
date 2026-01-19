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
