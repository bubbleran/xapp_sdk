#ifndef RAN_PARAMETER_TEST_E2RC_H
#define RAN_PARAMETER_TEST_E2RC_H 

#include "../../../../util/byte_array.h"

#include "ran_param_test_list.h"
#include "ran_param_test_struct.h"
#include "ran_param_elm_key_false.h"
#include "ran_param_elm_key_true.h"

#include <stdbool.h>

typedef enum{

  LIST_RAN_PARAMETER_TYPE,
  STRUCTURE_RAN_PARAMETER_TYPE,
  ELEMENT_WITH_KEY_FLAG_TRUE_RAN_PARAMETER_TYPE,
  ELEMENT_WITH_KEY_FLAG_FALSE_RAN_PARAMETER_TYPE,

  END_RAN_PARAMETER_TYPE

} ran_parameter_type_e ;

// 9.3.30
typedef struct ran_param_test_s  {

  //RAN Parameter ID
  //Mandatory
  //Bug in the standard. 9.3.9 wrote in section 9. 
  //9.3.8 in ASN language. Probably 9.3.8 intended
  //1.. 4294967295
  uint32_t ran_param_id;

  ran_parameter_type_e type;
  union{
    ran_param_test_lst_t lst;
    ran_param_test_strct_t strct;
    ran_parameter_value_t flag_true;
    ran_param_elm_key_false_t flag_false;
  };

} ran_param_test_t;

void free_ran_param_test( ran_param_test_t * src);

bool eq_ran_param_test(ran_param_test_t const* m0, ran_param_test_t const* m1);

ran_param_test_t cp_ran_param_test(ran_param_test_t const* src);

#endif

