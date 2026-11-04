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

#ifndef DL_HARQ_STATS_E2SM_LLC_MIR_H
#define DL_HARQ_STATS_E2SM_LLC_MIR_H 

#include "dl_harq_ue_id.h"
#include <stdbool.h>

//8.3.23
typedef struct{
  // DL HARQ UE Ide
  // [1, 65535]
  size_t sz_dl_harq_ue_id;
  dl_harq_ue_id_t* dl_harq_ue_id;
} dl_harq_stats_t;

dl_harq_stats_t cp_dl_harq_stats(dl_harq_stats_t const* src); 

void free_dl_harq_stats(dl_harq_stats_t* src); 

bool eq_dl_harq_stats(dl_harq_stats_t const* m0, dl_harq_stats_t const* m1); 

#endif
