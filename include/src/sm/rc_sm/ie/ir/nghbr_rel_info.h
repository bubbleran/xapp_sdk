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

#ifndef NEIGHBOUR_RELATION_INFORMATION_MIR_H
#define NEIGHBOUR_RELATION_INFORMATION_MIR_H 

#include <stdlib.h>

#include "../../../../lib/sm/ie/cell_arfcn.h"
#include "../../../../lib/sm/ie/cell_pci.h"

#include "nghbr_cell.h"

// 9.3.38
// Neighbour Relation Information
typedef struct{
  // Serving Cell PCI
  // Mandatory
  // 9.3.39
  cell_pci_t pci;

  // Serving Cell ARFCN
  // Mandatory
  // 9.3.40
  cell_arfcn_t arfcn;

  // Neighbour Cell List
  // [1,65535]
  size_t sz_nghbr_cell;
  nr_nghbr_cell_t* nghbr_cell;

} nghbr_rel_info_t;

void free_nghbr_rel_info(nghbr_rel_info_t* src);

bool eq_nghbr_rel_info(nghbr_rel_info_t const* m0, nghbr_rel_info_t const* m1);

nghbr_rel_info_t cp_nghbr_rel_info( nghbr_rel_info_t const* src);


#endif
