/*
  Copyright (C) 2021-2025 BubbleRAN SAS

  External application
  Last Changed: 2025-05-02
  Project: MX-XAPP
  Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/



#ifndef E2SM_CCC_PLMN_IN_H
#define E2SM_CCC_PLMN_IN_H

#include <stdint.h>
#include <stdbool.h>
#include "../../../../lib/3gpp/ie/plmn_identity.h"
#include "../../../../lib/3gpp/ie/s_nssai.h"

// 9.3.14
typedef struct{
  // Mandatory
  // 9.3.12
  // E2SM 6.2.3.1
  e2sm_plmn_t plmn_id;

  // Optional
  // 9.3.13
  // E2SM 6.2.3.12
  s_nssai_e2sm_t* s_nssai;
} e2sm_ccc_plmn_info_t;

void free_e2sm_ccc_plmn_info(e2sm_ccc_plmn_info_t* src);

bool eq_e2sm_ccc_plmn_info(e2sm_ccc_plmn_info_t const* m0, e2sm_ccc_plmn_info_t const* m1);

e2sm_ccc_plmn_info_t cp_e2sm_ccc_plmn_info(e2sm_ccc_plmn_info_t const* src);

#endif

