/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef E2SM_CCC_INDICATION_MSG_FORMAT_2_H
#define E2SM_CCC_INDICATION_MSG_FORMAT_2_H

#include <stdbool.h>

#include "../../../../lib/sm/ie/cell_global_id.h"
#include "../../../../util/byte_array.h"
#include "change_type.h"
#include "ind_msg_ran_conf.h"

typedef struct {
  // Cell global id
  // Mandatory
  // 9.3.6
  cell_global_id_t cell_global_id;

  // List of Configuration Structures Reported
  // [1 - 65535]
  size_t sz_ind_msg_ran_conf;
  ind_msg_ran_conf_t* ind_msg_ran_conf;

} ind_msg_cell_report_t;

//9.2.1.4.2
typedef struct{
  // List of Cells Reported
  // [1 - 65535]
  size_t sz_ind_msg_cell_report;
  ind_msg_cell_report_t* ind_msg_cell_report;

} e2sm_ccc_ind_msg_frmt_2_t;

void free_ind_msg_cell_report(ind_msg_cell_report_t* src);

bool eq_ind_msg_cell_report(ind_msg_cell_report_t const* m0,  ind_msg_cell_report_t const* m1);

ind_msg_cell_report_t cp_ind_msg_cell_report(ind_msg_cell_report_t const* src);

void free_e2sm_ccc_ind_msg_frmt_2(e2sm_ccc_ind_msg_frmt_2_t const* src);

bool eq_e2sm_ccc_ind_msg_frmt_2( e2sm_ccc_ind_msg_frmt_2_t const* m0,  e2sm_ccc_ind_msg_frmt_2_t const* m1);

e2sm_ccc_ind_msg_frmt_2_t cp_e2sm_ccc_ind_msg_frmt_2(e2sm_ccc_ind_msg_frmt_2_t const* src);

#endif

