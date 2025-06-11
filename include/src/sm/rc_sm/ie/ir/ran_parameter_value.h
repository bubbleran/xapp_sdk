#ifndef RAN_PARAMETER_VALUE_E2RC_H
#define RAN_PARAMETER_VALUE_E2RC_H 

#include <stdbool.h>
#include <stdint.h>
#include "../../../../util/byte_array.h"

// 9.3.14
typedef enum{
  BOOLEAN_RAN_PARAMETER_VALUE,
  INTEGER_RAN_PARAMETER_VALUE,
  REAL_RAN_PARAMETER_VALUE,
  BIT_STRING_RAN_PARAMETER_VALUE,
  OCTET_STRING_RAN_PARAMETER_VALUE,
  PRINTABLESTRING_RAN_PARAMETER_VALUE,
  END_RAN_PARAMETER_VALUE 
} ran_parameter_value_e; 

// 9.3.14
typedef struct ran_parameter_value_s{
  ran_parameter_value_e type;
  union{
    bool bool_ran;
    int64_t int_ran;
    double real_ran;
    byte_array_t bit_str_ran;
    byte_array_t octet_str_ran;
    byte_array_t printable_str_ran;
  };
}  ran_parameter_value_t;

void free_ran_parameter_value(ran_parameter_value_t* src);

bool eq_ran_parameter_value(ran_parameter_value_t const* m0, ran_parameter_value_t const* m1);

ran_parameter_value_t cp_ran_parameter_value(ran_parameter_value_t const* src);

#endif

