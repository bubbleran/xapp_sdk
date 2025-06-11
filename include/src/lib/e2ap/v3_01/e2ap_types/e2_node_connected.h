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


#ifndef E2_NODE_CONNECTED
#define E2_NODE_CONNECTED 

#include "common/e2ap_global_node_id.h"
#include "common/e2ap_node_component_config_add.h"
#include "common/e2ap_ran_function.h"

#include <stdbool.h>

typedef struct{
  global_e2_node_id_t id;

  // [1-256]
  uint8_t len_cca; // one less than in the standard, but should be OK
  e2ap_node_component_config_add_t* cca;

  size_t len_rf;
  ran_function_t* ack_rf;
} e2_node_connected_t;

e2_node_connected_t cp_e2_node_connected(const e2_node_connected_t* src);

void free_e2_node_connected(e2_node_connected_t* src);

bool eq_e2_node_connected(const e2_node_connected_t* m0, const e2_node_connected_t* m1);

#endif

