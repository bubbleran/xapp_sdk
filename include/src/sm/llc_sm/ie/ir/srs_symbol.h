#ifndef SRS_E2SM_LLC_SYMBOL_MIR_H
#define SRS_E2SM_LLC_SYMBOL_MIR_H 

#include <stdbool.h>
#include <stdint.h>
#include "../../../../util/byte_array.h"

// From 8.3.19
typedef struct{
  // SRS Compression Header
  // C-ifStaticSRS
  uint8_t hdr;

  //  As defined in O-RAN
  // WG4.TS.CUS [8] Table 8.3.2-1
  // starting from Octet 13.
  // pag. 368
  byte_array_t raw_iq;

} srs_symbol_t;

srs_symbol_t cp_srs_symbol(srs_symbol_t const* src); 

void free_srs_symbol(srs_symbol_t* src); 

bool eq_srs_symbol(srs_symbol_t const* m0, srs_symbol_t const* m1);

#endif
