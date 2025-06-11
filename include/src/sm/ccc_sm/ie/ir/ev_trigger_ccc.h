/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef EVENT_TRIGGER_CCC_H
#define EVENT_TRIGGER_CCC_H

#include "../../../../util/byte_array.h"

typedef struct {
  // Event trigger style type
  // Mandatory
  // 9.3.3
  // Defined in common 6.2.2.2.
  uint32_t ev_trigger_style_type;

  // Event trigger style name
  // Mandatory
  // 9.3.4
  // Defined in common 6.2.2.3
  // Printable string - [1 - 150]
  byte_array_t ev_trigger_style_name;

  // Event trigger format type
  // Mandatory
  // 9.3.5
  // Defined in common 6.2.2.4
  uint32_t ev_trigger_fmr_type;

} lst_ev_trigger_ccc_t;

// 9.2.2.2.1
typedef struct {
  // Event trigger
  // List of supported event trigger styles
  // [1..63]
  size_t sz_lst_ev_trigger_ccc;
  lst_ev_trigger_ccc_t* lst_ev_trigger_ccc;
} ev_trigger_ccc_t;

void free_ev_trigger_ccc(ev_trigger_ccc_t* src);

bool eq_ev_trigger_ccc(ev_trigger_ccc_t const* m0, ev_trigger_ccc_t const* m1);

ev_trigger_ccc_t cp_ev_trigger_ccc(ev_trigger_ccc_t const* src);

#endif

