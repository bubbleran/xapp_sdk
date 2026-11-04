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

#ifndef E2SM_LLC_LOGICAL_CHANNEL_UE_ID_MIR_H
#define E2SM_LLC_LOGICAL_CHANNEL_UE_ID_MIR_H 

#include "../../../../lib/sm/ie/ue_id.h"
#include "log_chn_ctrl.h"
#include <stdbool.h>

// From 8.3.25
typedef struct{
  // 8.3.8
  // UE ID
  // Mandatory
  ue_id_e2sm_t ue_id;

  // List of logical channels
  // controlled by Near-RT RIC to
  // add
  // [0,63]
  size_t sz_log_chn_ctrl_add; 
  log_chn_ctrl_t* log_chn_ctrl_add;

  // [0,63]
  size_t sz_log_chn_ctrl_release; 
  log_chn_ctrl_t* log_chn_ctrl_release;

} logical_channel_ue_id_t;

logical_channel_ue_id_t cp_logical_channel_ue_id(logical_channel_ue_id_t const* src);

bool eq_logical_channel_ue_id(logical_channel_ue_id_t const* m0, logical_channel_ue_id_t const* m1);

void free_logical_channel_ue_id(logical_channel_ue_id_t* src);


#endif
