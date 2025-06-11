#ifndef SEQ_INS_IND_ACT_2_E2SM_RC_H
#define SEQ_INS_IND_ACT_2_E2SM_RC_H

#include <stdlib.h>
#include <stdint.h>

#include "ran_param_req.h"

//9.2.1.4.6
typedef struct{

  //  Insert Indication ID
  //  Mandatory
  //  9.3.16
  //  1.. 65535
  uint16_t ins_ind_id;

  // List of RAN parameters requested
  // [0-65535]
  size_t sz_ran_param_req;
  ran_param_req_t* ran_param_req;

} seq_ins_ind_act_2_t;

void free_seq_ins_ind_act_2( seq_ins_ind_act_2_t* src);

bool eq_seq_ins_ind_act_2(seq_ins_ind_act_2_t const* m0, seq_ins_ind_act_2_t const* m1);

seq_ins_ind_act_2_t cp_seq_ins_ind_act_2(seq_ins_ind_act_2_t const* src);

#endif

