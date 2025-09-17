#ifndef SRS_LLC_MIR_H
#define SRS_LLC_MIR_H 

#include "srs_rx_antenna.h"

#include <stdbool.h>

// 8.3.19
typedef struct{
  // [1,65535]
  size_t sz_srs_rx_antenna;
  srs_rx_antenna_t* rx; 
} srs_llc_t;

void free_srs_llc(srs_llc_t* src);

bool eq_srs_llc( srs_llc_t const* m0, srs_llc_t const* m1);

srs_llc_t cp_srs_llc(srs_llc_t const* src);

#endif
