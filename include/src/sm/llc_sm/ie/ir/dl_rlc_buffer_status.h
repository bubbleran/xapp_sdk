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

#ifndef DL_RLC_BUFFER_STATUS_E2SM_LLC_MIR_H
#define DL_RLC_BUFFER_STATUS_E2SM_LLC_MIR_H 

#include "dl_rlc_ue_id.h"
#include <stdbool.h>

// 8.3.21
typedef struct{
  // [1,65535]
  size_t sz_ue; 
  dl_rlc_ue_id_t* ue;
} dl_rlc_buffer_status_t ;

dl_rlc_buffer_status_t cp_dl_rlc_buffer_status(dl_rlc_buffer_status_t const* src);

bool eq_dl_rlc_buffer_status(dl_rlc_buffer_status_t const* m0, dl_rlc_buffer_status_t const* m1);

void free_dl_rlc_buffer_status(dl_rlc_buffer_status_t const* src);  

#endif
