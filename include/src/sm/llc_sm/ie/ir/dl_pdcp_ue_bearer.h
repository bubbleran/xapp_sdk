#ifndef DL_PDCP_UE_BEARER_E2SM_LLC_MIR_H
#define DL_PDCP_UE_BEARER_E2SM_LLC_MIR_H 

#include <stdbool.h>
#include <stdint.h>

// From 8.3.22 
typedef struct{

  // Mandatory
  // [1,32]
  uint32_t drb_id;

  // DL PDCP Buffer Occupancy
  // Mandatory
  uint32_t buf_occ_bytes;

  // DL PDCP HOL Time To Live
  // Mandatory
  // Time in units of 0.5ms. The time
  // available for the PDU at the head
  // of the line in the PDCP buffer to
  // be transmitted without violating
  // the PDB associated with
  // this DRB ID.
  // [0,1023] 
  uint32_t hol_05_ms_units;

} dl_pdcp_ue_bearer_t;

dl_pdcp_ue_bearer_t cp_dl_pdcp_ue_bearer(dl_pdcp_ue_bearer_t const* src);

void free_dl_pdcp_ue_bearer(dl_pdcp_ue_bearer_t* src);

bool eq_dl_pdcp_ue_bearer(dl_pdcp_ue_bearer_t const* m0, dl_pdcp_ue_bearer_t const* m1);

#endif
