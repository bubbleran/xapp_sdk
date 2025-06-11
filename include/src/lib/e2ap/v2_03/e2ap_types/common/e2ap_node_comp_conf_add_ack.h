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

#ifndef E2AP_NODE_COMP_CONF_ADD_ACK_MIR_H
#define E2AP_NODE_COMP_CONF_ADD_ACK_MIR_H 

#include "e2ap_cause.h"
#include <stdbool.h>

typedef enum{
  SUCCESS_E2AP_NODE_COMP_CONF_ACK = 0,
  FAILURE_E2AP_NODE_COMP_CONF_ACK,
} outcome_e2ap_node_comp_conf_ack_e;


// 9.2.28
// Mandatory
typedef struct {

  // Mandatory
  // Outcome
  outcome_e2ap_node_comp_conf_ack_e outcome;

  // Optional
  // 9.2.1
  cause_t* cause;

} e2ap_node_comp_conf_ack_t;

void free_e2ap_node_comp_conf_ack( e2ap_node_comp_conf_ack_t* src);

e2ap_node_comp_conf_ack_t cp_e2ap_node_comp_conf_ack( e2ap_node_comp_conf_ack_t const* src);

bool eq_e2ap_node_comp_conf_ack( e2ap_node_comp_conf_ack_t const* m0, e2ap_node_comp_conf_ack_t const* m1);

#endif
