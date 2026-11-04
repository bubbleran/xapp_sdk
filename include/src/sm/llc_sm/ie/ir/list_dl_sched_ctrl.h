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

#ifndef LIST_DL_SCHE_CTRL_LLC_E2SM_MIR_H
#define LIST_DL_SCHE_CTRL_LLC_E2SM_MIR_H 

#include "dl_sched_ctrl.h"
#include <stdbool.h>

typedef struct{
  //[1,63]
  size_t sz_dl_sched_ctrl; 
  dl_sched_ctrl_t* dl_sched_ctrl;
} lst_dl_sched_ctrl_t;

lst_dl_sched_ctrl_t cp_lst_dl_sched_ctrl(lst_dl_sched_ctrl_t const* src);

void free_lst_dl_sched_ctrl(lst_dl_sched_ctrl_t* src);

bool eq_lst_dl_sched_ctrl(lst_dl_sched_ctrl_t const* m0, lst_dl_sched_ctrl_t const* m1);

#endif
