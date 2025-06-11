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

#ifndef E2AP_NODE_COMPONENT_CONFIG_ADD_H
#define E2AP_NODE_COMPONENT_CONFIG_ADD_H

#include "e2ap_node_comp_interface_type.h"
#include "e2ap_node_comp_id.h"
#include "e2ap_node_comp_conf.h"

// From 9.1.2.2 E2 SETUP REQUEST
typedef struct{
  // Mandatory
  // 9.2.26
  e2ap_node_comp_interface_type_e e2_node_comp_interface_type;

  // Bug in the standard!!! Optional in the standard, Mandatory in asn specs
  // Let's take the asn definition;
  // 9.2.32
  e2ap_node_comp_id_t e2_node_comp_id;

  // Mandatory
  // 9.2.27
  e2ap_node_comp_conf_t e2_node_comp_conf;

} e2ap_node_component_config_add_t;

void free_e2ap_node_component_config_add(e2ap_node_component_config_add_t* src);

e2ap_node_component_config_add_t cp_e2ap_node_component_config_add(e2ap_node_component_config_add_t const* src);

bool eq_e2ap_node_component_config_add(e2ap_node_component_config_add_t const* m0, e2ap_node_component_config_add_t const* m1);

typedef struct{
  e2ap_node_component_config_add_t* cca;
  size_t len_cca;
} arr_node_component_config_add_t ;

#endif

