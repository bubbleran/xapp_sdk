#ifndef RAN_FUNC_DEF_CTRL_H
#define RAN_FUNC_DEF_CTRL_H

#include "seq_ctrl_style.h"

#include <stdlib.h>

// 9.2.2.5
typedef struct{

  // Sequence of CONTROL styles
  // [1 - 63]
  size_t sz_seq_ctrl_style;
  seq_ctrl_style_t* seq_ctrl_style;

} ran_func_def_ctrl_t;

void free_ran_func_def_ctrl(ran_func_def_ctrl_t* src);

bool eq_ran_func_def_ctrl(ran_func_def_ctrl_t const* m0, ran_func_def_ctrl_t const* m1);

ran_func_def_ctrl_t cp_ran_func_def_ctrl(ran_func_def_ctrl_t const* src);

#endif

