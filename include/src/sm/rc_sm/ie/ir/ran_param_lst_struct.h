#ifndef RAN_PARAM_LST_STRUCT_H
#define RAN_PARAM_LST_STRUCT_H 

#include <stdint.h>
#include "../../../../util/byte_array.h"

// Forward declaration to avoid cycle
typedef struct ran_param_def_s ran_param_def_t;

typedef struct {
  // RAN Parameter ID
  // Mandatory
  // 9.3.8
  uint32_t ran_param_id;

  // RAN Parameter Name
  // Mandatory
  // 9.3.9
  byte_array_t ran_param_name;

  // RAN Parameter Definition
  // Optional
  // 9.3.51
  ran_param_def_t* ran_param_def;

} ran_param_lst_struct_t;

void free_ran_param_lst_struct(ran_param_lst_struct_t* src); 

bool eq_ran_param_lst_struct(ran_param_lst_struct_t const* m0,  ran_param_lst_struct_t const* m1); 

ran_param_lst_struct_t cp_ran_param_lst_struct(ran_param_lst_struct_t const* src);

#endif


