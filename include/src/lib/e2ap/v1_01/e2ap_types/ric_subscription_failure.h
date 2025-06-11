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


#ifndef RIC_SUBSCRIPTION_FAILURE_H
#define RIC_SUBSCRIPTION_FAILURE_H

#include <stddef.h>

#include "common/ric_gen_id.h"
#include "common/ric_action_not_admitted.h"
#include "common/e2ap_criticality_diagnostics.h"


typedef struct {
  ric_gen_id_t ric_id;
  ric_action_not_admitted_t* not_admitted;
  size_t len_na;
  criticality_diagnostics_t* crit_diag; // optional
} ric_subscription_failure_t;


bool eq_ric_subscritption_failure(const ric_subscription_failure_t* m0, const ric_subscription_failure_t* m1);

#endif
