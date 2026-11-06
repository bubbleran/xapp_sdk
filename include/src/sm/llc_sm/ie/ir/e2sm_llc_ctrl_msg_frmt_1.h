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

#ifndef E2SM_LLC_CTRL_MSG_FRMT_1_MIR_H
#define E2SM_LLC_CTRL_MSG_FRMT_1_MIR_H 

#include "list_logical_channel_ue_id.h"
#include "list_dl_sched_ctrl.h"

#include <stdbool.h>

typedef enum{
  LOGICAL_CHANNEL_HANDLING_CONTROL_LLC_CTRL_MSG_FRMT_1_E,
  DL_SCHEDULING_CONTROL_LLC_CTRL_MSG_FRMT_1_E,
  END_LLC_CTRL_MSG_FRMT_1_E
} ctrl_type_llc_ctrl_msg_frmt_1_e;

typedef struct{
  ctrl_type_llc_ctrl_msg_frmt_1_e type;
  union{
    // 8.3.25
    lst_logical_channel_ue_id_t lst_log; 
    // 8.3.26
    lst_dl_sched_ctrl_t lst_dl_sched_ctrl;
  };

} e2sm_llc_ctrl_msg_frmt_1_t;

e2sm_llc_ctrl_msg_frmt_1_t cp_e2sm_llc_ctrl_msg_frmt_1(e2sm_llc_ctrl_msg_frmt_1_t const* src);

void free_e2sm_llc_ctrl_msg_frmt_1(e2sm_llc_ctrl_msg_frmt_1_t* src);

bool eq_e2sm_llc_ctrl_msg_frmt_1(e2sm_llc_ctrl_msg_frmt_1_t const* m0, e2sm_llc_ctrl_msg_frmt_1_t const* m1);

#endif
