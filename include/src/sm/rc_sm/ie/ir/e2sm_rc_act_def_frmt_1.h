#ifndef E2SM_RAN_CONTROL_ACTION_DEFINITION_FORMAT_1
#define E2SM_RAN_CONTROL_ACTION_DEFINITION_FORMAT_1

#include "param_report_def.h"

#include <stdbool.h>
#include <stdlib.h>

typedef struct{
  // Parameters to be Reported List
  // [1-65535]
  size_t sz_param_report_def; 
  param_report_def_t* param_report_def;

} e2sm_rc_act_def_frmt_1_t; 

void free_e2sm_rc_act_def_frmt_1(e2sm_rc_act_def_frmt_1_t* src);

bool eq_e2sm_rc_act_def_frmt_1(e2sm_rc_act_def_frmt_1_t const* m0, e2sm_rc_act_def_frmt_1_t const* m1);

e2sm_rc_act_def_frmt_1_t cp_e2sm_rc_act_def_frmt_1(e2sm_rc_act_def_frmt_1_t const* src);


#endif

