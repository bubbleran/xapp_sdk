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

#ifndef E2SM_CCC_ACTION_DEFINITION_FORMAT_1
#define E2SM_CCC_ACTION_DEFINITION_FORMAT_1

#include <stdbool.h>
#include <stdlib.h>

#include "act_def_ran_conf.h"

// 9.2.1.2.2
typedef struct{
  // List of Node-Level RAN configuration Structures
  // [1-256]
  size_t sz_act_def_ran_conf;
  act_def_ran_conf_t* act_def_ran_conf;

} e2sm_ccc_act_def_frmt_1_t; 

void free_e2sm_ccc_act_def_frmt_1(e2sm_ccc_act_def_frmt_1_t* src);

bool eq_e2sm_ccc_act_def_frmt_1(e2sm_ccc_act_def_frmt_1_t const* m0, e2sm_ccc_act_def_frmt_1_t const* m1);

e2sm_ccc_act_def_frmt_1_t cp_e2sm_ccc_act_def_frmt_1(e2sm_ccc_act_def_frmt_1_t const* src);

#endif

