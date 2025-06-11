#ifndef SEQ_CTRL_ACT_2_E2SM_RC_H
#define SEQ_CTRL_ACT_2_E2SM_RC_H 

#include "seq_ran_param_3.h"

#include <stdbool.h>
#include <stdlib.h>

// From 
// 9.2.2.5
typedef struct{ 
  // Control Action ID
  // Mandatory
  // 9.3.6
  // [1-65535]
  uint16_t id; 

  // Control Action Name
  // Mandatory
  // 9.3.7
  // [1-150]
  byte_array_t name;

  // Sequence of Associated RAN Parameters
  // [0-65535]
  size_t sz_seq_assoc_ran_param;
  seq_ran_param_3_t* assoc_ran_param;

} seq_ctrl_act_2_t;

void free_seq_ctrl_act_2(seq_ctrl_act_2_t* src);

bool eq_seq_ctrl_act_2( seq_ctrl_act_2_t const* m0, seq_ctrl_act_2_t const* m1);

seq_ctrl_act_2_t cp_seq_ctrl_act_2(seq_ctrl_act_2_t const* src);

#endif

