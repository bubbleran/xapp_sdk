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

#ifndef PRECODER_COEFF_E2SM_LLC_MIR_H
#define PRECODER_COEFF_E2SM_LLC_MIR_H 

#include <stdbool.h>
#include <stdint.h>

// From 8.3.26  
typedef struct{

  // Precoder Coefficient I
  // Mandatory
  int32_t i;

  // Precoder Coefficient Q
  // Mandatory
  int32_t q;

} precoder_coeff_t;

precoder_coeff_t cp_precoder_coeff(precoder_coeff_t src);

void free_precoder_coeff(precoder_coeff_t src);

bool eq_precoder_coeff(precoder_coeff_t const* m0,  precoder_coeff_t const* m1); 

#endif
