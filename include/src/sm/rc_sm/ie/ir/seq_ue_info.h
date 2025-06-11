#ifndef SEQ_UE_INFO_E2SM_RC_H
#define SEQ_UE_INFO_E2SM_RC_H

#include "../../../../lib/sm/ie/cell_global_id.h"
#include "../../../../lib/sm/ie/ue_id.h"
#include "../../../../util/byte_array.h"

// From 9.2.1.4.4
typedef struct{

  // UE ID
  // Mandatory
  // 9.3.10
  ue_id_e2sm_t ue_id; 

  // UE Context Information
  // Optiona;
  // OCTET STRING
  byte_array_t* ue_ctx_info; 

  // Cell Global ID
  // Mandatory
  // 9.3.36
  cell_global_id_t cell_global_id;

} seq_ue_info_t;

void free_seq_ue_info( seq_ue_info_t* src);

bool eq_seq_ue_info(seq_ue_info_t const* m0,  seq_ue_info_t const* m1);

seq_ue_info_t cp_seq_ue_info(seq_ue_info_t const* src);

#endif

