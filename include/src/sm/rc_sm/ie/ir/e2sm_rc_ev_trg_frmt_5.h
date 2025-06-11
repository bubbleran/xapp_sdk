#ifndef E2SM_RC_EV_TRG_FRMT_5
#define E2SM_RC_EV_TRG_FRMT_5

#include "ev_trigger_ue_info.h"
#include "ev_trigger_cell_info.h"

#include <stdbool.h>

typedef enum{

  TRUE_ON_DEMAND_FRMT_5,

  END_ON_DEMAND_FRMT_5 

} on_demand_frmt_5_e;

// 9.2.1.1.5

typedef struct{

  // On Demand
  // Mandatory
  on_demand_frmt_5_e on_demand;

  // Associated UE Info
  // Optional
  // 9.3.26
  ev_trigger_ue_info_t* assoc_ue_info;

  // Associated Cell Info
  // Optional
  // 9.3.27
  ev_trigger_cell_info_t* assoc_cell_info;


} e2sm_rc_ev_trg_frmt_5_t;

void free_e2sm_rc_ev_trg_frmt_5(e2sm_rc_ev_trg_frmt_5_t* src);

bool eq_e2sm_rc_ev_trg_frmt_5(e2sm_rc_ev_trg_frmt_5_t const* m0, e2sm_rc_ev_trg_frmt_5_t const* m1);

e2sm_rc_ev_trg_frmt_5_t cp_e2sm_rc_ev_trg_frmt_5(e2sm_rc_ev_trg_frmt_5_t const* src);

#endif

