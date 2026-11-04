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

#ifndef PDSCH_SMG_E2SM_LLC_MIR_H
#define PDSCH_SMG_E2SM_LLC_MIR_H 

#include <stdbool.h>
#include <stdint.h>


// From 8.3.26 
typedef struct{

  // Precoder ID
  // Mandatory
  // [0,63]
  uint32_t precoder_id;

  // SMG Priority
  // Optional
  // [0,31]
  uint32_t* smg_priority;

  // Start RB
  // Mandatory
  uint32_t start_rb;

  // Number of RBs
  // Mandatory
  uint32_t num_rb;

  // Start Symbol 
  // Mandatory
  uint32_t start_symb;

  // Number of Symbols
  // Mandatory
  uint32_t num_symb;

} pdsch_smg_t; 

pdsch_smg_t cp_pdsch_smg(pdsch_smg_t const* src); 

void free_pdsch_smg(pdsch_smg_t* src); 

bool eq_pdsch_smg(pdsch_smg_t const* m0, pdsch_smg_t const* m1);

#endif
