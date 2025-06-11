#ifndef SEQ_INS_IND_ACT_DEF_E2SM_RC_H
#define SEQ_INS_IND_ACT_DEF_E2SM_RC_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#include "ran_param_ins_ind.h"

// From 9.2.1.2.4
// From 9.2.1.4.6
typedef struct{
  // Insert Indication ID
  // Mandatory
  // 9.3.16
  // [1 - 65535]
  uint16_t ind_id;

  // List of RAN parameters for
  // Insert Indication
  // [1-65535] 9.2.1.2.4
  // [0-65535] 9.2.1.4.6
  size_t sz_ran_param_ins_ind;
  ran_param_ins_ind_t* ran_param_ins_ind;

} seq_ins_ind_act_def_t;

void free_seq_ins_ind_act_def(seq_ins_ind_act_def_t* src);

bool eq_seq_ins_ind_act_def( seq_ins_ind_act_def_t const* m0, seq_ins_ind_act_def_t const* m1);

seq_ins_ind_act_def_t cp_seq_ins_ind_act_def(seq_ins_ind_act_def_t const* src);

#endif

