#ifndef DL_PDCP_UE_ID_E2SM_LLC_MIR_H
#define DL_PDCP_UE_ID_E2SM_LLC_MIR_H 

#include "../../../../lib/sm/ie/ue_id.h"

#include "dl_pdcp_ue_bearer.h"

// From 8.3.22 
typedef struct{
  // 8.3.8
  // Mandatory
  ue_id_e2sm_t ue_id;

  // [1,225]
  size_t sz_dl_pdcp_ue_bearer;
  dl_pdcp_ue_bearer_t* dl_pdcp_ue_bearer;

} dl_pdcp_ue_id_t;

dl_pdcp_ue_id_t cp_dl_pdcp_ue_id(dl_pdcp_ue_id_t const* src);

bool eq_dl_pdcp_ue_id(dl_pdcp_ue_id_t const* m0,dl_pdcp_ue_id_t const* m1);

void free_dl_pdcp_ue_id(dl_pdcp_ue_id_t* src); 


#endif
