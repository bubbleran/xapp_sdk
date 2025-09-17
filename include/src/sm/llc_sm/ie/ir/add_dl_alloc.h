#ifndef ADD_DL_ALLOC_E2SM_LLC_MIR_H
#define ADD_DL_ALLOC_E2SM_LLC_MIR_H 

#include "../../../../lib/sm/ie/ue_id.h"
#include <stdbool.h>

// From 8.3.27
// List of DL Grants
typedef struct{

  //UE ID 
  //Optional 
  //8.3.8
  ue_id_e2sm_t* ue_id;

  // Logical Channel ID
  // Optional
  // [1,32]
  uint32_t* log_channel_id; 

  // Number of Bytes Scheduled
  // Mandatory
  uint32_t num_bytes_sched;

  // Start Symbol
  // Optional
  uint32_t* start_symb;

  // Number of Symbols
  // Optional
  uint32_t* num_symb;

  // Start RB
  // Optional
  uint32_t* start_rb;

  // Number of RBs
  // Optional
  uint32_t* num_rb;

} add_dl_alloc_t;

add_dl_alloc_t cp_add_dl_alloc( add_dl_alloc_t const* src);

void free_add_dl_alloc(add_dl_alloc_t* src);

bool eq_add_dl_alloc(add_dl_alloc_t const* m0, add_dl_alloc_t const* m1);


#endif
