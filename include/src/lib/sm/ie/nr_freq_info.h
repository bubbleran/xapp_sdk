/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef NR_FREQ_INFO_RC_SM_MIR_H
#define NR_FREQ_INFO_RC_SM_MIR_H 

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "nr_frq_bnd_it.h"

// 9.3.44
// 6.2.3.36.
// Bug in the standard!!!
// 6.2.3.36 should be 6.2.3.35
// for O-RAN.WG3.E2SM-R003-v05.00
// 6.2.3.35
typedef struct {
  //NR ARFCN
  //Mandatory
  //6.2.3.30
  uint32_t arfcn; // [0,3279165]

  // [1,32]
  nr_frq_bnd_it_t* frq_bnd_it;
  size_t sz_frq_bnd_it;

  // NRFrequency Shift
  // 7p5khz
  // Optional
  bool* freq_shift_7p5khz;

} nr_freq_info_t;

void free_nr_freq_info(nr_freq_info_t* src);

bool eq_nr_freq_info(nr_freq_info_t const* m0, nr_freq_info_t const* m1);

nr_freq_info_t cp_nr_freq_info(nr_freq_info_t const* src);



#endif
