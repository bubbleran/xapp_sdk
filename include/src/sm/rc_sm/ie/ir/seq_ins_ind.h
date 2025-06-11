#ifndef SEQ_INS_IND_E2SM_RC_H
#define SEQ_INS_IND_E2SM_RC_H

#include "seq_ran_param_3.h"

// From 9.2.2.4
typedef struct{
  // Insert Indication ID
  // Mandatory
  // 9.3.16
  // [1-65535]
  uint16_t id;

  // Insert Indication Name
  // Mandatory
  // 9.3.17
  // [1-150]
  byte_array_t name;

  // Sequence of Insert Indications
  // [0-65535]
  size_t sz_seq_ins_ind;
  seq_ran_param_3_t* seq_ins_ind;

} seq_ins_ind_t;

void free_seq_ins_ind(seq_ins_ind_t* src);

bool eq_seq_ins_ind(seq_ins_ind_t const* m0, seq_ins_ind_t const* m1);

seq_ins_ind_t cp_seq_ins_ind(seq_ins_ind_t const* src);

#endif
