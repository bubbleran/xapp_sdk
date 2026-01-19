#ifndef LOGICAL_CHANNEL_LLC_E2SM_MIR_H
#define LOGICAL_CHANNEL_LLC_E2SM_MIR_H 

#include <stdbool.h>
#include <stdint.h>

// From 8.3.26    
typedef struct{
  //Logical Channel ID 
  //Mandatory 
  //[1,32]
  uint32_t log_channel_id;

  // TB1 Number of Bytes 
  // Mandatory
  uint32_t tb1_bytes;

  // TB2 Number of Bytes
  // Optional
  uint32_t* tb2_bytes;

} log_chann_llc_t;

log_chann_llc_t cp_log_chann_llc(log_chann_llc_t const* src);

void free_log_chann_llc(log_chann_llc_t* src);

bool eq_log_chann_llc(log_chann_llc_t const* m0, log_chann_llc_t const* m1);


#endif
