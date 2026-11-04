/*

Copyright (C) 2026 BubbleRAN

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see http://www.gnu.org/licenses/.
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

