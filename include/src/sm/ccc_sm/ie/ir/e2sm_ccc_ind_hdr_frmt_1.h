/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef E2SM_CCC_INDICATION_HEADER_FORMAT_1_H
#define E2SM_CCC_INDICATION_HEADER_FORMAT_1_H

#include <stdbool.h>
#include <stdint.h>

#include "../../../../util/byte_array.h"

typedef enum {
  IND_REASON_UPON_SUB,
  IND_REASON_UPON_CHANGE,
  IND_REASON_PERIODIC,

  END_IND_REASON
} indication_reason_e;

// 9.2.1.3.1
typedef struct{
  // Event time
  // 9.3.10
  // Mandatory
  char* event_time;

  // Indication reason
  // Mandatory
  indication_reason_e ind_reason;

} e2sm_ccc_ind_hdr_frmt_1_t;


e2sm_ccc_ind_hdr_frmt_1_t cp_e2sm_ccc_ind_hdr_frmt_1(e2sm_ccc_ind_hdr_frmt_1_t const* src);

void free_e2sm_ccc_ind_hdr_frmt_1(e2sm_ccc_ind_hdr_frmt_1_t* src);

bool eq_e2sm_ccc_ind_hdr_frmt_1(e2sm_ccc_ind_hdr_frmt_1_t const* m0,e2sm_ccc_ind_hdr_frmt_1_t const* m1);

#endif
