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

#ifndef SERVING_CELL_ARFCN_MIR_H
#define SERVING_CELL_ARFCN_MIR_H 
#include <stdint.h>
#include <stdbool.h>
#include "rat_type.h"

// 9.3.40
// 6.2.2.15
typedef struct{
  // CHOICE RAT type
  // Mandatory
  rat_type_e type;

  union{
    uint32_t nr_arfcn; // [0,3279165]  6.2.3.30  
    uint16_t eutra_arfcn; // [0,65535] 6.2.3.33
  }; 

} cell_arfcn_t;

void free_cell_arfcn(cell_arfcn_t* src);

cell_arfcn_t cp_cell_arfcn(cell_arfcn_t const* src);

bool eq_cell_arfcn(cell_arfcn_t const* m0, cell_arfcn_t const* m1);



#endif
