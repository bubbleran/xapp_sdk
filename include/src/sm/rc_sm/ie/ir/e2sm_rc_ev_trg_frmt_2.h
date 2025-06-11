#ifndef E2SM_RC_EV_TRG_FRMT_2
#define E2SM_RC_EV_TRG_FRMT_2

#include "ev_trigger_ue_info.h"
#include "ran_param_cond_crit_def.h"

#include <stdbool.h>
#include <stdint.h>

// 9.2.1.1.2

typedef struct{

  //  Call Process Type ID
  //  Mandatory
  //  9.3.15
  //  INTEGER (1.. 65535, …)
  uint16_t call_proc_type_id;

  // Call Breakpoint ID
  // Mandatory
  // 9.3.49
  // INTEGER (1.. 65535, …)
  uint16_t call_break_id; 

  // Associated E2 Node Info
  // Optional
  // 9.3.29
  ran_param_cond_crit_def_t* assoc_e2_node_info;

  // Associated UE Info
  // Optional
  // 9.3.26
  ev_trigger_ue_info_t* assoc_ue_info;

} e2sm_rc_ev_trg_frmt_2_t; 

void free_e2sm_rc_ev_trg_frmt_2(e2sm_rc_ev_trg_frmt_2_t const* src);

bool eq_e2sm_rc_ev_trg_frmt_2(e2sm_rc_ev_trg_frmt_2_t const* m0, e2sm_rc_ev_trg_frmt_2_t const* m1);

e2sm_rc_ev_trg_frmt_2_t cp_e2sm_rc_ev_trg_frmt_2(e2sm_rc_ev_trg_frmt_2_t const* src);

#endif

