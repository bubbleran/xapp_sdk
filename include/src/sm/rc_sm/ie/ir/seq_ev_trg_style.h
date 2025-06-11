#ifndef SEQ_EV_TRG_STYLE_E2SM_RC_H
#define SEQ_EV_TRG_STYLE_E2SM_RC_H

#include "../../../../util/byte_array.h"

#include <stddef.h>
#include <stdint.h>

// From 9.2.2.2
typedef struct{
  // RIC Event Trigger Style Type
  // Mandatory
  // 9.3.3
  // 6.2.2.2.
  //  INTEGER
  uint32_t style;

  // RIC Event Trigger Style Name
  // Mandatory
  // 9.3.4
  // 6.2.2.3
  //PrintableString(SIZE(1..150,...))
  byte_array_t name;

  // RIC Event Trigger Format Type
  // Mandatory
  // 9.3.5
  // 6.2.2.4.
  // INTEGER
  uint32_t format;

} seq_ev_trg_style_t;

void free_seq_ev_trg_style(seq_ev_trg_style_t* src);

bool eq_seq_ev_trg_style( seq_ev_trg_style_t const* m0,  seq_ev_trg_style_t const* m1);

seq_ev_trg_style_t cp_seq_ev_trg_style(seq_ev_trg_style_t const* src);

#endif

