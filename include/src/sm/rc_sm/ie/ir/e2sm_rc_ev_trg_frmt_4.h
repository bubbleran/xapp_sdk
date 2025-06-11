#ifndef E2SM_RC_EV_TRG_FRMT_4
#define E2SM_RC_EV_TRG_FRMT_4


#include <stdbool.h>
#include <stdlib.h>

#include "ue_info_chng.h"

// 9.2.1.1.4

typedef struct{
 // Sequence of UE Information Change
 // [ 1 - 65535]
 size_t sz_ue_info_chng;
 ue_info_chng_t* ue_info_chng;

} e2sm_rc_ev_trg_frmt_4_t;

void free_e2sm_rc_ev_trg_frmt_4(e2sm_rc_ev_trg_frmt_4_t* src);

bool eq_e2sm_rc_ev_trg_frmt_4( e2sm_rc_ev_trg_frmt_4_t const* m0, e2sm_rc_ev_trg_frmt_4_t const* m1);

e2sm_rc_ev_trg_frmt_4_t cp_e2sm_rc_ev_trg_frmt_4(e2sm_rc_ev_trg_frmt_4_t const* src);

#endif

