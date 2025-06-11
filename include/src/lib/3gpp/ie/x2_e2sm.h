/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef X2_E2SM_H
#define X2_E2SM_H 

#include "global_enb_id.h"
#include "global_en_gnb_id.h"

typedef struct{

  union{
    //Global eNB ID
    //6.2.3.9
      global_enb_id_t global_enb_id;
      
    // Global en-gNB ID 
    // 6.2.3.4
    global_en_gnb_id_t global_en_gnb_id;
  };

} x2_e2sm_t;


#endif

