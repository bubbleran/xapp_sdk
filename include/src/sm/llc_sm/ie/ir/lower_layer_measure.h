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

#ifndef E2SM_LLC_LOWER_LAYER_MEASUREMENT_TYPE_MIR_H
#define E2SM_LLC_LOWER_LAYER_MEASUREMENT_TYPE_MIR_H 

// 8.3.16
typedef enum {
  DL_RLC_BUFFER_STATUS_LLM_E,
  DL_PDCP_Buffer_Status_LLM_E,
  DL_HARQ_Statistics_LLM_E,
  SLOT_TIME_STAMP_LLM_E,
  END_LLM_E,
} lower_layer_measure_e;

#endif
