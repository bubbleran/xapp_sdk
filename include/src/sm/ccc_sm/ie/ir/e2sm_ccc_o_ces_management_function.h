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

#ifndef E2SM_CCC_O_CES_MANAGEMENT_FUNCTION_H
#define E2SM_CCC_O_CES_MANAGEMENT_FUNCTION_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "e2sm_ccc_plmn_info.h"

typedef enum{
  TRUE_CES_SWITCH,
  FALSE_CES_SWITCH,
  END_CES_SWITCH
}ces_switch_e;

typedef enum{
  IS_NOT_ENERGY_SAVING_STATE,
  IS_ENERGY_SAVING_STATE,
  END_ENERGY_SAVING_STATE,
}energy_saving_state_e;

typedef enum{
  TO_BE_ENERGY_SAVING_CONTROL,
  TO_BE_NOT_ENERGY_SAVING_CONTROL,
  END_ENERGY_SAVING_CONTROL,
}energy_saving_control_e;

// 8.8.2.5
typedef struct{
  ces_switch_e ces_switch;

  energy_saving_control_e energy_saving_control;

  energy_saving_state_e energy_saving_state;

} e2sm_ccc_o_ces_management_function_t;

void free_e2sm_ccc_o_ces_management_function(e2sm_ccc_o_ces_management_function_t* src);

bool eq_e2sm_ccc_o_ces_management_function(e2sm_ccc_o_ces_management_function_t const* m0, e2sm_ccc_o_ces_management_function_t const* m1);

e2sm_ccc_o_ces_management_function_t cp_e2sm_ccc_o_ces_management_function(e2sm_ccc_o_ces_management_function_t const* src);

#endif

