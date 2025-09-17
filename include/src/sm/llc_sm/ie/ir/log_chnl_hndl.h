#ifndef LOG_CHNL_HNDL_E2SM_LLC_MIR_H
#define LOG_CHNL_HNDL_E2SM_LLC_MIR_H

#include <stdint.h>

// 8.3.24
typedef struct{

  // Received Timestamp 
  // Mandatory
  uint8_t tstamp[8];

} log_chnl_hndl_t ;

#endif
