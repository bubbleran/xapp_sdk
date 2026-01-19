#ifndef PDSCH_SMG_E2SM_LLC_MIR_H
#define PDSCH_SMG_E2SM_LLC_MIR_H 

#include <stdbool.h>
#include <stdint.h>


// From 8.3.26 
typedef struct{

  // Precoder ID
  // Mandatory
  // [0,63]
  uint32_t precoder_id;

  // SMG Priority
  // Optional
  // [0,31]
  uint32_t* smg_priority;

  // Start RB
  // Mandatory
  uint32_t start_rb;

  // Number of RBs
  // Mandatory
  uint32_t num_rb;

  // Start Symbol 
  // Mandatory
  uint32_t start_symb;

  // Number of Symbols
  // Mandatory
  uint32_t num_symb;

} pdsch_smg_t; 

pdsch_smg_t cp_pdsch_smg(pdsch_smg_t const* src); 

void free_pdsch_smg(pdsch_smg_t* src); 

bool eq_pdsch_smg(pdsch_smg_t const* m0, pdsch_smg_t const* m1);

#endif
