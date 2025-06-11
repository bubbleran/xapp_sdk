#ifndef SEQUENCE_UE_IDENTIFIER_E2SM_RC_H
#define SEQUENCE_UE_IDENTIFIER_E2SM_RC_H

#include "seq_ran_param.h"

#include <stdbool.h>
#include <stdlib.h>
#include "../../../../lib/sm/ie/ue_id.h"

// From 9.2.1.4.2
typedef struct{

  // UE ID
  // Mandatory
  // 9.3.10
  ue_id_e2sm_t ue_id;

  // Sequence of
  // RAN Parameter
  // [1- 65535]
  size_t sz_seq_ran_param;
  seq_ran_param_t* seq_ran_param;

} seq_ue_id_t;

void free_seq_ue_id(seq_ue_id_t* src);

bool eq_seq_ue_id(seq_ue_id_t const* m0, seq_ue_id_t const* m1);

seq_ue_id_t cp_seq_ue_id( seq_ue_id_t const* src);

#endif

