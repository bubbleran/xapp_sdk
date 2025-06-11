#ifndef E2SM_RC_CTRL_MSG_FRMT_1_RC_H
#define E2SM_RC_CTRL_MSG_FRMT_1_RC_H

#include "seq_ran_param.h"
#include <stdlib.h>

// 9.2.1.7.1
typedef struct{
  // List of RAN parameters
  // [0- 65535]
  size_t sz_ran_param; 
  seq_ran_param_t* ran_param;
} e2sm_rc_ctrl_msg_frmt_1_t;

void free_e2sm_rc_ctrl_msg_frmt_1( e2sm_rc_ctrl_msg_frmt_1_t* src);

bool eq_e2sm_rc_ctrl_msg_frmt_1(e2sm_rc_ctrl_msg_frmt_1_t const* m0, e2sm_rc_ctrl_msg_frmt_1_t const* m1);

e2sm_rc_ctrl_msg_frmt_1_t cp_e2sm_rc_ctrl_msg_frmt_1(e2sm_rc_ctrl_msg_frmt_1_t const* src);

#endif

