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


#ifndef E2AP_RAN_FUNCTION_H
#define E2AP_RAN_FUNCTION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../../../../../util/byte_array.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct ran_function {
  byte_array_t defn;
  uint16_t id;
  uint16_t rev;
  byte_array_t* oid; // optional
} ran_function_t;

ran_function_t cp_ran_function(const ran_function_t* src);

void free_ran_function_wrapper(void* a);

void free_ran_function(ran_function_t* src);

bool eq_ran_function(const ran_function_t* m0, const ran_function_t* m1);

bool eq_ran_function_wrapper(void const* a_v, void const* b_v);

int cmp_ran_function(const ran_function_t* m0, const ran_function_t* m1);

#ifdef __cplusplus
}
#endif

#endif
