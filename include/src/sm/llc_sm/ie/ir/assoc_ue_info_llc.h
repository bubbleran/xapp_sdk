#ifndef ASSOC_UE_INFO_LLC_MIR_H
#define ASSOC_UE_INFO_LLC_MIR_H 

#include <stdbool.h>
#include "logical_or_llc.h"
#include "group_ue.h"

#include "../../../../lib/sm/ie/ue_id.h"

typedef enum{
  INDIVIDUAL_UE_UE_TYPE_E,
  GROUP_UE_UE_TYPE_E,
  END_UE_TYPE_E,
} ue_type_llc_e ;

// 8.3.12
typedef struct{

  // 8.3.10
  // Event Trigger ID for UE
  // Mandatory 
  // [1,65535]
  uint32_t ev_trg_id_ue;

  ue_type_llc_e ue_type;
  union{
    // 8.3.8
    ue_id_e2sm_t ue;
    // 8.3.13 
    group_ue_t ues; 
  };

  // 8.3.11
  // Logical OR 
  // Optional
  logical_or_llc_e* logical_or;

} assoc_ue_info_llc_t;

assoc_ue_info_llc_t cp_assoc_ue_info_llc(assoc_ue_info_llc_t const* src); 

void free_assoc_ue_info_llc(assoc_ue_info_llc_t* src);

bool eq_assoc_ue_info_llc(  assoc_ue_info_llc_t const* m0, assoc_ue_info_llc_t const* m1);

#endif
