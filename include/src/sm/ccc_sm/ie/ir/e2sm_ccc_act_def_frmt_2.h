/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef E2SM_CCC_ACTION_DEFINITION_FORMAT_2
#define E2SM_CCC_ACTION_DEFINITION_FORMAT_2

#include <stdbool.h>
#include <stdlib.h>

#include "../../../../lib/sm/ie/cell_global_id.h"
#include "../../../../util/byte_array.h"
#include "act_def_ran_conf.h"

typedef struct{
  // Cell global ID
  // Optional
  // 9.3.6
  cell_global_id_t* cell_global_id;

  // List of Cell-level RAN Configuration Structures
  // [1 - 1024]
  size_t sz_act_def_ran_conf;
  act_def_ran_conf_t* act_def_ran_conf;

} act_def_cell_report_t;

// 9.2.1.2.2
typedef struct{
  // List of Cell Configuration to be reported
  // [1-1024]
  size_t sz_act_def_cell_report;
  act_def_cell_report_t* act_def_cell_report;

} e2sm_ccc_act_def_frmt_2_t; 

void free_e2sm_ccc_act_def_frmt_2(e2sm_ccc_act_def_frmt_2_t* src);

bool eq_e2sm_ccc_act_def_frmt_2(e2sm_ccc_act_def_frmt_2_t const* m0, e2sm_ccc_act_def_frmt_2_t const* m1);

e2sm_ccc_act_def_frmt_2_t cp_e2sm_ccc_act_def_frmt_2(e2sm_ccc_act_def_frmt_2_t const* src); 

#endif

