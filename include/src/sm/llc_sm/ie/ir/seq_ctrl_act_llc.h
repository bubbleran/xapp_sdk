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

#ifndef SEQ_CTRL_ACT_LLC_E2SM_MIR_H 
#define SEQ_CTRL_ACT_LLC_E2SM_MIR_H  

#include <stdbool.h>
#include <stdint.h>
#include "../../../../util/byte_array.h"


typedef struct{
  // Control Action ID
  // Mandatory
  // 8.3.6
  // [1-65535]
  uint16_t id; 

  // Control Action Name
  // Mandatory
  // 8.3.7
  // [1-150]
  byte_array_t name;

} seq_ctrl_act_llc_t;

seq_ctrl_act_llc_t cp_seq_ctrl_act_llc(seq_ctrl_act_llc_t const* src);

void free_seq_ctrl_act_llc(seq_ctrl_act_llc_t* src);

bool eq_seq_ctrl_act_llc(seq_ctrl_act_llc_t const* m0, seq_ctrl_act_llc_t const* m1);


#endif
