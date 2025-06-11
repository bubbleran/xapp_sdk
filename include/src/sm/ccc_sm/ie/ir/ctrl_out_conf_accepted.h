/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef CCC_CTRL_OUT_CONF_ACCEPTED_H
#define CCC_CTRL_OUT_CONF_ACCEPTED_H

#include "../../../../util/byte_array.h"
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

  // Current Values of Attributes
  // Mandatory
  // 8.6.1
  values_of_attributes_t* cur_atr_val;

  // Applied Timestamp
  // Optional
  byte_array_t app_timestamp;

} ctrl_out_conf_accepted_t;

void free_ctrl_out_conf_accepted(ctrl_out_conf_accepted_t * src);

bool eq_ctrl_out_conf_accepted(ctrl_out_conf_accepted_t const* m0, ctrl_out_conf_accepted_t const* m1);

ctrl_out_conf_accepted_t cp_ctrl_out_conf_accepted(ctrl_out_conf_accepted_t const* src);

#endif

