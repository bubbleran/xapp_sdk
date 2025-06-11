/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef E2SM_CCC_5QI_LST_H
#define E2SM_CCC_5QI_LST_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../../../lib/3gpp/ie/plmn_identity.h"
#include "../../../../lib/3gpp/ie/s_nssai.h"

// 9.3.19
typedef struct{
  // [1..128]
  size_t sz_lst_5qi;
  // Mandatory
  // Intger
  uint32_t* lst_5qi;

} e2sm_ccc_5qi_lst_t;

void free_e2sm_ccc_5qi_lst(e2sm_ccc_5qi_lst_t* src);

bool eq_e2sm_ccc_5qi_lst(e2sm_ccc_5qi_lst_t const* m0, e2sm_ccc_5qi_lst_t const* m1);

e2sm_ccc_5qi_lst_t cp_e2sm_ccc_5qi_lst(e2sm_ccc_5qi_lst_t const* src);

#endif

