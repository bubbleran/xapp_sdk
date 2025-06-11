#ifndef E2SM_RC_INDICATION_HEADER_FORMAT_1_H
#define E2SM_RC_INDICATION_HEADER_FORMAT_1_H

#include <stdbool.h>
#include <stdint.h>

// 9.2.1.3.1
typedef struct{
  // Event Trigger Condition ID
  // Optional
  // 9.3.21
  // [1 - 65535]
  uint16_t* ev_trigger_id;

} e2sm_rc_ind_hdr_frmt_1_t; 


e2sm_rc_ind_hdr_frmt_1_t cp_e2sm_rc_ind_hdr_frmt_1(e2sm_rc_ind_hdr_frmt_1_t const* src);

void free_e2sm_rc_ind_hdr_frmt_1(e2sm_rc_ind_hdr_frmt_1_t* src);

bool eq_e2sm_rc_ind_hdr_frmt_1(e2sm_rc_ind_hdr_frmt_1_t const* m0,e2sm_rc_ind_hdr_frmt_1_t const* m1);

#endif
