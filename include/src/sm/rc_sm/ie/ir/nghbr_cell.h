#ifndef NGHBR_CELL_RC_SM_MIR_H
#define NGHBR_CELL_RC_SM_MIR_H 

#include <stdbool.h>

#include "../../../../lib/sm/ie/rat_type.h"
#include "nr_nghbr_cell.h"
#include "eutra_nghbr_cell.h"

// Neighbour Cell List
// 9.3.38
typedef struct{
  // CHOICE RAT type
  // Mandatory
  rat_type_e type;

  union {
    nr_nghbr_cell_t nr;
    eutra_nghbr_cell_t eutra;
  };

} nghbr_cell_t;

void free_nghbr_cell(nghbr_cell_t* src);

bool eq_nghbr_cell(nghbr_cell_t const* m0, nghbr_cell_t const* m1);

#endif
