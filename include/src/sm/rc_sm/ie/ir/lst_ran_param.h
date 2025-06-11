#ifndef LIST_OF_RAN_PARAMETER_H
#define LIST_OF_RAN_PARAMETER_H

#include "ran_param_struct.h"

#include <stdint.h>

typedef struct{

  // Bug in the standard. RAN Parameter List 9.3.13 
  // has a mandatory ie RAN Parameter ID 9.3.8 
  // and a mandatory ie RAN Parameter Structure 9.3.12
  // However, the ASN  
  // RANParameter-LIST ::= SEQUENCE {
  // list-of-ranParameter  SEQUENCE (SIZE(1..maxnoofItemsinList)) OF RANParameter-STRUCTURE, 
  // ..
  // }
  //
  // Misses RAN Parameter ID and only has RAN Parameter Structure

  // RAN Parameter ID
  // Mandatory
  // 9.3.8
  //1.. 4294967295
  // Let's ignore the english written standard and believe the ASN.1 is the correct
  //  uint32_t ran_param_id;

  // RAN Parameter Structure
  // Mandatory
  // 9.3.12
  //ran_param_struct_t ran_param_struct;

  // RAN Parameter ID
  // Mandatory
  // 9.3.8
  //1.. 4294967295
  // uint32_t ran_param_id;

  // RAN Parameter Structure
  // Mandatory
  // 9.3.12
  ran_param_struct_t ran_param_struct;

} lst_ran_param_t;

void free_lst_ran_param(lst_ran_param_t* src);

bool eq_lst_ran_param(lst_ran_param_t const* m0, lst_ran_param_t const* m1);

lst_ran_param_t cp_lst_ran_param(lst_ran_param_t const* src);

#endif

