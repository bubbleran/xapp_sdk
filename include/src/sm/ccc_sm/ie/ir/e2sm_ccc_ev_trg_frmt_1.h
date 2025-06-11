/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef CCC_EVENT_TRIGGER_FORMAT_1_SM_H
#define CCC_EVENT_TRIGGER_FORMAT_1_SM_H

#include <stdbool.h>
#include <stdlib.h>

#include "attribute.h"
#include "../../../../util/byte_array.h"
#include "ev_trg_ran_conf.h"

// 9.2.1.1.1
typedef struct{
  // List of Node-level Configuration Structures
  // [1 - 256]
  size_t sz_ev_trg_ran_conf;
  ev_trg_ran_conf_t* ev_trg_ran_conf;
} e2sm_ccc_ev_trg_frmt_1_t;

void free_e2sm_ccc_ev_trg_frmt_1(e2sm_ccc_ev_trg_frmt_1_t* src);

bool eq_e2sm_ccc_ev_trg_frmt_1(e2sm_ccc_ev_trg_frmt_1_t const* m0, e2sm_ccc_ev_trg_frmt_1_t const* m1);

e2sm_ccc_ev_trg_frmt_1_t cp_e2sm_ccc_ev_trg_frmt_1(  e2sm_ccc_ev_trg_frmt_1_t const* src);

#endif

