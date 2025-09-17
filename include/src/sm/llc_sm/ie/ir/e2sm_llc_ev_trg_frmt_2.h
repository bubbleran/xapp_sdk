#ifndef E2SM_LLC_EVENT_TRIGGER_FORMAT_2_MIR_H
#define E2SM_LLC_EVENT_TRIGGER_FORMAT_2_MIR_H 

#include "assoc_ue_info_llc.h"
#include "ev_trg_ue_info.h"

// 8.2.1.1.2
typedef struct{
  // Reporting Period 
  // Mandatory
  // [1, 65535]
  uint32_t period_ms;

  // 8.3.12
  // Associated UE Info
  // Optional
   ev_trg_ue_info_t* assoc_ue_info;

} e2sm_llc_ev_trg_frmt_2_t;

void free_e2sm_llc_ev_trg_frmt_2(e2sm_llc_ev_trg_frmt_2_t const* src); 

bool eq_e2sm_llc_ev_trg_frmt_2(e2sm_llc_ev_trg_frmt_2_t const* m0, e2sm_llc_ev_trg_frmt_2_t const* m1); 

e2sm_llc_ev_trg_frmt_2_t cp_e2sm_llc_ev_trg_frmt_2(e2sm_llc_ev_trg_frmt_2_t const* src);

#endif
