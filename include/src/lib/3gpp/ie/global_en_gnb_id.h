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

