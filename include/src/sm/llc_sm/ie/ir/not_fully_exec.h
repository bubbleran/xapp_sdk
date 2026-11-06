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

#ifndef NOT_FULLY_EXEC_E2SM_LLC_MIR_H
#define NOT_FULLY_EXEC_E2SM_LLC_MIR_H 

#include "schd_log_chnl.h"
#include <stdbool.h>
#include <stdlib.h>

// From 8.3.27
// List of DL Grants

typedef struct{

  // List of Scheduled Logical Channels
  // [1,63]
  size_t sz_schd_log_chnl; 
  schd_log_chnl_t* schd_log_chnl;

} not_fully_exec_t;

not_fully_exec_t cp_not_fully_exec(not_fully_exec_t const* src);

void free_not_fully_exec(not_fully_exec_t* src);

bool eq_not_fully_exec(not_fully_exec_t const* m0, not_fully_exec_t const* m1);

#endif
