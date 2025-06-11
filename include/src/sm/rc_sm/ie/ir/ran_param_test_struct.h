#ifndef RAN_PARAMETER_TEST_STRUCT_E2SM_H
#define RAN_PARAMETER_TEST_STRUCT_E2SM_H 

#include <stdbool.h>
#include <stdlib.h>


// Forward declaration to avoid cycle
typedef struct ran_param_test_s  ran_param_test_t;

typedef struct{
  // [1- 65535]
  size_t sz_strct;
  // RAN Parameter Testing
  // 9.3.30
  ran_param_test_t* ran_param_test;
}ran_param_test_strct_t  ;

void free_ran_param_test_strct(ran_param_test_strct_t* src);

bool eq_ran_param_test_strct(ran_param_test_strct_t const* m0, ran_param_test_strct_t const* m1);

ran_param_test_strct_t cp_ran_param_test_strct( ran_param_test_strct_t const* src);

#endif

