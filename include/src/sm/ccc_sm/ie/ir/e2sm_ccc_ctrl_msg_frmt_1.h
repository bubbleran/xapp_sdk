/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef E2SM_CCC_CTRL_MSG_FRMT_1_H
#define E2SM_CCC_CTRL_MSG_FRMT_1_H

#include <stdlib.h>
#include <stdbool.h>
#include "../../../../util/byte_array.h"
#include "ctrl_msg_ran_conf.h"

// 9.2.1.7.1
typedef struct{
  // List of Configuration Structures
  // [1-65535]
  size_t sz_ctrl_msg_ran_conf;
  ctrl_msg_ran_conf_t* ctrl_msg_ran_conf;

} e2sm_ccc_ctrl_msg_frmt_1_t;

void free_e2sm_ccc_ctrl_msg_frmt_1( e2sm_ccc_ctrl_msg_frmt_1_t* src);

bool eq_e2sm_ccc_ctrl_msg_frmt_1(e2sm_ccc_ctrl_msg_frmt_1_t const* m0, e2sm_ccc_ctrl_msg_frmt_1_t const* m1);

e2sm_ccc_ctrl_msg_frmt_1_t cp_e2sm_ccc_ctrl_msg_frmt_1(e2sm_ccc_ctrl_msg_frmt_1_t const* src);

#endif

