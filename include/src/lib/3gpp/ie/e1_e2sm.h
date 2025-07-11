/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef E1_E2SM_H
#define E1_E2SM_H 

#include "global_gnb_id.h"

typedef struct{

  // Global gNB ID
  // Mandatory
  // 6.2.3.2
  global_gnb_id_t global_gnb_id;

  // gNB-CU-UP ID
  // Mandatory
  // 6.2.3.5
 uint64_t gnb_cu_up_id;   //INTEGER (0 .. 2^36-1)

} e1_e2sm_t;

#endif

