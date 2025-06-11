#ifndef RAN_PARAM_COND_CRIT_DEF_H
#define RAN_PARAM_COND_CRIT_DEF_H

#include <stdbool.h>
#include <stdlib.h>

#include "ran_param_test.h"

// 9.3.29
typedef struct{

  // [1 - 255 ]
  size_t sz_ran_param_test;
  // RAN Parameter Test
  // 9.3.30
  ran_param_test_t* ran_param_test;

} ran_param_cond_crit_def_t; 

void free_ran_param_cond_crit_def(ran_param_cond_crit_def_t* src);

bool eq_ran_param_cond_crit_def(ran_param_cond_crit_def_t const* m0, ran_param_cond_crit_def_t const* m1);

ran_param_cond_crit_def_t cp_ran_param_cond_crit_def(ran_param_cond_crit_def_t const* src);

#endif

