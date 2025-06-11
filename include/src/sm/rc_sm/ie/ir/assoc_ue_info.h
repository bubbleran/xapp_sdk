#ifndef EVENT_TRIGGER_UE_INFORMATION_E2RC_H 
#define EVENT_TRIGGER_UE_INFORMATION_E2RC_H

#include "individual_ue.h"
#include "logical_or.h"

typedef enum{

  INDIVIDUAL_UE_UE_TYPE,
  UE_GROUP_UE_TYPE ,
  UE_TYPE_END

} ue_type_e ;


// This is NOT 9.3.26.

typedef struct{

  // Event Trigger UE ID
  // Mandatory
  // 9.3.22
  uint16_t ev_trigger_ue_id; // [1 - 65535]

  // CHOICE UE Type
  ue_type_e ue_type;
  union{
    individual_ue_t ind_ue;
    ran_param_t ue_group; 
  };

  // Logical OR
  // 9.3.25
  // Optional
  logical_or_e* log_or; 

} assoc_ue_info_t;


#endif

