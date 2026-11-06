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

