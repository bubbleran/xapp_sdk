/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef EV_TRG_RAN_CONF_H
#define EV_TRG_RAN_CONF_H

#include "attribute.h"
#include "../../../../util/byte_array.h"

typedef struct{
  // RAN Configuration Structure Name
  // Mandatory
  // 9.3.7
  byte_array_t ran_conf_name;

  // List of Attributes
  // [0 - 66535]
  size_t sz_attribute;
  attribute_t* attribute;

} ev_trg_ran_conf_t;

void free_ev_trg_ran_conf(ev_trg_ran_conf_t* src);

bool eq_ev_trg_ran_conf(ev_trg_ran_conf_t const* m0, ev_trg_ran_conf_t const* m1);

ev_trg_ran_conf_t cp_ev_trg_ran_conf(ev_trg_ran_conf_t const* src);

#endif

