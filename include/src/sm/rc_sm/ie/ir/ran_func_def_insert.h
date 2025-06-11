#ifndef RAN_FUNC_DEF_INSERT_H
#define RAN_FUNC_DEF_INSERT_H

#include <stdbool.h>
#include <stdlib.h>

#include "seq_ins_sty.h"

// 9.2.2.4
typedef struct{
  // Sequence of INSERT styles
  // [1-63]
  size_t sz_seq_ins_sty;
  seq_ins_sty_t* seq_ins_sty;
} ran_func_def_insert_t;

void free_ran_func_def_insert(ran_func_def_insert_t const* src);

bool eq_ran_func_def_insert(ran_func_def_insert_t const* m0, ran_func_def_insert_t const* m1);

ran_func_def_insert_t cp_ran_func_def_insert(ran_func_def_insert_t const* src);

#endif

