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


#ifndef E2AP_CRITICALITY_DIAGNOSTICS_H
#define E2AP_CRITICALITY_DIAGNOSTICS_H

#include <stddef.h>
#include <stdint.h>

#include "ric_gen_id.h"
#include "e2ap_criticality.h"
#include "ric_gen_id.h"
#include "e2ap_ie_criticality_diagnostics.h"


typedef enum {
  INITIATING_MESSAGE,
  SUCCESSFUL_OUTCOME,
  UNSUCCESSFUL_OUTCOME
} triggering_message_e;


typedef struct {
  uint8_t* procedure_code; //optional
  triggering_message_e* trig_msg; // optional
  criticality_e* proc_crit; // optional
  ric_gen_id_t* req_id; // optional
  ie_criticality_diagnostics_t* ie;
  size_t len_ie;
} criticality_diagnostics_t;

bool eq_criticality_diagnostics(const criticality_diagnostics_t* m0, const criticality_diagnostics_t* m1);

#endif

