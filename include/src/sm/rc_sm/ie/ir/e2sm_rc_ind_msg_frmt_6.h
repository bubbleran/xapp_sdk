#ifndef E2SM_RC_INDICATION_MSG_FORMAT_6_H
#define E2SM_RC_INDICATION_MSG_FORMAT_6_H

#include <stdbool.h>
#include <stdlib.h>

#include "seq_ins_style_2.h"

//9.2.1.4.6
typedef struct{

  // Sequence of Insert Styles for Multiple Actions
  // [1-63]
  size_t sz_seq_ins_style_ind_msg;
  seq_ins_style_2_t* seq_ins_style;

} e2sm_rc_ind_msg_frmt_6_t;

void free_e2sm_rc_ind_msg_frmt_6(e2sm_rc_ind_msg_frmt_6_t* src);

bool eq_e2sm_rc_ind_msg_frmt_6( e2sm_rc_ind_msg_frmt_6_t const* m0, e2sm_rc_ind_msg_frmt_6_t const* m1);

e2sm_rc_ind_msg_frmt_6_t cp_e2sm_rc_ind_msg_frmt_6(e2sm_rc_ind_msg_frmt_6_t const* src);

#endif

