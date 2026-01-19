#ifndef RAN_FUNC_DEF_EVENT_TRIGGER_LLC_MIR_H
#define RAN_FUNC_DEF_EVENT_TRIGGER_LLC_MIR_H 

#include "seq_ev_trg_style.h"

typedef struct{

  // List of EVENT TRIGGER styles
  // [1,63]
  size_t sz_seq_ev_trg_style;
  seq_ev_trg_style_t* seq_ev_trg_style;

} ran_func_def_ev_trig_llc_t;

#endif
