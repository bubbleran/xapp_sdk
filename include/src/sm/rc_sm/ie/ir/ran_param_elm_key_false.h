#ifndef RAN_PARAM_ELM_KEY_FALSE_E2RC_H
#define RAN_PARAM_ELM_KEY_FALSE_E2RC_H

#include "logical_or.h"
#include "ran_parameter_value.h"
#include "ran_parameter_test_condition.h"

#include <stdbool.h>

typedef struct{

  // RAN Parameter Test Condition
  // 9.3.31
  // Mandatory
  ran_param_test_cond_t test_cond;

  // RAN Parameter Value
  // Optional
  // 9.3.14
  ran_parameter_value_e* value;

  // Logical OR
  // Optional
  // 9.3.25
  logical_or_e* logical_or;

} ran_param_elm_key_false_t; 

void free_ran_param_elm_key_false(ran_param_elm_key_false_t* src);

bool eq_ran_param_elm_key_false(ran_param_elm_key_false_t const* m0, ran_param_elm_key_false_t const* m1);

ran_param_elm_key_false_t cp_ran_param_elm_key_false( ran_param_elm_key_false_t const* src);

#endif

