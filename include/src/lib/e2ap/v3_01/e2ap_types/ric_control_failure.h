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



#ifndef RIC_CONTROL_FAILURE_H
#define RIC_CONTROL_FAILURE_H

#include "common/ric_gen_id.h"
#include "common/e2ap_cause.h" 
#include "common/e2ap_criticality_diagnostics.h"
#include "util/byte_array.h"

typedef struct {
  ric_gen_id_t ric_id;
  byte_array_t* call_process_id; // optional
  cause_t cause;
  byte_array_t* control_outcome; // optional
  criticality_diagnostics_t* crit; // optional
} ric_control_failure_t;

bool eq_control_failure(const ric_control_failure_t* m0, const ric_control_failure_t* m1);

ric_control_failure_t cp_ric_control_failure(ric_control_failure_t const* src);



#endif

