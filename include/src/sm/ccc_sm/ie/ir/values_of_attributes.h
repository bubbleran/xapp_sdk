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

#ifndef VALUES_OF_ATTRIBUTES_H
#define VALUES_OF_ATTRIBUTES_H

#include "e2sm_ccc_o_gnb_du_function.h"
#include "e2sm_ccc_o_gnb_cu_cp_function.h"
#include "e2sm_ccc_o_gnb_cu_up_function.h"
#include "e2sm_ccc_o_rrm_policy_ratio.h"
#include "e2sm_ccc_o_nr_cell_cu.h"
#include "e2sm_ccc_o_nr_cell_du.h"
#include "e2sm_ccc_o_nr_cell_cu.h"
#include "e2sm_ccc_o_bwp.h"
#include "e2sm_ccc_o_ces_management_function.h"

typedef enum{
  VALUES_OF_ATTRIBUTES_O_GNBDUFunction,
  VALUES_OF_ATTRIBUTES_O_GNBCUCPFunction,
  VALUES_OF_ATTRIBUTES_O_GNBCUUPFunction,
  VALUES_OF_ATTRIBUTES_O_RRMPolicyRatio,
  VALUES_OF_ATTRIBUTES_O_NRCellCU,
  VALUES_OF_ATTRIBUTES_O_NRCellDU,
  VALUES_OF_ATTRIBUTES_O_BWP,
  VALUES_OF_ATTRIBUTES_O_CESManagementFunction,

  VALUES_OF_ATTRIBUTES_END,
} values_of_attributes_e;

typedef struct{
  values_of_attributes_e values_of_attributes_type;

  union {
    e2sm_ccc_o_gnb_du_function_t e2sm_ccc_o_gnb_du_function;
    e2sm_ccc_o_gnb_cu_cp_function_t e2sm_ccc_o_gnb_cu_cp_function;
    e2sm_ccc_o_gnb_cu_up_function_t e2sm_ccc_o_gnb_cu_up_function;
    e2sm_ccc_o_rrm_policy_ratio_t e2sm_ccc_o_rrm_policy_ratio;
    e2sm_ccc_o_nr_cell_cu_t e2sm_ccc_o_nr_cell_cu;
    e2sm_ccc_o_nr_cell_du_t e2sm_ccc_o_nr_cell_du;
    e2sm_ccc_o_bwp_t e2sm_ccc_o_bwp;
    e2sm_ccc_o_ces_management_function_t e2sm_ccc_o_ces_management_function;
  };

} values_of_attributes_t;

void free_values_of_attributes(values_of_attributes_t* src);

bool eq_values_of_attributes(values_of_attributes_t const* m0, values_of_attributes_t const* m1);

values_of_attributes_t cp_values_of_attributes(values_of_attributes_t const* src);

#endif

