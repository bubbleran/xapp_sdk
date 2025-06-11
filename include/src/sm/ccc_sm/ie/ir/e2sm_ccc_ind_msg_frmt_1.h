/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef E2SM_CCC_INDICATION_MSG_FORMAT_1_H
#define E2SM_CCC_INDICATION_MSG_FORMAT_1_H

#include <stdbool.h>
#include <stdlib.h>

#include "../../../../util/byte_array.h"
#include "change_type.h"
#include "ind_msg_ran_conf.h"

//9.2.1.4.1
typedef struct{
  //  List of Configuration Structures Reported
  //  [1 - 65535]
  size_t sz_ind_msg_node_conf;
  ind_msg_ran_conf_t* ind_msg_ran_conf;

} e2sm_ccc_ind_msg_frmt_1_t;

void free_e2sm_ccc_ind_msg_frmt_1(e2sm_ccc_ind_msg_frmt_1_t const* src);

bool eq_e2sm_ccc_ind_msg_frmt_1( e2sm_ccc_ind_msg_frmt_1_t const* m0,  e2sm_ccc_ind_msg_frmt_1_t const* m1);

e2sm_ccc_ind_msg_frmt_1_t cp_e2sm_ccc_ind_msg_frmt_1(e2sm_ccc_ind_msg_frmt_1_t const* src);

#endif
