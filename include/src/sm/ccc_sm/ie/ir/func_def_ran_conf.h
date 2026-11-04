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

#ifndef FUNC_DEF_RAN_CONF_H
#define FUNC_DEF_RAN_CONF_H

#include "attribute.h"
#include "../../../../util/byte_array.h"
#include "report_type.h"
#include "supported_services.h"

typedef struct {
  // Attribute name
  // Mandatory
  // 9.3.8
  byte_array_t attribute_name;

  // Supported Services
  // Mandatory
  // 9.2.2.2
  supported_services_t supported_services;

} lst_sp_attributes_t;

typedef struct {
  // RAN configuration structure name
  // Mandatory
  // 9.3.7
  byte_array_t ran_conf_str_name;

  // List of supported attributes
  // [0..65535]
  size_t sz_lst_sp_attributes;
  lst_sp_attributes_t* lst_sp_attributes;

} func_def_ran_conf_t;

void free_func_def_ran_conf(func_def_ran_conf_t* src);

bool eq_func_def_ran_conf(func_def_ran_conf_t const* m0, func_def_ran_conf_t const* m1);

func_def_ran_conf_t cp_func_def_ran_conf(func_def_ran_conf_t const* src);

#endif

