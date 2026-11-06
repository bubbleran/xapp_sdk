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

#ifndef SUPPORTED_SERVICES_H
#define SUPPORTED_SERVICES_H

#include "stdint.h"
#include "../../../../util/byte_array.h"
#include "ev_trigger_ccc.h"
#include "report_service_ccc.h"
#include "control_service_ccc.h"

typedef struct {
  // Empty
  uint32_t dummy;
} insert_service_ccc_t;

typedef struct {
  // Empty
  uint32_t dummy;
} policy_service_ccc_t;

typedef struct {
  // Event Trigger
  // Optional
  // 9.2.2.2.1
  ev_trigger_ccc_t* ev_trigger_ccc;

  // Report service
  // Optional
  // 9.2.2.2.2
  report_service_ccc_t* report_service_ccc;

  // Insert service
  // Optional
  // 9.2.2.2.3
  insert_service_ccc_t* insert_service_ccc;

  // Control service
  // Optional
  // 9.2.2.2.4
  control_service_ccc_t* control_service_ccc;

  // Policy service
  // Optional
  // 9.2.2.2.5
  policy_service_ccc_t* policy_service_ccc;

} supported_services_t;

void free_supported_services(supported_services_t* src);

bool eq_supported_services(supported_services_t const* m0, supported_services_t const* m1);

supported_services_t cp_supported_services(supported_services_t const* src);

#endif
