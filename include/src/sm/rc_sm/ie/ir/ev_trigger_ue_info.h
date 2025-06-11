#ifndef EVENT_TRIGGER_UE_INFORMATION_E2SM_H
#define EVENT_TRIGGER_UE_INFORMATION_E2SM_H 

#include <stdint.h>
#include <stdlib.h>

#include "assoc_ue_info.h"

// 9.3.26
typedef struct{

  // [1-65535]
  size_t sz_assoc_ue_info;
  assoc_ue_info_t* assoc_ue_info;

} ev_trigger_ue_info_t;

#endif

