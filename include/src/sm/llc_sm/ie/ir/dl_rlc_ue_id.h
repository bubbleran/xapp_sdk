#ifndef DL_RLC_UE_ID_E2SM_LLC_MIR_H
#define DL_RLC_UE_ID_E2SM_LLC_MIR_H 

#include "../../../../lib/sm/ie/ue_id.h"

#include "dl_rlc_ue_bearer.h"

// From  8.3.21
typedef struct{
  // 8.3.8
  // Mandatory
  ue_id_e2sm_t ue_id;
  
  size_t sz_bearer;
  dl_rlc_ue_bearer_t* bearer; 

} dl_rlc_ue_id_t;

dl_rlc_ue_id_t cp_dl_rlc_ue_id(dl_rlc_ue_id_t const* src);

void free_dl_rlc_ue_id(dl_rlc_ue_id_t* src);

bool eq_dl_rlc_ue_id(dl_rlc_ue_id_t const* m0, dl_rlc_ue_id_t const* m1);

#endif
