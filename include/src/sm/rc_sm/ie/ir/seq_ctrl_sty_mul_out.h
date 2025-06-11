#ifndef SEQ_CTRL_STY_MUL_OUT_E2SM_RC_H
#define SEQ_CTRL_STY_MUL_OUT_E2SM_RC_H


#include "seq_ctrl_act_out.h"

#include <stdint.h>
#include <stddef.h>


// From 9.2.1.8.2
typedef struct{
  // Indicated Control Style
  // Mandatory
  // 9.3.3
  //  6.2.2.2.
  uint32_t ind_ctrl_style;

  //Sequence of Control
  //Actions Outcom
  // [1-63]
  size_t sz_seq_ctrl_act_out;
  seq_ctrl_act_out_t* seq_ctrl_act_out;

} seq_ctrl_sty_mul_out_t;

void free_seq_ctrl_sty_mul_out( seq_ctrl_sty_mul_out_t* src);

seq_ctrl_sty_mul_out_t cp_seq_ctrl_sty_mul_out( seq_ctrl_sty_mul_out_t const* src);

bool eq_seq_ctrl_sty_mul_out( seq_ctrl_sty_mul_out_t const* m0,  seq_ctrl_sty_mul_out_t const* m1);

#endif

