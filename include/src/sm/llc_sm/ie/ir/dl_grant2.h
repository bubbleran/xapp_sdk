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

#ifndef DL_GRANT2_E2SM_LLC_MIR_H
#define DL_GRANT2_E2SM_LLC_MIR_H 

#include "not_fully_exec.h"
#include <stdbool.h>

typedef enum{
  FULLY_EXECUTED_EXECUTION_LEVEL_E,
  NOT_FULLY_EXECUTED_EXECUTION_LEVEL_E,
  END_FULLY_EXECUTED_EXECUTION_LEVEL_E,
} execution_level_e ;

// From 8.3.27
// List of DL Grants
typedef struct{

  // Grant ID 
  // Mandatory
  uint32_t grant_id;

  execution_level_e execution_level; 

  // Only applies when exec_level NOT_FULLY_EXECUTED_EXECUTION_LEVEL_E !!!!
  union{
    not_fully_exec_t not_fully_exec;
  };

} dl_grant2_t;

dl_grant2_t cp_dl_grant2(dl_grant2_t const* src);

void free_dl_grant2(dl_grant2_t* src); 

bool eq_dl_grant2(dl_grant2_t const* m0, dl_grant2_t const* m1); 

#endif
