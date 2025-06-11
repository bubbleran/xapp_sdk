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


#ifndef E42_SETUP_REQUEST_H
#define E42_SETUP_REQUEST_H 

#include "common/e2ap_ran_function.h"

typedef struct e42_setup_request {
  ran_function_t* ran_func_item;
  size_t len_rf;
} e42_setup_request_t;


e42_setup_request_t cp_e42_setup_request(const e42_setup_request_t* src);

void free_e42_setup_request(e42_setup_request_t* src);

bool eq_e42_setup_request(const e42_setup_request_t* m0, const e42_setup_request_t* m1);

#endif

