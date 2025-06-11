
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


#ifndef E42_SETUP_RESPONSE_H
#define E42_SETUP_RESPONSE_H 

#include "common/e2ap_node_component_config_add.h"
#include "e2_node_connected.h"

typedef struct e42_setup_response {
  uint16_t xapp_id;
  uint8_t len_e2_nodes_conn;
  e2_node_connected_t* nodes;
} e42_setup_response_t;

e42_setup_response_t cp_e42_setup_response(const e42_setup_response_t* src);

bool eq_e42_setup_response(const e42_setup_response_t* m0, const e42_setup_response_t* m1);

#endif

