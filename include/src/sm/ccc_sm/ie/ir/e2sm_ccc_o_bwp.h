/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef E2SM_CCC_O_BWP_H
#define E2SM_CCC_O_BWP_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum{
  DL_BWP_CONTEXT,
  UL_BWP_CONTEXT,
  SUL_BWP_CONTEXT,
  END_BWP_CONTEXT,
}bwp_context_e;

typedef enum{
  INITIAL_IS_INITIAL_BWP,
  OTHER_IS_INITIAL_BWP,
  SUL_IS_INITIAL_BWP, // Missing this json schema value in spec
  END_IS_INITIAL_BWP,
}is_initial_bwp_e;

typedef enum{
  SUB_CARRIER_SPACING_15,
  SUB_CARRIER_SPACING_30,
  SUB_CARRIER_SPACING_60,
  SUB_CARRIER_SPACING_120,
  SUB_CARRIER_SPACING_END,
}sub_carrier_spacing_e;

typedef enum{
  CYCLIC_PREFIX_15,
  CYCLIC_PREFIX_30,
  CYCLIC_PREFIX_60,
  CYCLIC_PREFIX_120,
  CYCLIC_PREFIX_END,
}cyclic_prefix_e;

// 8.8.2.3
typedef struct{
  bwp_context_e bwp_context;

  is_initial_bwp_e is_initial_bwp;

  sub_carrier_spacing_e sub_carrier_spacing;

  // Conflict with ccc json schema
  // Follow json schema definition
  cyclic_prefix_e cyclic_prefix;

  // Integer
  uint32_t start_rb;

  // Integer
  uint32_t number_of_rbs;

} e2sm_ccc_o_bwp_t;

void free_e2sm_ccc_o_bwp(e2sm_ccc_o_bwp_t* src);

bool eq_e2sm_ccc_o_bwp(e2sm_ccc_o_bwp_t const* m0, e2sm_ccc_o_bwp_t const* m1);

e2sm_ccc_o_bwp_t cp_e2sm_ccc_o_bwp(e2sm_ccc_o_bwp_t const* src);

#endif

