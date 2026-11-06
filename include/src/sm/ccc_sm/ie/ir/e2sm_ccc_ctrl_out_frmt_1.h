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

#ifndef E2SM_CCC_CTRL_OUT_FRMT_1_H
#define E2SM_CCC_CTRL_OUT_FRMT_1_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "../../../../util/byte_array.h"
#include "ctrl_out_conf_failed.h"
#include "ctrl_out_conf_accepted.h"

// 9.2.1.8.1
typedef struct{
  // Received Timestamp
  // Optional
  byte_array_t rev_timestamp;

  // RAN Configuration Structures Accepted List
  // [0-65535]
  size_t sz_ctrl_out_conf_accepted;
  ctrl_out_conf_accepted_t* ctrl_out_conf_accepted;

  // RAN Configuration Structures Failed List
  // [0-65535]
  size_t sz_ctrl_out_conf_failed;
  ctrl_out_conf_failed_t* ctrl_out_conf_failed;

} e2sm_ccc_ctrl_out_frmt_1_t;

void free_e2sm_ccc_ctrl_out_frmt_1(e2sm_ccc_ctrl_out_frmt_1_t* src);

e2sm_ccc_ctrl_out_frmt_1_t cp_e2sm_ccc_ctrl_out_frmt_1(e2sm_ccc_ctrl_out_frmt_1_t const* src);

bool eq_e2sm_ccc_ctrl_out_frmt_1(e2sm_ccc_ctrl_out_frmt_1_t const* m0, e2sm_ccc_ctrl_out_frmt_1_t const* m1);

#endif

