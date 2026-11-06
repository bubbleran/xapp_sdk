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

#ifndef ELEMENT_YAML_MIR_H
#define ELEMENT_YAML_MIR_H 

#include "kv_pair_yaml.h"

typedef struct elm{
  kv_pair_yaml_t kv;  
  int indentation;
} elm_yaml_t;

void free_elm_yaml(elm_yaml_t*);

#endif
