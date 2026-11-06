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

#ifndef RAN_FUNC_DEF_CONTROL_LLC_E2SM_MIR_H
#define RAN_FUNC_DEF_CONTROL_LLC_E2SM_MIR_H 

#include "seq_ctrl_style_llc.h"

#include <stdlib.h>


typedef struct {
  // Sequence of CONTROL styles
  // [1 - 63]
  size_t sz_seq_ctrl_style;
  seq_ctrl_style_llc_t* seq_ctrl_style;

} ran_func_def_ctrl_llc_t;

#endif
