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

#ifndef DL_PDCP_BUFFER_STATUS_E2SM_MIR_H
#define DL_PDCP_BUFFER_STATUS_E2SM_MIR_H 

#include "dl_pdcp_ue_id.h"
#include <stdbool.h>

// From 8.3.22 
typedef struct{
  // [1, 65535]
  size_t sz_dl_pdcp_ue_id;
  dl_pdcp_ue_id_t* dl_pdcp_ue_id;
} dl_pdcp_buffer_status_t;

dl_pdcp_buffer_status_t cp_dl_pdcp_buffer_status(dl_pdcp_buffer_status_t const* src);  

void free_dl_pdcp_buffer_status(dl_pdcp_buffer_status_t* src); 

bool eq_dl_pdcp_buffer_status(dl_pdcp_buffer_status_t const* m0, dl_pdcp_buffer_status_t const* m1); 



#endif
