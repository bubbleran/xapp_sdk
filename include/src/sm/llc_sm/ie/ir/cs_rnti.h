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

#ifndef CS_RNTI_E2SM_LLC_MIR_H
#define CS_RNTI_E2SM_LLC_MIR_H 

#include <stdbool.h>
#include <stdint.h>

typedef struct{
  // SPS Config Index
  // C-ifSPSLis
  // [0,7]
  uint32_t* sps_config_idx; 

  // Activation 
  // Mandatory
  bool activate;

} cs_rnti_t ;

cs_rnti_t cp_cs_rnti(cs_rnti_t const* src);

void free_cs_rnti(cs_rnti_t* src);

bool eq_cs_rnti(cs_rnti_t const* m0, cs_rnti_t const* m1);


#endif
