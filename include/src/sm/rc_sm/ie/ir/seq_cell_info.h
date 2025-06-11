#ifndef SEQUENCE_CELLULAR_INFORMATION_E2SM_RC_H
#define SEQUENCE_CELLULAR_INFORMATION_E2SM_RC_H

#include "../../../../lib/sm/ie/cell_global_id.h"
#include "../../../../util/byte_array.h"
#include "nr_nghbr_cell.h"

// From 9.2.1.4.3
typedef struct{

  // Cell Global ID
  // Mandatory
  // 9.3.36
  // 6.2.2.5
  cell_global_id_t cell_global_id;

  // Cell Context Information
  // Optional
  // OCTET STRING
  byte_array_t* cell_ctx_info;

  // Cell Deleted
  // Optional
  // BOOLEAN
  bool* cell_del; 

  // Neighbour Relation Table
  // Optional
  // 9.3.38
  nr_nghbr_cell_t* neighbour_rela_tbl;

} seq_cell_info_t;

void free_seq_cell_info( seq_cell_info_t* src);

bool eq_seq_cell_info( seq_cell_info_t const* m0,  seq_cell_info_t const* m1);

seq_cell_info_t cp_seq_cell_info(seq_cell_info_t const* src);

#endif


