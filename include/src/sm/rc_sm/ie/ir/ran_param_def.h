#ifndef RAN_PARAM_DEFINITION_H
#define RAN_PARAM_DEFINITION_H

#include <stdint.h>
#include "../../../../util/byte_array.h"
#include "ran_param_type.h"


typedef enum {
  LIST_RAN_PARAMETER_DEF_TYPE,
  STRUCTURE_RAN_PARAMETER_DEF_TYPE,

  END_RAN_PARAMETER_DEF_TYPE

} ran_parameter_def_type_e;

// 9.3.51
typedef struct ran_param_def_s{

  // RAN Parameter Type
  // Mandatory
  ran_parameter_def_type_e type;

  union {
    ran_param_type_t* lst;
    ran_param_type_t* strct;
  };

} ran_param_def_t;

void free_ran_param_def(ran_param_def_t* src);

bool eq_ran_param_def(ran_param_def_t const* m0, ran_param_def_t const* m1);

ran_param_def_t cp_ran_param_def(ran_param_def_t const* src);


#endif
