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

#ifndef E2SM_CCC_EV_TRG_FRMT_2
#define E2SM_CCC_EV_TRG_FRMT_2

#include <stdbool.h>

#include "../../../../util/byte_array.h"
#include "../../../../lib/sm/ie/cell_global_id.h"
#include "attribute.h"
#include "ev_trg_ran_conf.h"

typedef struct{
  // Cell global ID
  // Optional
  // 9.3.6
  cell_global_id_t cell_global_id;

  // List of Cell-level RAN Configuration Structures
  // [1 - 1024]
  size_t sz_ev_trg_ran_conf;
  ev_trg_ran_conf_t * ev_trg_ran_conf;

} ev_trg_cell_t;

// 9.2.1.1.2
typedef struct {
  // List of Cell-level Configuration Structures
  // [1 - 1024]
  size_t sz_ev_trg_cell;
  ev_trg_cell_t* ev_trg_cell;
} e2sm_ccc_ev_trg_frmt_2_t;

void free_e2sm_ccc_ev_trg_frmt_2(e2sm_ccc_ev_trg_frmt_2_t const* src);

bool eq_e2sm_ccc_ev_trg_frmt_2(e2sm_ccc_ev_trg_frmt_2_t const* m0, e2sm_ccc_ev_trg_frmt_2_t const* m1);

e2sm_ccc_ev_trg_frmt_2_t cp_e2sm_ccc_ev_trg_frmt_2(e2sm_ccc_ev_trg_frmt_2_t const* src);

#endif

