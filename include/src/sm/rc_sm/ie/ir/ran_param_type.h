#ifndef RAN_PARAM_TYPE_H_MIR
#define RAN_PARAM_TYPE_H_MIR 

#include "ran_param_lst_struct.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct {
  // [1-65535]
  size_t sz_ran_param;
  ran_param_lst_struct_t* ran_param;

} ran_param_type_t;

void free_ran_param_type(ran_param_type_t* src);

bool eq_ran_param_type(ran_param_type_t const* m0, ran_param_type_t const* m1);

ran_param_type_t cp_ran_param_type(ran_param_type_t const* src);

#endif
