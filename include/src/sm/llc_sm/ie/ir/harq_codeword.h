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

#ifndef HARQ_CODEWORD_E2SM_LLC_MIR_H
#define HARQ_CODEWORD_E2SM_LLC_MIR_H 

#include <stdbool.h>
#include <stdint.h>


//From 8.3.23
typedef struct{
  // DL SU ACK Count
  // Mandatory
  uint32_t dl_su_ack_cnt; 
  // DL SU NACK Count
  // Mandatory
  uint32_t dl_su_nack_cnt;
  // DL SU DTX Count
  // Mandatory
  uint32_t dl_su_dtx_cnt; 
  // DL MU ACK Count
  // Mandatory
  uint32_t dl_mu_ack_cnt;
  // DL MU NACK Count
  // Mandatory
  uint32_t dl_mu_nack_cnt;

  // DL MU DTX Count
  // Mandatory
  uint32_t dl_mu_dtx_cnt;

} harq_codeword_t;

harq_codeword_t cp_harq_codeword(harq_codeword_t const* src); 

void free_harq_codeword(harq_codeword_t* src); 

bool eq_harq_codeword(harq_codeword_t const* m0,harq_codeword_t const* m1); 

#endif
