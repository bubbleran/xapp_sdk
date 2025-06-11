/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef CCC_CTRL_OUT_CONF_FAILED_H
#define CCC_CTRL_OUT_CONF_FAILED_H

#include "../../../../util/byte_array.h"
#include "cause.h"
#include "values_of_attributes.h"

typedef struct{
  // RAN Configuration Structure Name
  // Mandatory
  // 9.3.7
  byte_array_t ran_conf_name;

  // Old Values of Attributes
  // Mandatory
  // 8.6.1
  values_of_attributes_t* old_atr_val;

  // Requested Values of Attributes
  // Mandatory
  // 8.6.1
  values_of_attributes_t* req_atr_val;

  // Cause
  // Mandatory
  // 9.3.11
  ccc_cause_e cause;

} ctrl_out_conf_failed_t;

void free_ctrl_out_conf_failed(ctrl_out_conf_failed_t * src);

bool eq_ctrl_out_conf_failed(ctrl_out_conf_failed_t const* m0, ctrl_out_conf_failed_t const* m1);

ctrl_out_conf_failed_t cp_ctrl_out_conf_failed(ctrl_out_conf_failed_t const* src);

#endif

