#ifndef POLICY_ACTION_E2SM_RC_H
#define POLICY_ACTION_E2SM_RC_H

#include "seq_ran_param.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

typedef enum{
  ACCEPT_RIC_POL_DECISION,
  REJECT_RIC_POL_DECISION,

  END_RIC_POL_DECISION
} ric_pol_decision_e;

// 9.3.20
typedef struct{

//  Policy Action ID
//  Mandatory
//  9.3.6
//  [1 - 65535]
  uint16_t policy_act_id;

// Sequence of RAN Parameters
// [0- 65535]
  size_t sz_seq_ran_param;
  seq_ran_param_t* seq_ran_param;

  // RIC Policy decision
  // Optional
  ric_pol_decision_e* pol_dec; 

} policy_action_t;

void free_policy_action(policy_action_t* src);

bool eq_policy_action(policy_action_t const* m0, policy_action_t const* m1);

policy_action_t cp_policy_action(policy_action_t const* src);

#endif

