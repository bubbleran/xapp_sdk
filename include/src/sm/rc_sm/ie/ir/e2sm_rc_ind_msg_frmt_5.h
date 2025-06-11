#ifndef E2SM_RC_INDICATION_MSG_FORMAT_5_H
#define E2SM_RC_INDICATION_MSG_FORMAT_5_H

#include <stdbool.h>
#include <stdlib.h>

#include "seq_ran_param.h"

//9.2.1.4.5
typedef struct{

  // List of RAN parameters requested
  // [0-65535]
  size_t sz_seq_ran_param;
  seq_ran_param_t* seq_ran_param;

} e2sm_rc_ind_msg_frmt_5_t;


void free_e2sm_rc_ind_msg_frmt_5(e2sm_rc_ind_msg_frmt_5_t* src);

bool eq_e2sm_rc_ind_msg_frmt_5(e2sm_rc_ind_msg_frmt_5_t const* m0, e2sm_rc_ind_msg_frmt_5_t const* m1);

e2sm_rc_ind_msg_frmt_5_t cp_e2sm_rc_ind_msg_frmt_5(e2sm_rc_ind_msg_frmt_5_t const* src);

#endif

