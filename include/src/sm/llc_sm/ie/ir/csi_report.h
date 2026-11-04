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

#ifndef CSI_REPORT_E2SM_LLC_MIR_H
#define CSI_REPORT_E2SM_LLC_MIR_H

#include <stdbool.h>
#include "../../../../util/byte_array.h"


// From 8.3.20
typedef struct{

  // Mandatory
  // [0,47]
  uint32_t config_id;

  // CSI Fields of CSI Report Part 1
  // Mandatory
  byte_array_t part1;

  // CSI Fields of CSI Report Part 2
  // C-ifCsiPart2
  byte_array_t* part2;

} csi_report_t;

csi_report_t cp_csi_report( csi_report_t const* src);

void free_csi_report(csi_report_t* src);

bool eq_csi_report(csi_report_t const* m0, csi_report_t const* m1);


#endif
