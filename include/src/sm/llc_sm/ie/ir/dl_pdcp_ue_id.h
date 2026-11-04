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

#ifndef DL_PDCP_UE_ID_E2SM_LLC_MIR_H
#define DL_PDCP_UE_ID_E2SM_LLC_MIR_H 

#include "../../../../lib/sm/ie/ue_id.h"

#include "dl_pdcp_ue_bearer.h"

// From 8.3.22 
typedef struct{
  // 8.3.8
  // Mandatory
  ue_id_e2sm_t ue_id;

  // [1,225]
  size_t sz_dl_pdcp_ue_bearer;
  dl_pdcp_ue_bearer_t* dl_pdcp_ue_bearer;

} dl_pdcp_ue_id_t;

dl_pdcp_ue_id_t cp_dl_pdcp_ue_id(dl_pdcp_ue_id_t const* src);

bool eq_dl_pdcp_ue_id(dl_pdcp_ue_id_t const* m0,dl_pdcp_ue_id_t const* m1);

void free_dl_pdcp_ue_id(dl_pdcp_ue_id_t* src); 


#endif
