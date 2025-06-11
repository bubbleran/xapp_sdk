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


#ifndef E2AP_GLOBAL_NODE_ID_H
#define E2AP_GLOBAL_NODE_ID_H

#ifdef __cplusplus
extern "C" {
#endif

#include "e2ap_plmn.h"
#include "../../../../../util/e2ap_ngran_types.h"
#include "../../../../3gpp/ie/e2ap_gnb_id.h"

#include <stdbool.h>
#include <stdint.h>


typedef struct global_e2_node_id {
  e2ap_ngran_node_t type;
  e2ap_plmn_t plmn;
  e2ap_gnb_id_t nb_id;
  uint64_t *cu_du_id;
} global_e2_node_id_t;

global_e2_node_id_t cp_global_e2_node_id(global_e2_node_id_t const* src);

void free_global_e2_node_id(global_e2_node_id_t* src);

void free_global_e2_node_id_wrapper(void* src);

bool eq_global_e2_node_id(const global_e2_node_id_t* m0, const global_e2_node_id_t* m1); 

bool eq_global_e2_node_id(const global_e2_node_id_t* m0, const global_e2_node_id_t* m1);
 
bool eq_global_e2_node_id_wrapper(const void* m0_v, const void* m1_v );
 
int cmp_global_e2_node_id(const global_e2_node_id_t* m0, const global_e2_node_id_t* m1);
 
int cmp_global_e2_node_id_wrapper(const void* m0_v, const void* m1_v);

#ifdef __cplusplus
}
#endif

#endif

