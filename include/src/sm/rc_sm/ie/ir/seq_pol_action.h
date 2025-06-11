#ifndef SEQ_POL_ACTION_E2SM_RC_H
#define SEQ_POL_ACTION_E2SM_RC_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "../../../../util/byte_array.h"
#include "seq_ran_param_3.h"

// From 
// 9.2.2.6
typedef struct{
  // Policy Action ID
  // Mandatory
  // 9.3.6
  uint32_t action_id; 

  // Policy Action Name
  // Mandatory
  // 9.3.7
  // [1-150]
  byte_array_t name;

  // RIC Action Definition Format Type
  // Mandatoyr
  // 9.3.5
  uint32_t frmt_type;

  // Sequence of Associated RAN Parameters for Policy Action
  // [0- 65535]
  size_t sz_seq_assoc_rp_action;
  seq_ran_param_3_t* seq_assoc_rp_action;

  // Sequence of Associated RAN Parameters for Policy Condition
  // [0- 65535]
  size_t sz_seq_assoc_rp_policy;
  seq_ran_param_3_t*  seq_assoc_rp_policy;

}seq_pol_action_t;

void free_seq_pol_action(seq_pol_action_t* src);

bool eq_seq_pol_action(seq_pol_action_t const* m0, seq_pol_action_t const* m1);

seq_pol_action_t cp_seq_pol_action(seq_pol_action_t* src);


#endif
