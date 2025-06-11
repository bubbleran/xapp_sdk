#ifndef E2SM_RC_CTRL_HDR_FRMT_2_E2SM_RC_H
#define E2SM_RC_CTRL_HDR_FRMT_2_E2SM_RC_H

#include "../../../../lib/sm/ie/ue_id.h"

#include <stdbool.h>

typedef enum{
  ACCEPT_RIC_CTRL_DEC_CTRL_HDR_FRMT_2, 
  REJECT_RIC_CTRL_DEC_CTRL_HDR_FRMT_2,

  END_RIC_CTRL_DEC_CTRL_HDR_FRMT_2
} ric_ctrl_dec_ctrl_hdr_frmt_2_e;

// 9.2.1.6.1
typedef struct{
 // UE ID
 // Optional
 // 9.3.10
  ue_id_e2sm_t* ue_id;

  // RIC Control decision
  // Optional
  ric_ctrl_dec_ctrl_hdr_frmt_2_e* ric_ctrl_dec;

} e2sm_rc_ctrl_hdr_frmt_2_t;

void free_e2sm_rc_ctrl_hdr_frmt_2( e2sm_rc_ctrl_hdr_frmt_2_t* src);

bool eq_e2sm_rc_ctrl_hdr_frmt_2( e2sm_rc_ctrl_hdr_frmt_2_t const* m0, e2sm_rc_ctrl_hdr_frmt_2_t const* m1);
     
e2sm_rc_ctrl_hdr_frmt_2_t cp_e2sm_rc_ctrl_hdr_frmt_2( e2sm_rc_ctrl_hdr_frmt_2_t const* src);

#endif
