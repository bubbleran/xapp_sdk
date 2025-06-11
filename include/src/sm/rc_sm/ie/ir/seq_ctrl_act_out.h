#ifndef SEQ_CTRL_ACT_OUT_E2SM_RC_H
#define SEQ_CTRL_ACT_OUT_E2SM_RC_H

#include "seq_ran_param_2.h"

#include <stdbool.h>

// From 9.2.1.8.2
typedef struct{
  // Control Action ID
  // Mandatory
  // 9.3.6
  // [1- 65535]
  uint16_t ctrl_act_id;

  //Sequence of RAN
  //Parameters
  // [1-255]  
  size_t sz_ran_param; 
  seq_ran_param_2_t* ran_param;

} seq_ctrl_act_out_t ;

void free_seq_ctrl_act_out(seq_ctrl_act_out_t* src);

seq_ctrl_act_out_t cp_seq_ctrl_act_out(seq_ctrl_act_out_t const* src);

bool eq_seq_ctrl_act_out(seq_ctrl_act_out_t const* m0, seq_ctrl_act_out_t const* m1);

#endif

