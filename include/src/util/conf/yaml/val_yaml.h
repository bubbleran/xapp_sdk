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

#ifndef VALUE_YAML_MIR_H
#define VALUE_YAML_MIR_H 

#include <stdint.h>

typedef enum{
  INT64_val_e,
  FLOAT64_val_e,
  STRING_val_e,
  LIST_INT64_val_e,
  LIST_FLOAT64_val_e,
  LIST_STRING_val_e,
  NESTED_or_LIST_val_e,
  END_val_e
} val_yaml_e;

typedef struct{
  val_yaml_e type;
  union{
    int64_t i64;
    double f64;
    char* str;
  };
} val_yaml_t;

void free_val_yaml(val_yaml_t*);

#endif
