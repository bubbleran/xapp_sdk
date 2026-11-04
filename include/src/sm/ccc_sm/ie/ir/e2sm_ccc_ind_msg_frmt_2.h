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

#ifndef E2SM_CCC_INDICATION_MSG_FORMAT_2_H
#define E2SM_CCC_INDICATION_MSG_FORMAT_2_H

#include <stdbool.h>

#include "../../../../lib/sm/ie/cell_global_id.h"
#include "../../../../util/byte_array.h"
#include "change_type.h"
#include "ind_msg_ran_conf.h"

typedef struct {
  // Cell global id
  // Mandatory
  // 9.3.6
  cell_global_id_t cell_global_id;

  // List of Configuration Structures Reported
  // [1 - 65535]
  size_t sz_ind_msg_ran_conf;
  ind_msg_ran_conf_t* ind_msg_ran_conf;

} ind_msg_cell_report_t;

//9.2.1.4.2
typedef struct{
  // List of Cells Reported
  // [1 - 65535]
  size_t sz_ind_msg_cell_report;
  ind_msg_cell_report_t* ind_msg_cell_report;

} e2sm_ccc_ind_msg_frmt_2_t;

void free_ind_msg_cell_report(ind_msg_cell_report_t* src);

bool eq_ind_msg_cell_report(ind_msg_cell_report_t const* m0,  ind_msg_cell_report_t const* m1);

ind_msg_cell_report_t cp_ind_msg_cell_report(ind_msg_cell_report_t const* src);

void free_e2sm_ccc_ind_msg_frmt_2(e2sm_ccc_ind_msg_frmt_2_t const* src);

bool eq_e2sm_ccc_ind_msg_frmt_2( e2sm_ccc_ind_msg_frmt_2_t const* m0,  e2sm_ccc_ind_msg_frmt_2_t const* m1);

e2sm_ccc_ind_msg_frmt_2_t cp_e2sm_ccc_ind_msg_frmt_2(e2sm_ccc_ind_msg_frmt_2_t const* src);

#endif

