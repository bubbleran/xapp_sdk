#ifndef F1_E2SM_H
#define F1_E2SM_H

#include "global_gnb_id.h"

typedef struct{

  // Global gNB ID
  // Mandatory
  // 6.2.3.2
  global_gnb_id_t global_gnb_id;

  // gNB-DU ID
  // Mandatory
  // 6.2.3.6
  uint64_t gnb_du_id; // INTEGER (0 .. 2^36-1)


} f1_e2sm_t;

#endif

