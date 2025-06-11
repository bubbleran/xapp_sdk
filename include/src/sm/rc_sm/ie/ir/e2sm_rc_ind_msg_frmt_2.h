#ifndef E2SM_RC_INDICATION_MSG_FORMAT_2_H
#define E2SM_RC_INDICATION_MSG_FORMAT_2_H

#include "seq_ue_id.h"

#include <stdbool.h>
#include <stdlib.h>

#include "seq_ue_id.h"

//9.2.1.4.2
typedef struct{
  //Sequence of UE Identifier
  //[1-65535]
  size_t sz_seq_ue_id;
  seq_ue_id_t* seq_ue_id;

} e2sm_rc_ind_msg_frmt_2_t;

void free_e2sm_rc_ind_msg_frmt_2(e2sm_rc_ind_msg_frmt_2_t const* src);

bool eq_e2sm_rc_ind_msg_frmt_2( e2sm_rc_ind_msg_frmt_2_t const* m0,  e2sm_rc_ind_msg_frmt_2_t const* m1);

e2sm_rc_ind_msg_frmt_2_t cp_e2sm_rc_ind_msg_frmt_2(e2sm_rc_ind_msg_frmt_2_t const* src);

#endif

