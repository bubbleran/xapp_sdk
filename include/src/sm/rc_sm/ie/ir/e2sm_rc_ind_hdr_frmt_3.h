#ifndef E2SM_RC_INDICATION_HEADER_FORMAT_3_H
#define E2SM_RC_INDICATION_HEADER_FORMAT_3_H

#include <stdint.h>
#include "../../../../lib/sm/ie/ue_id.h"

typedef struct{

  // Event Trigger Condition ID
  // Optional
  // 9.3.21
  // [1 - 65535]
  uint16_t* ev_trigger_cond; 

  // UE ID
  // Optional 
  // 9.3.10
  ue_id_e2sm_t* ue_id;

} e2sm_rc_ind_hdr_frmt_3_t; 

void free_e2sm_rc_ind_hdr_frmt_3(e2sm_rc_ind_hdr_frmt_3_t* src);

bool eq_e2sm_rc_ind_hdr_frmt_3(e2sm_rc_ind_hdr_frmt_3_t const* m0, e2sm_rc_ind_hdr_frmt_3_t const* m1);

e2sm_rc_ind_hdr_frmt_3_t cp_e2sm_rc_ind_hdr_frmt_3(e2sm_rc_ind_hdr_frmt_3_t const* src);

#endif


