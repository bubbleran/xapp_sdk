#ifndef SRS_RX_ANTENNA_LLC_MIR_H
#define SRS_RX_ANTENNA_LLC_MIR_H 

#include "srs_symbol.h"
#include <stdbool.h>

// From 8.3.19
typedef struct{
  // Valid values: {1,2,4}
  size_t sz_srs_symbols;
  srs_symbol_t* symbol; 
} srs_rx_antenna_t;

srs_rx_antenna_t cp_srs_rx_antenna(srs_rx_antenna_t const* src); 

bool eq_srs_rx_antenna(srs_rx_antenna_t const* m0, srs_rx_antenna_t const* m1);

void free_srs_rx_antenna(srs_rx_antenna_t* src);

#endif
