#ifndef SEQ_CELL_INFO_2_E2SM_RC_H
#define SEQ_CELL_INFO_2_E2SM_RC_H

#include "../../../../lib/sm/ie/cell_global_id.h"
#include "../../../../util/byte_array.h"
#include "nghbr_rel_info.h"

#include <stdbool.h>

// From 9.2.1.4.4
typedef struct{

  // Cell Global ID
  // Mandatory
  // 9.3.36
  // 6.2.2.5. 
  cell_global_id_t cell_global_id;

  // Cell Context Information
  // Optional
  // OCTET STRING
  byte_array_t* cell_ctx_info;

  // Neighbour Relation Table
  // Optional
  // 9.3.38
  nghbr_rel_info_t* neighbour_rela_tbl;

} seq_cell_info_2_t;

void free_seq_cell_info_2(seq_cell_info_2_t* src);

bool eq_seq_cell_info_2(seq_cell_info_2_t const* m0, seq_cell_info_2_t const* m1);

seq_cell_info_2_t cp_seq_cell_info_2(seq_cell_info_2_t const* src); 

#endif

