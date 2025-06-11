#ifndef RAN_PARAMETER_E2RC_H
#define RAN_PARAMETER_E2RC_H 

#include <stdlib.h>

#include "ran_param_test.h"

// 9.3.29
typedef struct{

  // [1-255]
  size_t sz_ran_param_test;
  ran_param_test_t* ran_param_test;

} ran_param_t; 

#endif

