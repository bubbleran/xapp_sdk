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

#ifndef LIST_LOGICAL_CHANNEL_UE_ID_LLC_E2SM_MIR_H
#define LIST_LOGICAL_CHANNEL_UE_ID_LLC_E2SM_MIR_H 

#include "logical_channel_ue_id.h"
#include <stdbool.h>

typedef struct{
  //[0, 65535]
  size_t sz_logical_channel_ue_id;
  logical_channel_ue_id_t* logical_channel_ue_id; 
} lst_logical_channel_ue_id_t;

lst_logical_channel_ue_id_t cp_lst_logical_channel_ue_id(lst_logical_channel_ue_id_t const* src);

void free_lst_logical_channel_ue_id(lst_logical_channel_ue_id_t* src);

bool eq_lst_logical_channel_ue_id(lst_logical_channel_ue_id_t const* m0, lst_logical_channel_ue_id_t const* m1);

#endif
