#ifndef E2SM_RC_CTRL_OUT_FRMT_3_H
#define E2SM_RC_CTRL_OUT_FRMT_3_H

#include "seq_ran_param.h"

#include <stdbool.h>
#include <stddef.h>

// 9.2.1.8.3
typedef struct{

  //  Sequence of RAN Parameters
  //  [0-255]
  size_t sz_seq_ran_param;
  seq_ran_param_t* ran_param;

} e2sm_rc_ctrl_out_frmt_3_t;

void free_e2sm_rc_ctrl_out_frmt_3( e2sm_rc_ctrl_out_frmt_3_t* src);

e2sm_rc_ctrl_out_frmt_3_t cp_e2sm_rc_ctrl_out_frmt_3(e2sm_rc_ctrl_out_frmt_3_t const* src);

bool eq_e2sm_rc_ctrl_out_frmt_3( e2sm_rc_ctrl_out_frmt_3_t const* m0,  e2sm_rc_ctrl_out_frmt_3_t const* m1);


#endif

