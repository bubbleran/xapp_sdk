#ifndef RAN_PARAMETER_STRUCT_E2RC_h
#define RAN_PARAMETER_STRUCT_E2RC_h 

#include "seq_ran_param.h"
#include <stdbool.h>
#include <stdlib.h>


// 9.3.12
typedef struct ran_param_struct_s {
  // [1-65535]
  size_t sz_ran_param_struct;
  seq_ran_param_t* ran_param_struct;
} ran_param_struct_t;

void free_ran_param_struct(ran_param_struct_t* src);

bool eq_ran_param_struct(ran_param_struct_t const* m0, ran_param_struct_t const* m1);

ran_param_struct_t cp_ran_param_struct(ran_param_struct_t const* src);

#endif

