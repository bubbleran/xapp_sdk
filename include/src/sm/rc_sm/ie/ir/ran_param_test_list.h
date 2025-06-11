#ifndef RAN_PARAMETER_TEST_LIST_E2SM_RC_H
#define RAN_PARAMETER_TEST_LIST_E2SM_RC_H

#include <stdbool.h>
#include <stdlib.h>


// Forward declaration to avoid cycle
typedef struct ran_param_test_s  ran_param_test_t;

typedef struct{

  // [1- 65535]
  size_t sz_lst;
  // RAN Parameter Testing
  // 9.3.30
  ran_param_test_t* ran_param_test;

} ran_param_test_lst_t;

void free_ran_param_test_lst( ran_param_test_lst_t* src);

bool eq_ran_param_test_lst(ran_param_test_lst_t const* m0, ran_param_test_lst_t const* m1);

ran_param_test_lst_t cp_ran_param_test_lst(ran_param_test_lst_t const* src);

#endif
