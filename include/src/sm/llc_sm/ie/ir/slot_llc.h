#ifndef SLOT_LLC_E2SM_MIR_H
#define SLOT_LLC_E2SM_MIR_H 

#include "add_dl_alloc.h"
#include "csi_rs_precoding_bnd2.h"
#include "dl_grant2.h"
#include "slot_info.h"

#include <stdbool.h>


// From 8.3.27
typedef struct{

  // Slot Information 
  // Mandatory 
  // 8.3.17
  slot_info_t slot_info;

  // List of DL Grants
  // [1, 63]
  size_t sz_dl_grant2;
  dl_grant2_t* dl_grant2;

  // List of Additional DL Allocations
  // [0, 63]
  size_t sz_add_dl_alloc;
  add_dl_alloc_t* add_dl_alloc;

  // List of CSI-RS Precoding
  // Bands Not Executed
  // [0,63]
  size_t sz_csi_rs_precoding_bnd2;
  csi_rs_precoding_bnd2_t* csi_rs_precoding_bnd2;

} slot_llc_t;

slot_llc_t cp_slot_llc(slot_llc_t const* src); 

void free_slot_llc(slot_llc_t* src);

bool eq_slot_llc(slot_llc_t const* m0, slot_llc_t const* m1);

#endif
