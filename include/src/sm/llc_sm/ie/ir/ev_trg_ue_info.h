#ifndef EVENT_TRIGGER_UE_INFO_MIR_H
#define EVENT_TRIGGER_UE_INFO_MIR_H 

#include "assoc_ue_info_llc.h"

#include <stdbool.h>

// 8.3.12
typedef struct{
  // [1,65535]
  size_t sz_assoc_ue_info;
  assoc_ue_info_llc_t* assoc_ue_info;
} ev_trg_ue_info_t;

ev_trg_ue_info_t cp_ev_trg_ue_info(ev_trg_ue_info_t const* src); 

void free_ev_trg_ue_info(ev_trg_ue_info_t* src);

bool eq_ev_trg_ue_info(ev_trg_ue_info_t const* m0, ev_trg_ue_info_t const* m1);

#endif
