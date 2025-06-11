#ifndef RAN_FUNC_DEF_POLICY_H
#define RAN_FUNC_DEF_POLICY_H

#include "seq_policy_sty.h"

#include <stdbool.h>
#include <stdlib.h>

// 9.2.2.6
typedef struct{
  // Sequence of POLICY styles
  // [1-63]
  size_t sz_policy_styles;
  seq_policy_sty_t* seq_policy_sty;

} ran_func_def_policy_t;

void free_ran_func_def_policy(ran_func_def_policy_t* src);

bool eq_ran_func_def_policy(ran_func_def_policy_t const* m0,  ran_func_def_policy_t const* m1);

ran_func_def_policy_t cp_ran_func_def_policy(ran_func_def_policy_t const* src);

#endif

