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

#ifndef LOGICAL_OR_E2SM_LLC_MIR_H
#define LOGICAL_OR_E2SM_LLC_MIR_H 

#include <stdbool.h>

// 8.3.11
// If set to “true”,
// logical connection
// to the next
// condition is “or”.
// Otherwise, “and”.
typedef enum{
  TRUE_LOGICAL_OR_LLC_E,
  FALSE_LOGICAL_OR_LLC_E,

  END_LOGICAL_OR_LLC_E
} logical_or_llc_e;

bool eq_logical_or_llc(logical_or_llc_e const* m0, logical_or_llc_e const* m1);

#endif
