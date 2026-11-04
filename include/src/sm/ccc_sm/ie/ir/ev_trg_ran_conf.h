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

#ifndef EV_TRG_RAN_CONF_H
#define EV_TRG_RAN_CONF_H

#include "attribute.h"
#include "../../../../util/byte_array.h"

typedef struct{
  // RAN Configuration Structure Name
  // Mandatory
  // 9.3.7
  byte_array_t ran_conf_name;

  // List of Attributes
  // [0 - 66535]
  size_t sz_attribute;
  attribute_t* attribute;

} ev_trg_ran_conf_t;

void free_ev_trg_ran_conf(ev_trg_ran_conf_t* src);

bool eq_ev_trg_ran_conf(ev_trg_ran_conf_t const* m0, ev_trg_ran_conf_t const* m1);

ev_trg_ran_conf_t cp_ev_trg_ran_conf(ev_trg_ran_conf_t const* src);

#endif

