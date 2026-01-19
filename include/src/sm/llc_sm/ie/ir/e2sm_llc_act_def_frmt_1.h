#ifndef E2SM_LLC_ACT_DEF_FORMAT_1_MIR_H
#define E2SM_LLC_ACT_DEF_FORMAT_1_MIR_H 

#include "lower_layer_info.h"

// 8.2.1.2.1
typedef struct{
  // 8.3.15
  // Lower Layers Information Type 
  // Mandatory 
 lower_layer_info_e lower_layer_info;  

} e2sm_llc_act_def_frmt_1_t;

void free_e2sm_llc_act_def_frmt_1(e2sm_llc_act_def_frmt_1_t src); 

#endif
