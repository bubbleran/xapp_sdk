/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
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

