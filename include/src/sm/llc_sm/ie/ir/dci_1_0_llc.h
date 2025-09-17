#ifndef DCI_1_0_LLC_E2SM_MIR_H
#define DCI_1_0_LLC_E2SM_MIR_H 

#include "cs_rnti.h"
#include "vrb_to_prb_map.h"
#include "../../../../util/byte_array.h"

// From 8.3.26    
typedef struct{

  // Optional
  cs_rnti_t* cs_rnti;

  // Mandatory
  // Freq Domain Resources
  uint32_t freq_domain_res;

  // Mandatory
  // Time Domain Resources
  // [0,15] 
  uint32_t time_domain_res;

  // Optional
  // VRB to PRB Mapping
  vrb_to_prb_map_e* vrb_to_prb_map;

  // Mandatory
  // [0,31]
  uint32_t mcs; 

  // Mandatory
  // [0,3]
  uint32_t redundancy_version; 

} dci_1_0_llc_t;

dci_1_0_llc_t cp_dci_1_0_llc(dci_1_0_llc_t const* src);

void free_dci_1_0_llc(dci_1_0_llc_t* src);

bool eq_dci_1_0_llc(dci_1_0_llc_t const* m0, dci_1_0_llc_t const* m1);


#endif
