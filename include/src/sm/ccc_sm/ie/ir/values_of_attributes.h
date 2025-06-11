/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
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

