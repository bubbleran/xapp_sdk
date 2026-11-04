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

#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "../../../../util/byte_array.h"

typedef struct {
  // Attribute name
  // Mandatory
  // 9.3.8
  byte_array_t attribute_name;
} attribute_t;

void free_attribute(attribute_t* src);

bool eq_attribute(attribute_t const* m0, attribute_t const* m1);

attribute_t cp_attribute(attribute_t const* src);

#endif

