/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef IND_MSG_RAN_CONF_H
#define IND_MSG_RAN_CONF_H

#include <stdbool.h>

#include "../../../../util/byte_array.h"
#include "values_of_attributes.h"
#include "change_type.h"

typedef struct{
  // Change Type
  // Mandatory
  change_type_e change_type;

  // RAN Configuration Structure Name
  // Mandatory
  // 9.3.7
  byte_array_t ran_conf_name;

  // Values of Attributes
  // Mandatory
  values_of_attributes_t* vals_attributes;

  // Old Values of Attributes
  // Optional
  values_of_attributes_t* old_vals_attributes;

} ind_msg_ran_conf_t;

void free_ind_msg_ran_conf(ind_msg_ran_conf_t* src);

bool eq_ind_msg_ran_conf(ind_msg_ran_conf_t const* m0, ind_msg_ran_conf_t const* m1);

ind_msg_ran_conf_t cp_ind_msg_ran_conf(ind_msg_ran_conf_t const* src);

#endif

