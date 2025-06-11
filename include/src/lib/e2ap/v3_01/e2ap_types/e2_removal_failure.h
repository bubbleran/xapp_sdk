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

#ifndef E2_REMOVAL_FAILURE_V2_MIR_H
#define E2_REMOVAL_FAILURE_V2_MIR_H 

#include <stdint.h>
#include "common/e2ap_cause.h"
#include "common/e2ap_criticality_diagnostics.h"

typedef struct{

  // Transaction ID
  // 9.2.33
  // Mandatory
  uint8_t trans_id;

  //Cause
  //9.2.1
  // Mandatory
  cause_t cause;

  //Criticality Diagnostics
  //9.2.2
  //Optional
  criticality_diagnostics_t* crit;

} e2_removal_failure_t;

#endif
