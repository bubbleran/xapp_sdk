#ifndef SEQ_POLICY_STY_E2SM_RC_H
#define SEQ_POLICY_STY_E2SM_RC_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#include "../../../../util/byte_array.h"

#include "seq_pol_action.h"

// From 
// 9.2.2.6
typedef struct{
  // RIC Policy Style Type
  // Mandatory
  // 9.3.3
  uint32_t style_type;

  // RIC Policy Style Name
  // Mandatory
  // 9.3.4
  byte_array_t name;

  // Supported RIC Event Trigger Style Type
  // Mandatory
  // 9.3.3
  uint32_t ev_trg_style_type;

  // Sequence of Policy Actions
  // [0-65535]
  size_t sz_seq_pol_action;
  seq_pol_action_t* seq_pol_action;

} seq_policy_sty_t;

void free_seq_policy_sty(seq_policy_sty_t* src);

bool eq_seq_policy_sty(seq_policy_sty_t const* m0,  seq_policy_sty_t const* m1);

seq_policy_sty_t cp_seq_policy_sty(seq_policy_sty_t const* src);

#endif

