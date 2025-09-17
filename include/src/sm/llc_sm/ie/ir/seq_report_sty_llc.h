#ifndef SEQ_REPORT_STY_LLC_E2SM_MIR_H
#define SEQ_REPORT_STY_LLC_E2SM_MIR_H

// From 8.2.2.3
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

} seq_report_sty_llc_t;


#endif
