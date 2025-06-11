#ifndef SEQ_INS_STYLE_MULTIPLE_ACTION_E2SM_RC_H
#define SEQ_INS_STYLE_MULTIPLE_ACTION_E2SM_RC_H

#include "seq_ins_ind_act_def.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

//9.2.1.4.4
//9.2.1.4.6

typedef struct{
  // Requested Insert Style
  // Mandatory
  // 9.3.3
  // 6.2.2.2. in E2 SM common 
  // Integer
  uint32_t req_insert_style;

  // Sequence of Insert Indication
  // Action Definition
  // [1-63]
  size_t sz_seq_ins_ind_act_def;
  seq_ins_ind_act_def_t* seq_ins_ind_act_def;

} seq_ins_style_t;

void free_seq_ins_style(seq_ins_style_t* src);

bool eq_seq_ins_style(seq_ins_style_t const* m0, seq_ins_style_t const* m1);

seq_ins_style_t cp_seq_ins_style(seq_ins_style_t const* src);

#endif

