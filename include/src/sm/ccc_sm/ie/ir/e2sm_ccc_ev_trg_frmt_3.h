/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef E2SM_CCC_EV_TRG_FRMT_3
#define E2SM_CCC_EV_TRG_FRMT_3

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

// 9.2.1.1.3
typedef struct{
  // Mandatory
  uint32_t period; // [1, 4294967295] reporting period in milliseconds
} e2sm_ccc_ev_trg_frmt_3_t;

void free_e2sm_ccc_ev_trg_frmt_3(e2sm_ccc_ev_trg_frmt_3_t* src);

bool eq_e2sm_ccc_ev_trg_frmt_3(e2sm_ccc_ev_trg_frmt_3_t const* m0, e2sm_ccc_ev_trg_frmt_3_t const* m1);

e2sm_ccc_ev_trg_frmt_3_t cp_e2sm_ccc_ev_trg_frmt_3(e2sm_ccc_ev_trg_frmt_3_t const* src);

#endif

