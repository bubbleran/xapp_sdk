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

