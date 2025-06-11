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

#ifndef E2AP_NODE_COMP_CONF_MIR_H
#define E2AP_NODE_COMP_CONF_MIR_H 

#include "../../../../../util/byte_array.h"
#include <stdbool.h>

// 9.2.27
// Contents depend on
// component type and used to
// carry new or updated
// component configuration. 

typedef struct{
  byte_array_t request; 
  byte_array_t response;  
} e2ap_node_comp_conf_t ;

void free_e2ap_node_comp_conf(e2ap_node_comp_conf_t* src);

bool eq_e2ap_node_comp_conf(e2ap_node_comp_conf_t const* m0, e2ap_node_comp_conf_t const* m1);

e2ap_node_comp_conf_t cp_e2ap_node_comp_conf(e2ap_node_comp_conf_t const* src);

#endif

