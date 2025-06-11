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



#ifndef E2_SETUP_FAILURE_H
#define E2_SETUP_FAILURE_H

#include "common/e2ap_cause.h"
#include "common/e2ap_criticality_diagnostics.h"
#include "common/e2ap_time_to_wait.h"
#include "common/transport_layer_info.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct {
  cause_t cause;
  e2ap_time_to_wait_e* time_to_wait_ms;       // optional
  criticality_diagnostics_t* crit_diag;   // optional
  transport_layer_information_t* tl_info; // optional
} e2_setup_failure_t;

bool eq_e2_setup_failure(const e2_setup_failure_t* m0, const e2_setup_failure_t* m1);

#endif

