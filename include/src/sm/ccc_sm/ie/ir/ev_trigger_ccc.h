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

#ifndef EVENT_TRIGGER_CCC_H
#define EVENT_TRIGGER_CCC_H

#include "../../../../util/byte_array.h"

typedef struct {
  // Event trigger style type
  // Mandatory
  // 9.3.3
  // Defined in common 6.2.2.2.
  uint32_t ev_trigger_style_type;

  // Event trigger style name
  // Mandatory
  // 9.3.4
  // Defined in common 6.2.2.3
  // Printable string - [1 - 150]
  byte_array_t ev_trigger_style_name;

  // Event trigger format type
  // Mandatory
  // 9.3.5
  // Defined in common 6.2.2.4
  uint32_t ev_trigger_fmr_type;

} lst_ev_trigger_ccc_t;

// 9.2.2.2.1
typedef struct {
  // Event trigger
  // List of supported event trigger styles
  // [1..63]
  size_t sz_lst_ev_trigger_ccc;
  lst_ev_trigger_ccc_t* lst_ev_trigger_ccc;
} ev_trigger_ccc_t;

void free_ev_trigger_ccc(ev_trigger_ccc_t* src);

bool eq_ev_trigger_ccc(ev_trigger_ccc_t const* m0, ev_trigger_ccc_t const* m1);

ev_trigger_ccc_t cp_ev_trigger_ccc(ev_trigger_ccc_t const* src);

#endif

