/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef ACT_DEF_RAN_CONF_H
#define ACT_DEF_RAN_CONF_H

#include "attribute.h"
#include "../../../../util/byte_array.h"
#include "report_type.h"

typedef struct{
  // Report Type
  // Mandatory
  // 9.3.9
  report_type_e report_type;

  // RAN Configuration Structure Name
  // Mandatory
  // 9.3.7
  byte_array_t ran_conf_name;

  // [0 - 66535]
  size_t sz_attribute;
  attribute_t* attribute;

} act_def_ran_conf_t;

void free_act_def_ran_conf(act_def_ran_conf_t* src);

bool eq_act_def_ran_conf(act_def_ran_conf_t const* m0, act_def_ran_conf_t const* m1);

act_def_ran_conf_t cp_act_def_ran_conf(act_def_ran_conf_t const* src);

#endif

