#ifndef E2SM_RAN_CONTROL_ACTION_DEFINITION_FORMAT_3
#define E2SM_RAN_CONTROL_ACTION_DEFINITION_FORMAT_3

#include "ran_param_insertion.h"
#include "../../../../lib/sm/ie/ue_id.h"

#include <stdbool.h>
#include <stdlib.h>

typedef struct{
  // Insert Indication ID
  // Mandatory
  // 9.3.16
  // [1 - 65535] 
  uint16_t id; 

  // List of RAN parameters for Insert
  // Indication
  // [1 - 65535]
  size_t sz_ran_param_ins;
  ran_param_ins_t* ran_param;

  //  UE ID
  //  Optional
  //  9.3.10
  ue_id_e2sm_t* ue_id;

} e2sm_rc_act_def_frmt_3_t;

void free_e2sm_rc_act_def_frmt_3(e2sm_rc_act_def_frmt_3_t * src);

bool eq_e2sm_rc_act_def_frmt_3( e2sm_rc_act_def_frmt_3_t const* m0, e2sm_rc_act_def_frmt_3_t const* m1);

e2sm_rc_act_def_frmt_3_t cp_e2sm_rc_act_def_frmt_3(e2sm_rc_act_def_frmt_3_t const* src);

#endif
