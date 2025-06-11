#ifndef RAN_PARAM_INS_IND_E2SM_RC_H
#define RAN_PARAM_INS_IND_E2SM_RC_H

#include "ran_param_def.h"

#include <stdbool.h>
#include <stdint.h>

// From 9.2.1.2.4
typedef struct{
  // RAN Parameter ID
  // Mandatory
  // 9.3.8
  // [1.. 429496729 ]
  uint32_t ran_param_id;

  // RAN Parameter Definition
  // Optional
  // 9.3.51
  ran_param_def_t* ran_param_def; 

} ran_param_ins_ind_t;

void free_ran_param_ins_ind(ran_param_ins_ind_t const* src);

bool eq_ran_param_ins_ind(ran_param_ins_ind_t const* m0, ran_param_ins_ind_t const* m1);

ran_param_ins_ind_t cp_ran_param_ins_ind(ran_param_ins_ind_t const* src);

#endif

