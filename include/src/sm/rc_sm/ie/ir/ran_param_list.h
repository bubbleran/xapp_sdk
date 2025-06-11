#ifndef RAN_PARAMETER_LIST_E2RC_H
#define RAN_PARAMETER_LIST_E2RC_H 

#include "lst_ran_param.h"

#include <stdbool.h>
#include <stdlib.h>

// 9.3.13
typedef struct ran_param_list_s {
  // [0- 65535]
  size_t sz_lst_ran_param;
  lst_ran_param_t* lst_ran_param;
} ran_param_list_t;

void free_ran_param_list(ran_param_list_t* src);

bool eq_ran_param_list(ran_param_list_t const* m0, ran_param_list_t const* m1);

ran_param_list_t cp_ran_param_list(ran_param_list_t const* src);

#endif

