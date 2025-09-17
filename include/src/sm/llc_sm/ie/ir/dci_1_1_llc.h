#ifndef DCI_1_1_LLC_E2SM_MIR_H
#define DCI_1_1_LLC_E2SM_MIR_H 

#include <stdbool.h>
#include <stdint.h>
#include "cs_rnti.h"
#include "vrb_to_prb_map.h"
#include "../../../../util/byte_array.h"

// From 8.3.26
typedef struct{

  // Optional
  cs_rnti_t* cs_rnti;

  // Optional
  // [1,7]
  uint32_t* carrier_indicator;

  // Mandatory
  // Freq Domain Resources
  byte_array_t freq_domain_res;

  // Mandatory
  // Time Domain Resources
  // [0,15]
  uint32_t time_domain_res;

  // Optional
  // VRB to PRB Mapping
  vrb_to_prb_map_e* vrb_to_prb_map;

  // Bug in the standard!!!!
  // Optional in text, Mandatory in ASN1.
  // Lets make it mandatory...
  // PRB Bundling Size Indicator
  // [0,1]
  uint32_t prb_bund_sz_ind;

  // Mandatory
  // [0,31]
  uint32_t tb1_mcs; 

  // Mandatory
  // [0,3]
  uint32_t tb1_version; 

  // Optional
  // [0,31]
  uint32_t* tb2_mcs; 

  // Mandatory
  // [0,3]
  uint32_t* tb2_version; 

  // Antenna ports 
  // Mandatory 
  // [4,6]
  byte_array_t antenna_ports;

  // Transmission Configuration Indication
  // Optional
  // [0,7]
  uint32_t* tx_conf_ind;

  // SRS Request 
  // Optional
  // [2,3]
  byte_array_t* srs_req;

  // DMRS Sequence Initialization
  // Mandatory
  // [0,1]
  uint32_t dmrs_seq_init; 

} dci_1_1_llc_t;

dci_1_1_llc_t cp_dci_1_1_llc(dci_1_1_llc_t const* src);

void free_dci_1_1_llc(dci_1_1_llc_t* src);

bool eq_dci_1_1_llc(dci_1_1_llc_t const* m0, dci_1_1_llc_t const* m1);

#endif

