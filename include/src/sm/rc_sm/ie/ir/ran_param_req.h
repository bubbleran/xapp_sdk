#ifndef RAN_PARAM_REQ_E2SM_RC_H
#define RAN_PARAM_REQ_E2SM_RC_H

#include <stdint.h>
#include "ran_parameter_value_type.h"

//9.2.1.4.6
typedef struct{

  // RAN Parameter ID
  // Mandatory
  // 9.3.8
  // 1 4294967295,
  uint32_t ran_param_id;

  // RAN Parameter Value Type
  // Mandatory
  // 9.3.11
 ran_param_val_type_t ran_param;

} ran_param_req_t;

void free_ran_param_req(ran_param_req_t* src);

bool eq_ran_param_req( ran_param_req_t const* m0,  ran_param_req_t const* m1);

ran_param_req_t cp_ran_param_req( ran_param_req_t const* src );

#endif
