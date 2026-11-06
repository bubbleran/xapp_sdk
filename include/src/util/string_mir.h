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

#ifndef STRING_DS_MIR_H
#define STRING_DS_MIR_H 

#include <stdlib.h>
#include <stdbool.h>
#include "string_view.h"

typedef struct{
  // Owning iterator
  char* it;
  size_t sz;
} string_t;

void free_string(string_t s);

string_t cp_string(string_t s);

string_t concat_string(string_t m0, string_t m1);

bool eq_string(string_t m0, string_t m1);

bool eq_string_ptr(string_t const* m0, string_t const* m1);

string_t char_to_string(char* src);

string_t string_view_to_string(string_view_t src); 

string_view_t string_to_string_view(string_t src);

#endif
