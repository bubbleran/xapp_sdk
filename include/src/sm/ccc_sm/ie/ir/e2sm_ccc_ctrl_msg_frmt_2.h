/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef E2SM_CCC_CTRL_MSG_FRMT_2_H
#define E2SM_CCC_CTRL_MSG_FRMT_2_H


#include <stdbool.h>
#include <stdlib.h>

#include "../../../../lib/sm/ie/cell_global_id.h"
#include "../../../../util/byte_array.h"
#include "ctrl_msg_ran_conf.h"

typedef struct{
  // Cell global ID
  // Mandatory
  // 9.3.6
  cell_global_id_t cell_global_id;

  // List of Configuration Structures
  // [1-65535]
  size_t sz_ctrl_msg_ran_conf;
  ctrl_msg_ran_conf_t* ctrl_msg_ran_conf;

} ctrl_msg_cell_t;

// 9.2.1.7.2
typedef struct{
  // List of Cells
  // [1-65535]
  size_t sz_ctrl_msg_cell;
  ctrl_msg_cell_t* ctrl_msg_cell;

} e2sm_ccc_ctrl_msg_frmt_2_t;

void free_e2sm_ccc_ctrl_msg_frmt_2( e2sm_ccc_ctrl_msg_frmt_2_t* src);

bool eq_e2sm_ccc_ctrl_msg_frmt_2( e2sm_ccc_ctrl_msg_frmt_2_t const* m0,  e2sm_ccc_ctrl_msg_frmt_2_t const* m1);

e2sm_ccc_ctrl_msg_frmt_2_t cp_e2sm_ccc_ctrl_msg_frmt_2(e2sm_ccc_ctrl_msg_frmt_2_t const* src);

#endif



