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

#ifndef EVENT_TRIGGER_UE_INFO_MIR_H
#define EVENT_TRIGGER_UE_INFO_MIR_H 

#include "assoc_ue_info_llc.h"

#include <stdbool.h>

// 8.3.12
typedef struct{
  // [1,65535]
  size_t sz_assoc_ue_info;
  assoc_ue_info_llc_t* assoc_ue_info;
} ev_trg_ue_info_t;

ev_trg_ue_info_t cp_ev_trg_ue_info(ev_trg_ue_info_t const* src); 

void free_ev_trg_ue_info(ev_trg_ue_info_t* src);

bool eq_ev_trg_ue_info(ev_trg_ue_info_t const* m0, ev_trg_ue_info_t const* m1);

#endif
