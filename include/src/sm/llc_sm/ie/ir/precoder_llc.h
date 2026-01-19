#ifndef PRECODER_LLC_E2SM_MIR_H
#define PRECODER_LLC_E2SM_MIR_H 

#include "compress_info.h"
#include "precoder_coeff.h"

#include <stdbool.h>

// From 8.3.26  
typedef struct{

  // Compression Information
  // Optional 
  compress_info_t* compress_info;

  // List of Precoder Coefficients 
  // [0,65535] 
  size_t sz_precoder_coeff;
  precoder_coeff_t* precoder_coeff; 

} precoder_llc_t;

precoder_llc_t cp_precoder_llc(precoder_llc_t const* src);

void free_precoder_llc(precoder_llc_t* src);

bool eq_precoder_llc(precoder_llc_t const* m0, precoder_llc_t const* m1);

#endif
