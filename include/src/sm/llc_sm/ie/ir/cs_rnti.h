#ifndef CS_RNTI_E2SM_LLC_MIR_H
#define CS_RNTI_E2SM_LLC_MIR_H 

#include <stdbool.h>
#include <stdint.h>

typedef struct{
  // SPS Config Index
  // C-ifSPSLis
  // [0,7]
  uint32_t* sps_config_idx; 

  // Activation 
  // Mandatory
  bool activate;

} cs_rnti_t ;

cs_rnti_t cp_cs_rnti(cs_rnti_t const* src);

void free_cs_rnti(cs_rnti_t* src);

bool eq_cs_rnti(cs_rnti_t const* m0, cs_rnti_t const* m1);


#endif
