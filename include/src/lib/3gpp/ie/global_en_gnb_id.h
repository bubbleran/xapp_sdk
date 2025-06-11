/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef GLOBAL_EN_GNB_ID_E2SM_H
#define GLOBAL_EN_GNB_ID_E2SM_H

#include "plmn_identity.h"

typedef struct{

  // PLMN Identity
  // Mandatory
  // 6.2.3.1
  e2sm_plmn_t plmn;

  // en-gNB ID
  // Mandatory
  // BIT STRING (SIZE(22..32))
  uint32_t en_gnb_id; 

} global_en_gnb_id_t ;

#endif

