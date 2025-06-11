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



#ifndef E2_SETUP_RESPONSE_H
#define E2_SETUP_RESPONSE_H

#include "common/e2ap_global_ric_id.h"
#include "common/e2ap_node_component_config_update.h"
#include "common/e2ap_rejected_ran_function.h"
#include <stdbool.h>

typedef uint16_t accepted_ran_function_t;

typedef struct {
  global_ric_id_t id;

  accepted_ran_function_t* accepted;
  size_t len_acc;

  rejected_ran_function_t* rejected;
  size_t len_rej;
  e2_node_component_config_update_t* comp_conf_update_ack_list;
  size_t len_ccual;
} e2_setup_response_t;

bool eq_e2_setup_response(const e2_setup_response_t* m0, const e2_setup_response_t* m1);

#endif

