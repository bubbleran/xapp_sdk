#ifndef PARAMETER_REPORT_DEFINITION_H
#define PARAMETER_REPORT_DEFINITION_H

#include <stdbool.h>
#include <stdint.h>

#include "ran_param_def.h"
 
typedef struct{
  // RAN Parameter ID
  // Mandatory
  // 9.3.8
  // [1 - 4294967295]
  uint32_t ran_param_id;

  // RAN Parameter Definition
  // Optional
  // 9.3.51
  ran_param_def_t* ran_param_def;

} param_report_def_t;

void free_param_report_def(param_report_def_t* src);

bool eq_param_report_def(param_report_def_t const* m0, param_report_def_t const* m1);

param_report_def_t cp_param_report_def(param_report_def_t const* src);

#endif

