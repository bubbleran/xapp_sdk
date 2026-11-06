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

#ifndef LOGICAL_CHANNEL_CONTROL_E2SM_LLC_MIR_H
#define LOGICAL_CHANNEL_CONTROL_E2SM_LLC_MIR_H 

#include "slot_info.h"
#include <stdbool.h>

// From 8.3.25
typedef struct{

  // Logical Channel ID 
  // Mandatory 
  // [1,32]
  uint32_t log_channel_id;

  //8.3.17
  //Starting Slot number 
  //Mandatory 
  slot_info_t slot_info; 

} log_chn_ctrl_t;

log_chn_ctrl_t cp_log_chn_ctrl(log_chn_ctrl_t const* src);

void free_log_chn_ctrl(log_chn_ctrl_t* src);

bool eq_log_chn_ctrl(log_chn_ctrl_t const* m0,log_chn_ctrl_t const* m1);

#endif
