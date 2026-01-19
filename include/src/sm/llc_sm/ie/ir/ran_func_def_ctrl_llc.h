#ifndef RAN_FUNC_DEF_CONTROL_LLC_E2SM_MIR_H
#define RAN_FUNC_DEF_CONTROL_LLC_E2SM_MIR_H 

#include "seq_ctrl_style_llc.h"

#include <stdlib.h>


typedef struct {
  // Sequence of CONTROL styles
  // [1 - 63]
  size_t sz_seq_ctrl_style;
  seq_ctrl_style_llc_t* seq_ctrl_style;

} ran_func_def_ctrl_llc_t;

#endif
