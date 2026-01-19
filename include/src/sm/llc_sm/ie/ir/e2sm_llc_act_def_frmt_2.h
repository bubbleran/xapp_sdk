#ifndef E2SM_LLC_ACTION_DEF_FORMAT_2_MIR_H
#define E2SM_LLC_ACTION_DEF_FORMAT_2_MIR_H 

#include "lower_layer_measure.h"
#include <stdbool.h>
#include <stddef.h>

// 8.2.1.2.2
typedef struct{
  // 8.3.16
  // [1,65535]
  size_t sz_llm;
  lower_layer_measure_e* llm;
} e2sm_llc_act_def_frmt_2_t;

e2sm_llc_act_def_frmt_2_t cp_e2sm_llc_act_def_frmt_2(e2sm_llc_act_def_frmt_2_t const* src);

bool eq_e2sm_llc_act_def_frmt_2(e2sm_llc_act_def_frmt_2_t const* m0, e2sm_llc_act_def_frmt_2_t const* m1);

void free_e2sm_llc_act_def_frmt_2( e2sm_llc_act_def_frmt_2_t* src);

#endif
