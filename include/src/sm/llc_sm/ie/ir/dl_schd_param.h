#ifndef DL_SCHD_PARAM_E2SM_LLC_MIR_H
#define DL_SCHD_PARAM_E2SM_LLC_MIR_H 

#include "slot_llc.h"
#include <stdbool.h>

// 8.3.27
typedef struct{

  // Received Timestamp 
  // Mandatory
  // 8.3.24
  uint8_t tstamp[8];

  // Processing Time Margin 
  // Mandatory 
  // INTEGER [-32767,32767]
  int32_t proc_time_margin;

  // List of Slots
  // [1, 63]
  size_t sz_slots;
  slot_llc_t* slot;

} dl_schd_param_t ;

dl_schd_param_t cp_dl_schd_param( dl_schd_param_t const* src);

void free_dl_schd_param( dl_schd_param_t* src);

bool eq_dl_schd_param(dl_schd_param_t const* m0, dl_schd_param_t const* m1 );




#endif
