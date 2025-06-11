#ifndef E2SM_RAN_CONTROL_ACTION_DEFINITION_FORMAT_2
#define E2SM_RAN_CONTROL_ACTION_DEFINITION_FORMAT_2

#include <stdbool.h>
#include <stdlib.h>

#include "policy_cond.h"

typedef struct{

  // Sequence of Policy Conditions
  // [1 - 65535]
  size_t sz_policy_cond;
  policy_cond_t* policy_cond; 

} e2sm_rc_act_def_frmt_2_t; 

void free_e2sm_rc_act_def_frmt_2(e2sm_rc_act_def_frmt_2_t* src);

bool eq_e2sm_rc_act_def_frmt_2(e2sm_rc_act_def_frmt_2_t const* m0, e2sm_rc_act_def_frmt_2_t const* m1);

e2sm_rc_act_def_frmt_2_t cp_e2sm_rc_act_def_frmt_2(e2sm_rc_act_def_frmt_2_t const* src); 

#endif

