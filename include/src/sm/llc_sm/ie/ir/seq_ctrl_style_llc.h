#ifndef SEQ_CTRL_STYLE_LLC_E2SM_MIR_H
#define SEQ_CTRL_STYLE_LLC_E2SM_MIR_H 

#include <stdbool.h>
#include <stdint.h>

#include "../../../../util/byte_array.h"
#include "seq_ctrl_act_llc.h"

typedef struct{
  // RIC Control Style Type
  // Mandatory
  // 8.3.3
  // 6.2.2.2.
  uint32_t style_type;

  //RIC Control Style Name
  //Mandatory
  //8.3.4
  // [1 -150]
  byte_array_t name;

  // Sequence of Control Actions
  // [0-65535]
  size_t sz_seq_ctrl_act;
  seq_ctrl_act_llc_t* seq_ctrl_act;
  
  // RIC Control Header Format Type
  // Mandatory
  // 8.3.5
  uint32_t hdr;

  // RIC Control Message Format Type
  // Mandatory
  // 8.3.5
  uint32_t msg;

  // RIC Call Process ID Format Type
  // Optional
  uint32_t* call_proc_id_type;

  // RIC Control Outcome Format Type
  // Mandatory
  // 8.3.5
  uint32_t out_frmt;

} seq_ctrl_style_llc_t;

seq_ctrl_style_llc_t cp_seq_ctrl_style_llc(seq_ctrl_style_llc_t const* src);

void free_seq_ctrl_style_llc(seq_ctrl_style_llc_t* src);

bool eq_seq_ctrl_style_llc(seq_ctrl_style_llc_t const* m0, seq_ctrl_style_llc_t const* m1);

#endif
