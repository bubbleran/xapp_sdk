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

#ifndef CSI_UE_ID_E2SM_LLC_MIR_H
#define CSI_UE_ID_E2SM_LLC_MIR_H 

#include "../../../../lib/sm/ie/ue_id.h"
#include "csi_report.h"
#include <stdbool.h>


typedef enum{
  PUCCH_UCI_CHANNEL_E, 
  PUSCH_UCI_CHANNEL_E,
  END_UCI_CHANNEL_E 
} uci_channel_e; 

// From 8.3.20
typedef struct{
  // 8.3.8
  // Mandatory
  ue_id_e2sm_t ue_id;

  // Channel carrying the UCI 
  // Mandatory
  uci_channel_e channel;

  // [1,255]
  size_t sz_csi_report;
  csi_report_t* csi_report;

} csi_ue_id_t;

csi_ue_id_t cp_csi_ue_id(csi_ue_id_t const* src); 

void free_csi_ue_id(csi_ue_id_t* src); 

bool eq_csi_ue_id(csi_ue_id_t const* m0, csi_ue_id_t const* m1); 

#endif
