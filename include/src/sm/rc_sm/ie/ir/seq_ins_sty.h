#ifndef SEQ_INS_STY_E2SM_RC_H
#define SEQ_INS_STY_E2SM_RC_H

#include "../../../../util/byte_array.h"

#include "seq_ins_ind.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

// From 9.2.2.4
typedef struct{
  // RIC Insert Style Type
  // Mandatory
  // 9.3.3
  // 6.2.2.2.
  // INTEGER
  uint32_t style_type;

  // RIC Insert Style Name
  // Mandatory
  // 9.3.4
  // 6.2.2.3.
  // [1-150]
  byte_array_t name;

  // Supported RIC Event Trigger Style Type
  // Mandatory
  // 9.3.3
  // 6.2.2.2.
  uint32_t ev_trig_style_type;

  // RIC Action Definition Format Type
  // Mandatory
  // 9.3.5
  // 6.2.2.4.
  uint32_t act_def_frmt_type;

  // Sequence of Insert Indications
  // [0-65535]
  size_t sz_seq_ins_ind;
  seq_ins_ind_t* seq_ins_ind;

  // RIC Indication Header Format Type
  // Mandatoyr
  // 9.3.5
  // 6.2.2.4.
  uint32_t ind_hdr_frmt_type;

  // RIC Indication Message Format Type
  // Mandatory
  // 9.3.5
  // 6.2.2.4.
  uint32_t ind_msg_frmt_type;

  // RIC Call Process ID Format Type
  // Mandatory
  // 9.3.5
  // 6.2.2.4.
  uint32_t call_proc_id_type;

} seq_ins_sty_t;

void free_seq_ins_sty(seq_ins_sty_t* src);

bool eq_seq_ins_sty(seq_ins_sty_t const* m0, seq_ins_sty_t const* m1);

seq_ins_sty_t cp_seq_ins_sty(seq_ins_sty_t const* src);

#endif
