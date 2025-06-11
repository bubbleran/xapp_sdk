#ifndef SEQUENCE_CONTROL_ACTION_E2SM_RC_H
#define SEQUENCE_CONTROL_ACTION_E2SM_RC_H

#include "e2sm_rc_ctrl_msg_frmt_1.h"

#include <stdbool.h>

// From 9.2.1.7.2
typedef struct{
  //Control Action ID
  //Mandatory
  //9.3.6
  // [1 - 65535]
  uint16_t ctrl_act_id;

  // Control Action Parameters
  // BUG, BUG, BUG in the standard 
  // Optional in english. Mandatory in ASN. 
  // 9.2.1.7.1 E2SM-RC Control Message Format 1
  e2sm_rc_ctrl_msg_frmt_1_t* ctrl_msg_frmt_1;

} seq_ctrl_act_t;

void free_seq_ctrl_act(seq_ctrl_act_t* src);

bool eq_seq_ctrl_act( seq_ctrl_act_t const* m0,  seq_ctrl_act_t const* m1);

seq_ctrl_act_t cp_seq_ctrl_act(seq_ctrl_act_t const* src);

#endif

