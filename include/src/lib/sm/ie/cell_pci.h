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

#ifndef SERVING_CELL_PCI_SM_H 
#define SERVING_CELL_PCI_SM_H  

#include "rat_type.h"
#include <stdbool.h>

// RC SM
// 9.3.39
// E2 SM 
// 6.2.2.14

typedef struct{
  // CHOICE RAT type
  // Mandatory
  rat_type_e type;

  union{
    int nr_pci; // [0,1007]  6.2.3.29 
    int eutra_pci; // [0,503] // 6.2.3.32
  };
} cell_pci_t;

bool eq_cell_pci( cell_pci_t const* m0,  cell_pci_t const* m1);

void free_cell_pci(cell_pci_t* src);

cell_pci_t cp_cell_pci(cell_pci_t const* src);



#endif
