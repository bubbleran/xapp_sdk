#ifndef UE_INFORMATION_CHANGE_E2SM_H
#define UE_INFORMATION_CHANGE_E2SM_H

#include "ev_trigger_ue_info.h"
#include "rrc_state_lst.h"
#include "ran_param_cond_crit_def.h"

#include <stdint.h>


typedef enum{
  RRC_STATE_UE_INFO_CHNG_TRIGGER_TYPE,
  UE_ID_CHANGE_UE_INFO_CHNG_TRIGGER_TYPE,
  L2_STATE_UE_INFO_CHNG_TRIGGER_TYPE,

  END_UE_INFO_CHNG_TRIGGER_TYPE 

} ue_info_chng_trigger_type_e;



typedef struct{
  //  Event Trigger Condition ID
  //  Mandatory
  //  9.3.21
  // INTEGER (1..65535, …)
  uint16_t ev_trig_cond_id;

  // CHOICE Trigger Type
  ue_info_chng_trigger_type_e type;
  union{
    // RRC State
    rrc_state_lst_t rrc_state;  

    // UE Identifier Change
    // [1 - 512]
    uint16_t ue_id_chng;

    // L2 State
    // 9.3.29
    // RAN Parameter Conditional Criteria Definition
    ran_param_cond_crit_def_t l2_state;
  };
  // Associated UE Info 
  // Optional
  // 9.3.26
  ev_trigger_ue_info_t* assoc_ue_info;

  // Logical OR
  // Optional
  // 9.3.25
  logical_or_e* log_or;

} ue_info_chng_t;

void free_ue_info_chng(ue_info_chng_t* src);

bool eq_ue_info_chng(ue_info_chng_t const* m0, ue_info_chng_t const* m1);

ue_info_chng_t cp_ue_info_chng(ue_info_chng_t const* src);

#endif

