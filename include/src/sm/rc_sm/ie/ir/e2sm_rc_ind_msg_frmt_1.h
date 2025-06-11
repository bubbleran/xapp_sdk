#ifndef E2SM_RC_INDICATION_MSG_FORMAT_1_H
#define E2SM_RC_INDICATION_MSG_FORMAT_1_H

#include <stdbool.h>
#include <stdlib.h>

#include "seq_ran_param.h"

//9.2.1.4.1
typedef struct{
  //  Sequence of RAN
  //  Parameters
  //  [1 - 65535]
  size_t sz_seq_ran_param;
  seq_ran_param_t* seq_ran_param;

} e2sm_rc_ind_msg_frmt_1_t;

void free_e2sm_rc_ind_msg_frmt_1(e2sm_rc_ind_msg_frmt_1_t const* src);

bool eq_e2sm_rc_ind_msg_frmt_1( e2sm_rc_ind_msg_frmt_1_t const* m0,  e2sm_rc_ind_msg_frmt_1_t const* m1);

e2sm_rc_ind_msg_frmt_1_t cp_e2sm_rc_ind_msg_frmt_1(e2sm_rc_ind_msg_frmt_1_t const* src);

#endif
