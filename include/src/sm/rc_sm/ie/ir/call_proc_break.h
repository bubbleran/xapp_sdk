#ifndef CALL_PROC_BREAK_E2SM_RC_H
#define CALL_PROC_BREAK_E2SM_RC_H

#include "seq_ran_param_3.h"

#include <stdlib.h>
#include <stdint.h>

// From 9.2.2.2
typedef struct{
  // Call Process Breakpoint ID
  // Mandatory
  // 9.3.49
  // [1 - 65535]
  uint16_t id;

  // Call Process Breakpoint Name
  // Mandatory
  // 9.3.50
  // [1-150]
  byte_array_t name;

  // Sequence of Associated RAN Parameters
  // [0-65535]
  size_t sz_param;
  seq_ran_param_3_t* param; 

} call_proc_break_t;

void free_call_proc_break(call_proc_break_t* src);

bool eq_call_proc_break(call_proc_break_t const* m0, call_proc_break_t const* m1);

call_proc_break_t cp_call_proc_break(call_proc_break_t const* src);


#endif
