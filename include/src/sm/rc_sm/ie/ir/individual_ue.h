#ifndef INDIVIDUAL_UE_E2RC_H
#define INDIVIDUAL_UE_E2RC_H

#include "ran_param.h"
#include "../../../../lib/sm/ie/ue_id.h"


typedef struct{

  // UE ID
  // Mandatory
  // 9.3.10
  // Defined in KPM
  ue_id_e2sm_t ue_id;

 // RAN Parameter Testing for Individual UE
 // Optional
 // 9.3.29
  ran_param_t ran_param;

} individual_ue_t; 


#endif

