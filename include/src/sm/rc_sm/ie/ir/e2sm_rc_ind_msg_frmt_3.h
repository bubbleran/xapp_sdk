#ifndef E2SM_RC_INDICATION_MSG_FORMAT_3_H
#define E2SM_RC_INDICATION_MSG_FORMAT_3_H

#include <stdbool.h>
#include <stdlib.h>

#include "seq_cell_info.h"

//9.2.1.4.3
typedef struct{

  // Sequence of Cell Information
  // [1 - 65535]
  size_t sz_seq_cell_info;
  seq_cell_info_t* seq_cell_info;

} e2sm_rc_ind_msg_frmt_3_t;

void free_e2sm_rc_ind_msg_frmt_3(e2sm_rc_ind_msg_frmt_3_t* src);

bool eq_e2sm_rc_ind_msg_frmt_3(e2sm_rc_ind_msg_frmt_3_t const* m0, e2sm_rc_ind_msg_frmt_3_t const* m1);

e2sm_rc_ind_msg_frmt_3_t cp_e2sm_rc_ind_msg_frmt_3(e2sm_rc_ind_msg_frmt_3_t const* src);

#endif



