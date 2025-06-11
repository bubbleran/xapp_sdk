#ifndef RAN_FUNC_DEF_REPORT_H
#define RAN_FUNC_DEF_REPORT_H

#include "seq_report_sty.h"

#include <stdbool.h>
#include <stdlib.h>

// 9.2.2.3
typedef struct{
  // Sequence of REPORT styles
  // [1 - 63]
  size_t sz_seq_report_sty;
  seq_report_sty_t* seq_report_sty;
} ran_func_def_report_t;

void free_ran_func_def_report(ran_func_def_report_t* src);

bool eq_ran_func_def_report( ran_func_def_report_t const* m0, ran_func_def_report_t const* m1);

ran_func_def_report_t cp_ran_func_def_report(ran_func_def_report_t const* src);

#endif

