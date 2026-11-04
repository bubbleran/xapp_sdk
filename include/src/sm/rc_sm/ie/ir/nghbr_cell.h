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

#ifndef NGHBR_CELL_RC_SM_MIR_H
#define NGHBR_CELL_RC_SM_MIR_H 

#include <stdbool.h>

#include "../../../../lib/sm/ie/rat_type.h"
#include "nr_nghbr_cell.h"
#include "eutra_nghbr_cell.h"

// Neighbour Cell List
// 9.3.38
typedef struct{
  // CHOICE RAT type
  // Mandatory
  rat_type_e type;

  union {
    nr_nghbr_cell_t nr;
    eutra_nghbr_cell_t eutra;
  };

} nghbr_cell_t;

void free_nghbr_cell(nghbr_cell_t* src);

bool eq_nghbr_cell(nghbr_cell_t const* m0, nghbr_cell_t const* m1);

#endif
