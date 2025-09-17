#ifndef PRECODER_COEFF_E2SM_LLC_MIR_H
#define PRECODER_COEFF_E2SM_LLC_MIR_H 

#include <stdbool.h>
#include <stdint.h>

// From 8.3.26  
typedef struct{

  // Precoder Coefficient I
  // Mandatory
  int32_t i;

  // Precoder Coefficient Q
  // Mandatory
  int32_t q;

} precoder_coeff_t;

precoder_coeff_t cp_precoder_coeff(precoder_coeff_t src);

void free_precoder_coeff(precoder_coeff_t src);

bool eq_precoder_coeff(precoder_coeff_t const* m0,  precoder_coeff_t const* m1); 

#endif
