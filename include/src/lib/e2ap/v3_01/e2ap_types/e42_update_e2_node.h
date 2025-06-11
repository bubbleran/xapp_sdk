
/*
 * Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The OpenAirInterface Software Alliance licenses this file to You under
 * the OAI Public License, Version 1.1  (the "License"); you may not use this file
 * except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.openairinterface.org/?page_id=698
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------------------
 * For more information about the OpenAirInterface (OAI) Software Alliance:
 *      contact@openairinterface.org
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

