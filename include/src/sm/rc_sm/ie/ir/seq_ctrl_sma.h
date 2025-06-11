#ifndef SEQUENCE_CONTROL_STYLES_MULTIPLE_ACTIONS_E2SM_RC_H
#define SEQUENCE_CONTROL_STYLES_MULTIPLE_ACTIONS_E2SM_RC_H 

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "seq_ctrl_act.h"

// From 9.2.1.7.2
typedef struct{
  // Indicated Control Style
  // Mandatory
  // 9.3.3
  // 6.2.2.2.
  // INTEGER
  uint32_t ctrl_style;

  // Sequence of Control Actions
  // [1-63]
  size_t sz_seq_ctrl_act;
  seq_ctrl_act_t* seq_ctrl_act;

} seq_ctrl_sma_t;

void free_seq_ctrl_sma(seq_ctrl_sma_t* src);

bool eq_seq_ctrl_sma(seq_ctrl_sma_t const* m0, seq_ctrl_sma_t const* m1);

seq_ctrl_sma_t cp_seq_ctrl_sma(seq_ctrl_sma_t const* src);

#endif

