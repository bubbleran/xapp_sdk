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

#ifndef SRS_LLC_MIR_H
#define SRS_LLC_MIR_H 

#include "srs_rx_antenna.h"

#include <stdbool.h>

// 8.3.19
typedef struct{
  // [1,65535]
  size_t sz_srs_rx_antenna;
  srs_rx_antenna_t* rx; 
} srs_llc_t;

void free_srs_llc(srs_llc_t* src);

bool eq_srs_llc( srs_llc_t const* m0, srs_llc_t const* m1);

srs_llc_t cp_srs_llc(srs_llc_t const* src);

#endif
