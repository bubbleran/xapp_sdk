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

#ifndef REPORT_SERVICE_CCC_H
#define REPORT_SERVICE_CCC_H

#include "../../../../util/byte_array.h"

typedef struct {

  // Event trigger style type
  // Mandatory
  // 9.3.3
  // Defined in common 6.2.2.2.
  uint32_t ev_trigger_style_type;

} lst_sp_ev_trigger_styles_report_service_t;

typedef struct {
  // Report service style type
  // Mandatory
  // 9.3.3
  // Defined in common 6.2.2.2.
  uint32_t report_service_style_type;

  // Report service style name
  // Mandatory
  // 9.3.4
  // Defined in common 6.2.2.3
  // Printable string - [1 - 150]
  byte_array_t report_service_style_name;

  // List of Supported Event Trigger Styles
  // Mandatory
  // [1..63]
  size_t sz_lst_sp_ev_trigger_styles_report_service;
  lst_sp_ev_trigger_styles_report_service_t* lst_sp_ev_trigger_styles_report_service;

  // Report Service Action Definition Format Type
  // Mandatory
  // 9.3.5
  // Defined in common 6.2.2.4
  uint32_t report_service_action_def_fmr_type;

  // Report Service Indication Header Format Type
  // Mandatory
  // 9.3.5
  // Defined in common 6.2.2.4
  uint32_t report_service_ind_header_fmr_type;

  // Report Service Indication Message Format Type
  // Mandatory
  // 9.3.5
  // Defined in common 6.2.2.4
  uint32_t report_service_ind_message_fmr_type;

} lst_report_service_ccc_t;

// 9.2.2.2.2
typedef struct {
  // Report style
  // List of Supported Report Styles
  // [1..63]
  size_t sz_lst_report_service_ccc;
  lst_report_service_ccc_t* lst_report_service_ccc;

} report_service_ccc_t;

void free_report_service_ccc(report_service_ccc_t* src);

bool eq_report_service_ccc(report_service_ccc_t const* m0, report_service_ccc_t const* m1);

report_service_ccc_t cp_report_service_ccc(report_service_ccc_t const* src);

#endif

