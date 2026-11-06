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

