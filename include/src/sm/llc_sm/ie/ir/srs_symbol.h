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

#ifndef SRS_E2SM_LLC_SYMBOL_MIR_H
#define SRS_E2SM_LLC_SYMBOL_MIR_H 

#include <stdbool.h>
#include <stdint.h>
#include "../../../../util/byte_array.h"

// From 8.3.19
typedef struct{
  // SRS Compression Header
  // C-ifStaticSRS
  uint8_t hdr;

  //  As defined in O-RAN
  // WG4.TS.CUS [8] Table 8.3.2-1
  // starting from Octet 13.
  // pag. 368
  byte_array_t raw_iq;

} srs_symbol_t;

srs_symbol_t cp_srs_symbol(srs_symbol_t const* src); 

void free_srs_symbol(srs_symbol_t* src); 

bool eq_srs_symbol(srs_symbol_t const* m0, srs_symbol_t const* m1);

#endif
