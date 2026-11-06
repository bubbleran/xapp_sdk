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

#ifndef NR_FREQUENCY_BAND_ITEM_E2SM_MIR_H
#define NR_FREQUENCY_BAND_ITEM_E2SM_MIR_H 

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>


// 6.2.3.35
typedef struct
{
  uint16_t bnd; // [1,1024]

  // [0,32]
  size_t sz_sul;
  uint16_t* sul_bnd_it; // [1,1024]

} nr_frq_bnd_it_t;

void free_nr_frq_bnd_it( nr_frq_bnd_it_t* src);

bool eq_nr_frq_bnd_it( nr_frq_bnd_it_t const* m0,  nr_frq_bnd_it_t const* m1);

nr_frq_bnd_it_t cp_nr_frq_bnd_it(nr_frq_bnd_it_t const* src);

#endif

