#ifndef RAN_PARAM_ELM_KEY_TRUE_E2RC_H
#define RAN_PARAM_ELM_KEY_TRUE_E2RC_H 

#include "ran_parameter_value.h"

#include <stdbool.h>

typedef struct{

//  9.3.14
  ran_parameter_value_t value;

} ran_param_elm_key_true_t ;

void free_ran_param_elm_key_true(ran_param_elm_key_true_t * src);

bool eq_ran_param_elm_key_true(ran_param_elm_key_true_t const* m0, ran_param_elm_key_true_t const* m1);

#endif

