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

#ifndef STRING_VIEW_MIR_H
#define STRING_VIEW_MIR_H 

#include <stdlib.h>
#include <stdbool.h>

// Non-owning ds. Do not try to free it!
typedef struct{
  // Non-owning iterator
  char* it;
  size_t sz;
} string_view_t;

bool eq_string_view(string_view_t m0, string_view_t m1);

size_t concat_str(char* dst, string_view_t m0, string_view_t m1);

size_t add_str(char* dst, string_view_t m0);

#endif

