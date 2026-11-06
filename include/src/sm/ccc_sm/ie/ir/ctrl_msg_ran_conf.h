/*

Copyright (C) 2026 BubbleRAN

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see http://www.gnu.org/licenses/.
*/

#ifndef CTRL_MSG_RAN_CONF_H
#define CTRL_MSG_RAN_CONF_H

#include <stdbool.h>

#include "../../../../util/byte_array.h"
#include "values_of_attributes.h"
#include "change_type.h"

typedef struct{
  // RAN Configuration Structure Name
  // Mandatory
  // 9.3.7
  byte_array_t ran_conf_name;

  // Values of Attributes
  // Mandatory
  values_of_attributes_t* vals_attributes;

  // Old Values of Attributes
  // Mandatory
  values_of_attributes_t* old_vals_attributes;

} ctrl_msg_ran_conf_t;

void free_ctrl_msg_ran_conf(ctrl_msg_ran_conf_t* src);

bool eq_ctrl_msg_ran_conf(ctrl_msg_ran_conf_t const* m0, ctrl_msg_ran_conf_t const* m1);

ctrl_msg_ran_conf_t cp_ctrl_msg_ran_conf(ctrl_msg_ran_conf_t const* src);

#endif

