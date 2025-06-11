#ifndef E2SM_RC_EV_TRG_FRMT_3
#define E2SM_RC_EV_TRG_FRMT_3

#include "e2_node_info_chng.h"

#include <stdbool.h>
#include <stdlib.h>

// 9.2.1.1.3

typedef struct{

  // Sequence of E2 Node
  // Information Change
  // [1 - 65535]
  size_t sz_e2_node_info_chng; 
  e2_node_info_chng_t* e2_node_info_chng; 

} e2sm_rc_ev_trg_frmt_3_t;

void free_e2sm_rc_ev_trg_frmt_3(e2sm_rc_ev_trg_frmt_3_t* src);

bool eq_e2sm_rc_ev_trg_frmt_3(e2sm_rc_ev_trg_frmt_3_t const* m0, e2sm_rc_ev_trg_frmt_3_t const* m1);

e2sm_rc_ev_trg_frmt_3_t cp_e2sm_rc_ev_trg_frmt_3(e2sm_rc_ev_trg_frmt_3_t const* src);

#endif

