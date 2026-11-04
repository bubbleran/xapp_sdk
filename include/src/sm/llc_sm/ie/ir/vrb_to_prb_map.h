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

#ifndef VRB_TO_PRB_MAP_LLC_E2SM_MIR_H
#define VRB_TO_PRB_MAP_LLC_E2SM_MIR_H 

#include <stdbool.h>

typedef enum{
  INTERLEAVED_VRB_TO_PRB_MAP,
  END_VRB_TO_PRB_MAP_E
} vrb_to_prb_map_e;

bool eq_vrb_to_prb_map(vrb_to_prb_map_e const* m0, vrb_to_prb_map_e const* m1);

#endif
