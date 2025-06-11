#ifndef E2SM_RC_INDICATION_MSG_FORMAT_4_H
#define E2SM_RC_INDICATION_MSG_FORMAT_4_H

#include <stdlib.h>

#include "seq_ue_info.h"
#include "seq_cell_info_2.h"

//9.2.1.4.4
typedef struct{

  //Sequence of UE Information
  // [0-65535]
  size_t sz_seq_ue_info;
  seq_ue_info_t* seq_ue_info;

  // Sequence of Cell Information
  // [0-65535]
  size_t sz_seq_cell_info_2;
  seq_cell_info_2_t* seq_cell_info_2; 

} e2sm_rc_ind_msg_frmt_4_t;

void free_e2sm_rc_ind_msg_frmt_4(e2sm_rc_ind_msg_frmt_4_t* src);

bool eq_e2sm_rc_ind_msg_frmt_4( e2sm_rc_ind_msg_frmt_4_t const* m0,  e2sm_rc_ind_msg_frmt_4_t const* m1);

e2sm_rc_ind_msg_frmt_4_t cp_e2sm_rc_ind_msg_frmt_4(e2sm_rc_ind_msg_frmt_4_t const* src);

#endif

