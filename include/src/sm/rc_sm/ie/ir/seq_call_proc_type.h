#ifndef SEQ_CALL_PROC_TYPE_E2SM_RC_H
#define SEQ_CALL_PROC_TYPE_E2SM_RC_H 

#include "../../../../util/byte_array.h"
#include "call_proc_break.h"

#include <stdint.h>
#include <stdlib.h>

typedef struct{
  // Call Process Type ID
  // Mandatory
  // 9.3.15
  // [1- 65535]
  uint16_t id; 

  // Call Process Type Name
  // Mandatory
  // 9.3.19
  // [1-150]
  byte_array_t name;

  // Sequence of Call Process Breakpoints
  // [1-65535]
  size_t sz_call_proc_break; 
  call_proc_break_t* call_proc_break;

} seq_call_proc_type_t;

void free_seq_call_proc_type( seq_call_proc_type_t* src);

bool eq_seq_call_proc_type( seq_call_proc_type_t const* m0,  seq_call_proc_type_t const* m1);

seq_call_proc_type_t cp_seq_call_proc_type(seq_call_proc_type_t const* src);


#endif
