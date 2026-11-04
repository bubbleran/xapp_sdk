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

#ifndef SCHEDULE_LOGICAL_CHANNELS_E2SM_LLC_MIR_H
#define SCHEDULE_LOGICAL_CHANNELS_E2SM_LLC_MIR_H 

#include <stdbool.h>
#include <stdint.h>

// 0= Other
// 1= Information arrived too late
// 2= LCID overwritten by other transmissions.
// 3= Reached maximum number of DCIs for the slot.
// 4= UE not available.
// 5= Resources used for retransmission/s
// 6= Insufficient RLC queue depth

typedef enum{
  OTHER_CAUSE_LLC_E,
  INFO_TOO_LATE_CAUSE_LLC_E,
  LCID_OVERWRITTEN_CAUSE_LLC_E,
  MAX_NUM_DCI_FOR_SLOT_CAUSE_LLC_E,
  UE_NOT_AVAIL_CAUSE_LLC_E,
  RESOURCE_USED_RX_CAUSE_LLC_E,
  INSUFFICIENT_RLC_QUEUE_DEPTH_CAUSE_LLC_E,
  END_CAUSE_LLC_E
} cause_llc_e;


// From 8.3.27
// List of DL Grants
typedef struct{

  // Logical Channel ID 
  // Mandatory
  // [1,32]
  uint32_t log_chnl_id; 

  // Number of Bytes Scheduled
  // Mandatory
  uint32_t num_bytes_sched;

  // Cause 
  // Mandatory
  cause_llc_e cause;

} schd_log_chnl_t;

schd_log_chnl_t cp_schd_log_chnl(schd_log_chnl_t const* src);

void free_schd_log_chnl(schd_log_chnl_t* src);

bool eq_schd_log_chnl(schd_log_chnl_t const* m0, schd_log_chnl_t const* m1);

#endif
