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




#ifndef E42_RIC_SUBSCRIPTION_REQUEST_H
#define E42_RIC_SUBSCRIPTION_REQUEST_H 

#include "common/e2ap_global_node_id.h"
#include "ric_subscription_request.h"

#include <stdbool.h>

typedef struct{
 uint16_t xapp_id;
 global_e2_node_id_t id;
 ric_subscription_request_t sr;
} e42_ric_subscription_request_t;

void free_e42_ric_subscription_request(e42_ric_subscription_request_t* sr);

bool eq_e42_ric_subscritption_request(const e42_ric_subscription_request_t* m0, const e42_ric_subscription_request_t* m1);

#endif

