#ifndef SEQ_RAN_PARAM_3_E2SM_RC_H
#define SEQ_RAN_PARAM_3_E2SM_RC_H

#include "../../../../util/byte_array.h"
#include "ran_param_def.h"

#include <stdbool.h>
#include <stdint.h>

typedef struct{
  // RAN Parameter ID
  // Mandatory
  // 9.3.8
  // [1- 4294967295]
  uint32_t id; 

  // RAN Parameter Name
  // Mandatory
  // 9.3.9
  // [1-150] 
  byte_array_t name;

  // RAN Parameter Definition
  // Optional
  // 9.3.51
  ran_param_def_t* def;

} seq_ran_param_3_t ;

void free_seq_ran_param_3(seq_ran_param_3_t* src);

bool eq_seq_ran_param_3(seq_ran_param_3_t const* m0, seq_ran_param_3_t const* m1);

seq_ran_param_3_t cp_seq_ran_param_3(seq_ran_param_3_t const* src);

#endif

