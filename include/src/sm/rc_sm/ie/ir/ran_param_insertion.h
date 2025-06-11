#ifndef RAN_PARAMETER_INSERTION_E2SM_H
#define RAN_PARAMETER_INSERTION_E2SM_H

#include <stdbool.h>
#include <stdint.h>

#include "ran_param_def.h"

// From 9.2.1.2.3

typedef struct{

  // RAN Parameter ID
  // Mandatory
  // 9.3.8
  // [1 - 4294967295]
  uint32_t ran_id;

  // RAN Parameter Definition
  // Optional
  // 9.3.51
  ran_param_def_t* def;

} ran_param_ins_t;

void free_ran_param_ins(ran_param_ins_t* src);

bool eq_ran_param_ins(ran_param_ins_t const* m0, ran_param_ins_t const* m1);

ran_param_ins_t cp_ran_param_ins(ran_param_ins_t const* src);

#endif

