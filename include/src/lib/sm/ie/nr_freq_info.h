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

#ifndef NR_FREQ_INFO_RC_SM_MIR_H
#define NR_FREQ_INFO_RC_SM_MIR_H 

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "nr_frq_bnd_it.h"

// 9.3.44
// 6.2.3.36.
// Bug in the standard!!!
// 6.2.3.36 should be 6.2.3.35
// for O-RAN.WG3.E2SM-R003-v05.00
// 6.2.3.35
typedef struct {
  //NR ARFCN
  //Mandatory
  //6.2.3.30
  uint32_t arfcn; // [0,3279165]

  // [1,32]
  nr_frq_bnd_it_t* frq_bnd_it;
  size_t sz_frq_bnd_it;

  // NRFrequency Shift
  // 7p5khz
  // Optional
  bool* freq_shift_7p5khz;

} nr_freq_info_t;

void free_nr_freq_info(nr_freq_info_t* src);

bool eq_nr_freq_info(nr_freq_info_t const* m0, nr_freq_info_t const* m1);

nr_freq_info_t cp_nr_freq_info(nr_freq_info_t const* src);



#endif
