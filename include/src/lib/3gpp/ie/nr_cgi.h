/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef NR_CGI_KPM_V2_H
#define NR_CGI_KPM_V2_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "plmn_identity.h"

//  6.2.3.7  NR CGI

typedef struct{
  e2sm_plmn_t plmn_id;  // 6.2.3.1
  // Not using nr_cell_id:36 since bit fields are nto addressable, 
  // and thus, memcpy does not work   
  uint64_t nr_cell_id; // bit string of 36 bits
} nr_cgi_t;

void free_nr_cgi(nr_cgi_t* src);

bool eq_nr_cgi(nr_cgi_t const * m0, nr_cgi_t const * m1);

nr_cgi_t cp_nr_cgi(nr_cgi_t const* src);

#ifdef __cplusplus
}
#endif

#endif

