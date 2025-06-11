#ifndef SEQUENCE_RAN_PARAMETER_E2SM_H
#define SEQUENCE_RAN_PARAMETER_E2SM_H 

#include <stdbool.h>
#include <stdint.h>

#include "ran_parameter_value_type.h"

typedef struct{
  // RAN Parameter ID
  // Mandatory
  // 9.3.8
  // [1 - 4294967295]
  // This IE uniquely identifies 
  // a specific RAN parameter of 
  // a given RIC Control style.
  // Standard is probably broken as it can
  // come from Indication Message Format 1
  uint32_t ran_param_id;

  // RAN Parameter Value Type
  // 9.3.11
  // Mandatory
  ran_param_val_type_t ran_param_val;

} seq_ran_param_t;

void free_seq_ran_param(seq_ran_param_t* src);

bool eq_seq_ran_param(seq_ran_param_t const* m0, seq_ran_param_t const* m1);

seq_ran_param_t cp_seq_ran_param(seq_ran_param_t const* src);

#endif

