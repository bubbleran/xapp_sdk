#ifndef E2SM_RC_CTRL_HDR_FRMT_1_E2SM_RC_H
#define E2SM_RC_CTRL_HDR_FRMT_1_E2SM_RC_H

#include "../../../../lib/sm/ie/ue_id.h"

typedef enum{
  ACCEPT_RIC_CTRL_DECISION , 
  REJECT_RIC_CTRL_DECISION ,
  END_RIC_CTRL_DECISION
} ric_ctrl_decision_e;

// 9.2.1.6.1
typedef struct{
  // UE ID
  // Mandatory
  // 9.3.10
  // 6.2.2.6
  ue_id_e2sm_t ue_id;

  // RIC Style Type
  // Mandatory
  // 9.3.3
  // 6.2.2.2. 
  // INTEGER
  uint32_t ric_style_type;

  // Control Action ID
  // Mandatory
  // 9.3.6
  // [1- 65535]
  uint16_t ctrl_act_id;

  // RIC Control decision
  // Optional
  ric_ctrl_decision_e* ric_ctrl_decision;
} e2sm_rc_ctrl_hdr_frmt_1_t;

void free_e2sm_rc_ctrl_hdr_frmt_1(e2sm_rc_ctrl_hdr_frmt_1_t* src);

bool eq_e2sm_rc_ctrl_hdr_frmt_1(e2sm_rc_ctrl_hdr_frmt_1_t const* m0, e2sm_rc_ctrl_hdr_frmt_1_t const* m1);

e2sm_rc_ctrl_hdr_frmt_1_t cp_e2sm_rc_ctrl_hdr_frmt_1( e2sm_rc_ctrl_hdr_frmt_1_t const* src);

#endif

