/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef NR_FREQUENCY_BAND_ITEM_E2SM_MIR_H
#define NR_FREQUENCY_BAND_ITEM_E2SM_MIR_H 

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>


// 6.2.3.35
typedef struct
{
  uint16_t bnd; // [1,1024]

  // [0,32]
  size_t sz_sul;
  uint16_t* sul_bnd_it; // [1,1024]

} nr_frq_bnd_it_t;

void free_nr_frq_bnd_it( nr_frq_bnd_it_t* src);

bool eq_nr_frq_bnd_it( nr_frq_bnd_it_t const* m0,  nr_frq_bnd_it_t const* m1);

nr_frq_bnd_it_t cp_nr_frq_bnd_it(nr_frq_bnd_it_t const* src);

#endif

