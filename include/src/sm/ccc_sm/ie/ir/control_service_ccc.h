/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef CONTROL_SERVICE_CCC_H
#define CONTROL_SERVICE_CCC_H

#include "../../../../util/byte_array.h"

typedef struct {
  // Control Service Style Type
  // Mandatory
  // 9.3.3
  // Defined in common 6.2.2.2.
  uint32_t control_service_style_type;

  // Control Service Style Name
  // Mandatory
  // 9.3.4
  // Defined in common 6.2.2.3
  // Printable string - [1 - 150]
  byte_array_t control_service_style_name;

  // Control Service Header Format Type
  // Mandatory
  // 9.3.5
  // Defined in common 6.2.2.4
  uint32_t control_service_header_fmr_type;

  // Control Service Message Format Type
  // Mandatory
  // 9.3.5
  // Defined in common 6.2.2.4
  uint32_t control_service_message_fmr_type;

  // RIC Call Process ID Format Type
  // Optional
  // 9.3.5
  // Defined in common 6.2.2.4
  uint32_t* ric_call_process_id_fmr_type;

  // Control Service Control Outcome Format Type
  // Mandatory
  // 9.3.5
  // Defined in common 6.2.2.4
  uint32_t control_service_control_outcome_fmr_type;

} lst_control_service_ccc_t;

// 9.2.2.2.1
typedef struct {
  // Control service
  // List of supported Control service styles
  // [1..63]
  size_t sz_lst_control_service_ccc;
  lst_control_service_ccc_t* lst_control_service_ccc;
} control_service_ccc_t;

void free_control_service_ccc(control_service_ccc_t* src);

bool eq_control_service_ccc(control_service_ccc_t const* m0, control_service_ccc_t const* m1);

control_service_ccc_t cp_control_service_ccc(control_service_ccc_t const* src);

#endif

