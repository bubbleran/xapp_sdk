#ifndef E2SM_RC_CTRL_MSG_FRMT_2_RC_H
#define E2SM_RC_CTRL_MSG_FRMT_2_RC_H

#include "seq_ctrl_sma.h"

#include <stdbool.h>
#include <stdlib.h>


// 9.2.1.7.2
typedef struct{
  // Sequence of Control Styles
  // for Multiple Actions
  // [1 - 63]  
  size_t sz_seq_ctrl_sma;
  seq_ctrl_sma_t* action;

} e2sm_rc_ctrl_msg_frmt_2_t;

void free_e2sm_rc_ctrl_msg_frmt_2( e2sm_rc_ctrl_msg_frmt_2_t* src);

bool eq_e2sm_rc_ctrl_msg_frmt_2( e2sm_rc_ctrl_msg_frmt_2_t const* m0,  e2sm_rc_ctrl_msg_frmt_2_t const* m1);

e2sm_rc_ctrl_msg_frmt_2_t cp_e2sm_rc_ctrl_msg_frmt_2(e2sm_rc_ctrl_msg_frmt_2_t const* src);

#endif



