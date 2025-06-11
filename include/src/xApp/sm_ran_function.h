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

#ifndef SM_RAN_FUNCTION_MIR_H
#define SM_RAN_FUNCTION_MIR_H

#include <stdint.h>
#include "sm_ran_function_def.h"

typedef struct{
  sm_ran_function_def_t defn;
  uint16_t id;
  uint16_t rev;
#ifdef E2AP_V1
  byte_array_t* oid; // optional
#elif defined(E2AP_V2) || defined(E2AP_V3) 
  byte_array_t oid; 
#endif
} sm_ran_function_t;

void free_sm_ran_function(sm_ran_function_t* src);

sm_ran_function_t cp_sm_ran_function(sm_ran_function_t const* src);

bool eq_sm_ran_function(sm_ran_function_t const* m0, sm_ran_function_t const* m1);

#endif

