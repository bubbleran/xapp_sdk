#ifndef SEQUENCE_OF_POLICY_CONDITION_H
#define SEQUENCE_OF_POLICY_CONDITION_H

#include <stdbool.h>

#include "ran_param_cond_crit_def.h"
#include "policy_action.h"

typedef struct{

  // Policy Action Definition
  // Mandatory
  // 9.3.20
  policy_action_t pol_act; 

  // Policy Condition Definition
  // Optional
  // 9.3.29
  ran_param_cond_crit_def_t* pol;

} policy_cond_t;

void free_policy_cond(policy_cond_t* src);

bool eq_policy_cond(policy_cond_t const* m0, policy_cond_t const* m1);

policy_cond_t cp_policy_cond(policy_cond_t const* src);

#endif

