#ifndef E2SM_RC_CTRL_OUT_FRMT_2_H
#define E2SM_RC_CTRL_OUT_FRMT_2_H

#include "seq_ctrl_sty_mul_out.h"

#include <stdbool.h>
#include <stddef.h>

// 9.2.1.8.2
typedef struct{

// Sequence of Control Styles
// for Multiple Outcomes
// [1-63]
  size_t sz_seq_ctrl_sty_mul_out; 
  seq_ctrl_sty_mul_out_t* seq_ctrl_sty_mul_out; 

} e2sm_rc_ctrl_out_frmt_2_t;

void free_e2sm_rc_ctrl_out_frmt_2(e2sm_rc_ctrl_out_frmt_2_t* src);

e2sm_rc_ctrl_out_frmt_2_t cp_e2sm_rc_ctrl_out_frmt_2(e2sm_rc_ctrl_out_frmt_2_t const* src);

bool eq_e2sm_rc_ctrl_out_frmt_2(e2sm_rc_ctrl_out_frmt_2_t const* m0, e2sm_rc_ctrl_out_frmt_2_t const* m1);

#endif

