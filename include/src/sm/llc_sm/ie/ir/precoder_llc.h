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

#ifndef PRECODER_LLC_E2SM_MIR_H
#define PRECODER_LLC_E2SM_MIR_H 

#include "compress_info.h"
#include "precoder_coeff.h"

#include <stdbool.h>

// From 8.3.26  
typedef struct{

  // Compression Information
  // Optional 
  compress_info_t* compress_info;

  // List of Precoder Coefficients 
  // [0,65535] 
  size_t sz_precoder_coeff;
  precoder_coeff_t* precoder_coeff; 

} precoder_llc_t;

precoder_llc_t cp_precoder_llc(precoder_llc_t const* src);

void free_precoder_llc(precoder_llc_t* src);

bool eq_precoder_llc(precoder_llc_t const* m0, precoder_llc_t const* m1);

#endif
