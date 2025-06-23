#ifndef W1_E2SM_H
#define W1_E2SM_H

#include "global_ng_enb_id.h"

typedef struct{

  // Global ng-eNB ID
  // Mandatory
  // 6.2.3.8
  global_ng_enb_id_t global_ng_enb_id;

  // ng-eNB-DU ID
  // Mandatory
  // 6.2.3.10
  uint64_t ng_enb_du_id; // INTEGER (0 .. 2^36-1)

} w1_e2sm_t;


#endif
