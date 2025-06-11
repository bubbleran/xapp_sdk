#ifndef SEQ_REPORT_STY_E2SM_RC_H
#define SEQ_REPORT_STY_E2SM_RC_H

#include <stdlib.h>
#include "seq_ran_param_3.h"

// From 
// 9.2.2.3
typedef struct{
  // RIC Report Style Type
  // Mandatory
  // 9.3.3
  // 6.2.2.2.
  // INTEGER
  uint32_t report_type;

  // RIC Report Style Name
  // Mandatory
  // 9.3.4
  // 6.2.2.3.
  // PrintableString(SIZE(1..150,...)) 
  byte_array_t name;

  // Supported RIC Event Trigger Style Type 
  // Mandatory
  // 9.3.3
  // 6.2.2.2.
  // INTEGER
  uint32_t ev_trig_type;

  // RIC Report Action Format Type
  // Mandatory
  // 9.3.5
  // 6.2.2.4.
  // INTEGER
  uint32_t act_frmt_type;

  // RIC Indication Header Format Type
  // Mandatory
  // 9.3.5
  // 6.2.2.4.
  // INTEGER
  uint32_t ind_hdr_type;

  // RIC Indication Message Format Type
  // Mandatory
  // 9.3.5
  // 6.2.2.4.
  // INTEGER
  uint32_t ind_msg_type;

  // Sequence of RAN Parameters Supported
  // [0 - 65535]
  size_t sz_seq_ran_param;
  seq_ran_param_3_t* ran_param; 

} seq_report_sty_t;

void free_seq_report_sty(seq_report_sty_t* src);

seq_report_sty_t cp_seq_report_sty(seq_report_sty_t const* src);

bool eq_seq_report_sty(seq_report_sty_t const* m0, seq_report_sty_t const* m1); 

#endif
