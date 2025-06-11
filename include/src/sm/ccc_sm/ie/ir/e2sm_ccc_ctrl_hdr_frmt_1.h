/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef E2SM_CCC_CTRL_HDR_FRMT_1_E2SM_H
#define E2SM_CCC_CTRL_HDR_FRMT_1_E2SM_H

#include <stdint.h>
#include <stdbool.h>

// 9.2.1.6.1
typedef struct{
  //  RIC Style Type
  //  Mandatory
  //  9.3.3
  //  Defined in common 6.2.2.2.
  uint32_t ric_style_type;
} e2sm_ccc_ctrl_hdr_frmt_1_t;

void free_e2sm_ccc_ctrl_hdr_frmt_1(e2sm_ccc_ctrl_hdr_frmt_1_t* src);

bool eq_e2sm_ccc_ctrl_hdr_frmt_1(e2sm_ccc_ctrl_hdr_frmt_1_t const* m0, e2sm_ccc_ctrl_hdr_frmt_1_t const* m1);

e2sm_ccc_ctrl_hdr_frmt_1_t cp_e2sm_ccc_ctrl_hdr_frmt_1( e2sm_ccc_ctrl_hdr_frmt_1_t const* src);

#endif

