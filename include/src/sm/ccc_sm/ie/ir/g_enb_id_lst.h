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

#ifndef G_ENB_ID_LST_H
#define G_ENB_ID_LST_H

#include <stdlib.h>
#include <stdbool.h>

// Conflict type between json schema and ie
// Following CCC json schema type
typedef struct {
  size_t sz_g_enb_id_lst;
  char** g_enb_id_lst;
} g_enb_id_lst_t;

void free_g_enb_id_lst(g_enb_id_lst_t* src);

bool eq_g_enb_id_lst(g_enb_id_lst_t const* m0, g_enb_id_lst_t const* m1);

g_enb_id_lst_t cp_g_enb_id_lst(g_enb_id_lst_t const* src);

#endif

