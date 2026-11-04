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

#ifndef E42_UPDATE_E2_NODE_H
#define E42_UPDATE_E2_NODE_H

#include "e2_node_connected.h"

typedef struct e42_update_e2_node {
  uint16_t xapp_id;
  uint8_t len_e2_nodes_conn;
  e2_node_connected_t* nodes;
} e42_update_e2_node_t;

e42_update_e2_node_t cp_e42_update_e2_node(const e42_update_e2_node_t* src);

bool eq_e42_update_e2_node(const e42_update_e2_node_t* m0, const e42_update_e2_node_t* m1);

#endif

