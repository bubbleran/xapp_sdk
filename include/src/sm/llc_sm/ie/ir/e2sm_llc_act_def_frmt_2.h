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

#ifndef E2SM_LLC_ACTION_DEF_FORMAT_2_MIR_H
#define E2SM_LLC_ACTION_DEF_FORMAT_2_MIR_H 

#include "lower_layer_measure.h"
#include <stdbool.h>
#include <stddef.h>

// 8.2.1.2.2
typedef struct{
  // 8.3.16
  // [1,65535]
  size_t sz_llm;
  lower_layer_measure_e* llm;
} e2sm_llc_act_def_frmt_2_t;

e2sm_llc_act_def_frmt_2_t cp_e2sm_llc_act_def_frmt_2(e2sm_llc_act_def_frmt_2_t const* src);

bool eq_e2sm_llc_act_def_frmt_2(e2sm_llc_act_def_frmt_2_t const* m0, e2sm_llc_act_def_frmt_2_t const* m1);

void free_e2sm_llc_act_def_frmt_2( e2sm_llc_act_def_frmt_2_t* src);

#endif
