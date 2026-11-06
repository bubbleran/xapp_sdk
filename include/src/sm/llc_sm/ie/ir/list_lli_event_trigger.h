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

#ifndef LIST_LLI_EVENT_TRIGGER_MIR_H
#define LIST_LLI_EVENT_TRIGGER_MIR_H 

#include "assoc_ue_info_llc.h"
#include "ev_trg_ue_info.h"
#include "logical_or_llc.h"
#include "lower_layer_info.h"

typedef struct{
  // 8.3.9
  // Event Trigger Condition ID
  // Mandatory
  // (1..65535, …)
  uint32_t ev_trg_cond_id;  

  // 8.3.15
  // Lower Layers Information Type
  // Mandatory 
  lower_layer_info_e lower_layer_info;

  // 8.3.12
  // Associated UE Info  
  // Optional
  ev_trg_ue_info_t* assoc_ue_info;

  // 8.3.11
  // Logical OR 
  // Optional
  logical_or_llc_e* logical_or;

} lst_lli_ev_trg_t;

lst_lli_ev_trg_t cp_lst_lli_ev_trg(lst_lli_ev_trg_t const* src);

void free_lst_lli_ev_trg(lst_lli_ev_trg_t* src);

bool eq_lst_lli_ev_trg(lst_lli_ev_trg_t const* m0, lst_lli_ev_trg_t const* m1);

#endif
