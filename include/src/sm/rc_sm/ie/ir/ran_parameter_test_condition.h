#ifndef RAN_PARAMETER_TEST_CONDITION_E2RC_H
#define RAN_PARAMETER_TEST_CONDITION_E2RC_H 

#include <stdbool.h>

typedef enum{

  EQUAL_RAN_PARAM_TEST_COND_COMP,
  DIFFERENCE_RAN_PARAM_TEST_COND_COMP, 
  GREATERTHAN_RAN_PARAM_TEST_COND_COMP,
  LESSTHAN_RAN_PARAM_TEST_COND_COMP, 
  CONTAINS_RAN_PARAM_TEST_COND_COMP, 
  STARTS_WITH_RAN_PARAM_TEST_COND_COMP,

  END_RAN_PARAM_TEST_COND_COMP, 

}ran_param_test_cond_comp_e ;

typedef enum{

  PRESENT_RAN_PARAM_TEST_COND_PRESENCE,
  CONFIGURED_RAN_PARAM_TEST_COND_PRESENCE, 
  ROLLOVER_RAN_PARAM_TEST_COND_PRESENCE, 
  NON_ZERO_RAN_PARAM_TEST_COND_PRESENCE,

  END_RAN_PARAM_TEST_COND_PRESENCE,

} ran_param_test_cond_presence_e ;


typedef enum{
  COMPARISON_RAN_PARAM_TEST_COND,
  PRESENCE_RAN_PARAM_TEST_COND,

  END_RAN_PARAM_TEST_COND,
} ran_param_test_cond_e ;

typedef struct{

 ran_param_test_cond_e cond;
  union{
    ran_param_test_cond_comp_e comp;
    ran_param_test_cond_presence_e presence; 
  };

} ran_param_test_cond_t; 

void free_ran_param_test_cond(ran_param_test_cond_t* src);

bool eq_ran_param_test_cond(ran_param_test_cond_t const* m0, ran_param_test_cond_t const* m1); 

ran_param_test_cond_t cp_ran_param_test_cond(ran_param_test_cond_t const src);

#endif
