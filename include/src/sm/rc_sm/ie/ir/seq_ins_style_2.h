#ifndef SEQ_INS_STYLE_IND_MSG_E2SM_RC_H
#define SEQ_INS_STYLE_IND_MSG_E2SM_RC_H

#include <stdlib.h>
#include <stdint.h>

#include "seq_ins_ind_act_2.h"

//9.2.1.4.6
typedef struct{

  // Indicated Insert Style
  // Mandatory
  // 9.3.3
  // 6.2.2.2.
  // INTEGER
  uint32_t ind_ins_style;

  // Sequence of Insert Indication Actions
  // [1-63]
  size_t sz_seq_ins_ind_act_2;
  seq_ins_ind_act_2_t* seq_ins_ind_act;

}seq_ins_style_2_t;

void free_seq_ins_style_2(seq_ins_style_2_t* src);

bool eq_seq_ins_style_2(seq_ins_style_2_t const* m0, seq_ins_style_2_t const* m1);

seq_ins_style_2_t cp_seq_ins_style_2(seq_ins_style_2_t const* src); 

#endif

