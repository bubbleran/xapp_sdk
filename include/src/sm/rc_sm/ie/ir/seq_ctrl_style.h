#ifndef SEQUENCE_CONTROL_STYLE_E2SM_RC_H
#define SEQUENCE_CONTROL_STYLE_E2SM_RC_H

#include "call_proc_id_frmt.h"
#include "seq_ctrl_act_2.h"
#include "seq_ran_param_3.h"

#include <stdbool.h>
#include <stdlib.h>

// From 
// 9.2.2.5
typedef struct{
  // RIC Control Style Type
  // Mandatory
  // 9.3.3
  // 6.2.2.2.
  uint32_t style_type;

  //RIC Control Style Name
  //Mandatory
  //9.3.4
  // [1 -150]
  byte_array_t name;

  // Sequence of Control Actions
  // [0-65535]
  size_t sz_seq_ctrl_act;
  seq_ctrl_act_2_t* seq_ctrl_act;

  // RIC Control Header Format Type
  // Mandatory
  // 9.3.5
  uint32_t hdr;

  // RIC Control Message Format Type
  // Mandatory
  // 9.3.5
  uint32_t msg;

  // RIC Call Process ID Format Type
  // Optional
  uint32_t* call_proc_id_type;

  // RIC Control Outcome Format Type
  // Mandatory
  // 9.3.5
  uint32_t out_frmt;

  // Sequence of Associated RAN 
  // Parameters for Control Outcome
  // [0- 255]
  size_t sz_ran_param_ctrl_out;
  seq_ran_param_3_t* ran_param_ctrl_out;

} seq_ctrl_style_t;

void free_seq_ctrl_style(seq_ctrl_style_t* src);

bool eq_seq_ctrl_style( seq_ctrl_style_t const* m0, seq_ctrl_style_t const* m1);

seq_ctrl_style_t cp_seq_ctrl_style(seq_ctrl_style_t const* src);

#endif

