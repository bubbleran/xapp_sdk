#ifndef E2SM_LLC_EV_TRG_FRMT_1_MIR_H
#define E2SM_LLC_EV_TRG_FRMT_1_MIR_H 

#include "list_lli_event_trigger.h"

#include <stdbool.h>

// 8.2.1.1.1
typedef struct{
  // List of LLI for Event Trigger
  // [1,63]
  size_t sz_lst_lli_ev_trg; 
  lst_lli_ev_trg_t* lst_lli_ev_trg;

  // 8.3.12
  // Global Associated UE Info
  // Optional 
  ev_trg_ue_info_t* ev_trg_ue_info;
} e2sm_llc_ev_trg_frmt_1_t;

e2sm_llc_ev_trg_frmt_1_t cp_e2sm_llc_ev_trg_frmt_1(e2sm_llc_ev_trg_frmt_1_t const* src);

bool eq_e2sm_llc_ev_trg_frmt_1(e2sm_llc_ev_trg_frmt_1_t const* m0, e2sm_llc_ev_trg_frmt_1_t const* m1);


#endif
