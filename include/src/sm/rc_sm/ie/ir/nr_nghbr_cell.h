#ifndef NR_NGHBR_CELL_MIR_H
#define NR_NGHBR_CELL_MIR_H 

#include "../../../../lib/3gpp/ie/nr_cgi.h"
#include "../../../../lib/sm/ie/nr_freq_info.h"

typedef enum{
  FDD_MODE_NR_NGHBR_CELL_E, 
  TDD_MODE_NR_NGHBR_CELL_E,

  END_MODE_NR_NGHBR_CELL_E
} mode_nr_nghbr_cell_e;

typedef struct{
  // 9.3.41
  // NR CGI
  // 6.2.3.7
  // Mandatory
  nr_cgi_t cgi;

  // 9.3.42
  // NR PCI
  // Mandatory
  uint16_t pci; //[0,1007]

  // 9.3.43
  // 5GS TAC
  // 6.2.3.31
  // Defined in TS 38.473
  // 9.3.1.29
  // Mandatory
  uint8_t tac[3];

  // NR Mode Info
  // Mandatory
  mode_nr_nghbr_cell_e mode_info;

  // 9.3.44
  // NR Frequency Info
  // 6.2.3.36.
  // Bug in the standard!!!
  // 6.2.3.36 should be 6.2.3.35
  // for O-RAN.WG3.E2SM-R003-v05.00
  // NR Frequency Info 
  // Mandatory
  nr_freq_info_t nr_freq_info;

  // Xn X2 Established
  // Mandatory
  bool xn_x2_established;

  // HO Validated
  // Mandatory
  bool ho_validated;

  // Version
  // Mandatory
  // [1-65535] 
  uint16_t version;

} nr_nghbr_cell_t;

void free_nr_nghbr_cell(nr_nghbr_cell_t* src);

bool eq_nr_nghbr_cell(nr_nghbr_cell_t const* m0, nr_nghbr_cell_t const* m1);

nr_nghbr_cell_t cp_nr_nghbr_cell(nr_nghbr_cell_t const* src);

#endif

