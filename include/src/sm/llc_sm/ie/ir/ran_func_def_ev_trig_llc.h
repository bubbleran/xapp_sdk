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

#ifndef RAN_FUNC_DEF_EVENT_TRIGGER_LLC_MIR_H
#define RAN_FUNC_DEF_EVENT_TRIGGER_LLC_MIR_H 

#include "seq_ev_trg_style.h"

typedef struct{

  // List of EVENT TRIGGER styles
  // [1,63]
  size_t sz_seq_ev_trg_style;
  seq_ev_trg_style_t* seq_ev_trg_style;

} ran_func_def_ev_trig_llc_t;

#endif
