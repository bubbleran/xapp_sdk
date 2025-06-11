#ifndef E2SM_RC_CTRL_OUT_FRMT_1_H
#define E2SM_RC_CTRL_OUT_FRMT_1_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "seq_ran_param_2.h"

// 9.2.1.8.1
typedef struct{
  // Sequence of RAN
  // Parameters
  // [0 - 255]
  size_t sz_seq_ran_param_2;
  seq_ran_param_2_t* ran_param;

} e2sm_rc_ctrl_out_frmt_1_t;

void free_e2sm_rc_ctrl_out_frmt_1(e2sm_rc_ctrl_out_frmt_1_t* src);

e2sm_rc_ctrl_out_frmt_1_t cp_e2sm_rc_ctrl_out_frmt_1(e2sm_rc_ctrl_out_frmt_1_t const* src);

bool eq_e2sm_rc_ctrl_out_frmt_1(e2sm_rc_ctrl_out_frmt_1_t const* m0, e2sm_rc_ctrl_out_frmt_1_t const* m1);

#endif

