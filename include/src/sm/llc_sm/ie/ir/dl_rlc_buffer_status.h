#ifndef DL_RLC_BUFFER_STATUS_E2SM_LLC_MIR_H
#define DL_RLC_BUFFER_STATUS_E2SM_LLC_MIR_H 

#include "dl_rlc_ue_id.h"
#include <stdbool.h>

// 8.3.21
typedef struct{
  // [1,65535]
  size_t sz_ue; 
  dl_rlc_ue_id_t* ue;
} dl_rlc_buffer_status_t ;

dl_rlc_buffer_status_t cp_dl_rlc_buffer_status(dl_rlc_buffer_status_t const* src);

bool eq_dl_rlc_buffer_status(dl_rlc_buffer_status_t const* m0, dl_rlc_buffer_status_t const* m1);

void free_dl_rlc_buffer_status(dl_rlc_buffer_status_t const* src);  

#endif
