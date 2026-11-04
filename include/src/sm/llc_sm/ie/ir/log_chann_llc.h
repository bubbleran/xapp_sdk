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

#ifndef LOGICAL_CHANNEL_LLC_E2SM_MIR_H
#define LOGICAL_CHANNEL_LLC_E2SM_MIR_H 

#include <stdbool.h>
#include <stdint.h>

// From 8.3.26    
typedef struct{
  //Logical Channel ID 
  //Mandatory 
  //[1,32]
  uint32_t log_channel_id;

  // TB1 Number of Bytes 
  // Mandatory
  uint32_t tb1_bytes;

  // TB2 Number of Bytes
  // Optional
  uint32_t* tb2_bytes;

} log_chann_llc_t;

log_chann_llc_t cp_log_chann_llc(log_chann_llc_t const* src);

void free_log_chann_llc(log_chann_llc_t* src);

bool eq_log_chann_llc(log_chann_llc_t const* m0, log_chann_llc_t const* m1);


#endif
