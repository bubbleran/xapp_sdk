#ifndef RAN_CONTROL_EVENT_TRIGGER_FORMAT_1_SM_H
#define RAN_CONTROL_EVENT_TRIGGER_FORMAT_1_SM_H 

#include <stdlib.h>

#include "msg_ev_trg.h"
#include "ev_trigger_ue_info.h"

// 9.2.1.1.1
typedef struct{
  // [1 - 65535]
  size_t sz_msg_ev_trg;
  msg_ev_trg_t* msg_ev_trg;

  // Global Associated UE Info
  // Optional
  // 9.3.26
  ev_trigger_ue_info_t* global_assoc_ue_info;

} e2sm_rc_ev_trg_frmt_1_t; 

void free_e2sm_rc_ev_trg_frmt_1(e2sm_rc_ev_trg_frmt_1_t* src);

bool eq_e2sm_rc_ev_trg_frmt_1(e2sm_rc_ev_trg_frmt_1_t const* m0, e2sm_rc_ev_trg_frmt_1_t const* m1);

e2sm_rc_ev_trg_frmt_1_t cp_e2sm_rc_ev_trg_frmt_1(  e2sm_rc_ev_trg_frmt_1_t const* src);

#endif

