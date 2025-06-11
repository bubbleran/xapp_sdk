#ifndef SEQ_RAN_PARAM_2_E2SM_RC_H
#define SEQ_RAN_PARAM_2_E2SM_RC_H

#include <stdbool.h>
#include <stdint.h>

#include "ran_parameter_value.h"

// From 9.2.1.8.1
typedef struct{
  // RAN Parameter ID
  // Mandatory
  // 9.3.8
  // [1 - 4294967295]
  uint32_t ran_param_id;

  // RAN Parameter Value
  // Mandatory
  // 9.3.14
  ran_parameter_value_t ran_param_value;

} seq_ran_param_2_t;

void free_seq_ran_param_2(seq_ran_param_2_t* src);

bool eq_seq_ran_param_2(seq_ran_param_2_t const* m0, seq_ran_param_2_t const* m1);

seq_ran_param_2_t cp_seq_ran_param_2( seq_ran_param_2_t const* src);

#endif

