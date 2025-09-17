#ifndef LOWER_MEASUREMENT_E2SM_LLC_MIR_H
#define LOWER_MEASUREMENT_E2SM_LLC_MIR_H 

#include "slot_tstamp.h"
#include "dl_rlc_buffer_status.h"
#include "dl_pdcp_buffer_status.h"
#include "dl_harq_stats.h"

#include <stdbool.h>

typedef enum{
  DL_RLC_BUFFER_STATUS_LOWER_LAYER_MEASURE_E,
  // 8.3.22
  DL_PDCP_BUFFER_STATUS_LOWER_LAYER_MEASURE_E,
  // 8.3.23
  DL_HARQ_STATISTICS_LOWER_LAYER_MEASURE_E, 
  SLOT_TIME_STAMP_LOWER_LAYER_MEASURE_E,
  END_LOWER_LAYER_MEASURE_E 
} lower_layer_measure_llc_e;

// From 8.2.1.4.2
typedef struct{

  // 8.3.18
  // Slot Time Stamp 
  // Mandatory 
  slot_tstamp_t slot_tstamp; 

  // Lower Layers Measurement Type
  lower_layer_measure_llc_e type;
  union{
  // 8.3.21
  dl_rlc_buffer_status_t rlc;
  // 8.3.22
  dl_pdcp_buffer_status_t pdcp;
  //8.3.23
  dl_harq_stats_t harq;
  // Bug in the standard???   
  // slot_tstamp_t slot_tstamp2;
  };

} lower_measure_t;

lower_measure_t cp_lower_measure(lower_measure_t const* src);  

void free_lower_measure(lower_measure_t* src); 

bool eq_lower_measure(lower_measure_t const* m0, lower_measure_t const* m1);

#endif
