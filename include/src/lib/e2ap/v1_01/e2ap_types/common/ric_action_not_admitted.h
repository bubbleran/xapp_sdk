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


#ifndef RIC_ACTION_NOT_ADMITTED
#define  RIC_ACTION_NOT_ADMITTED

#include <stdbool.h>
#include <stdint.h>
#include "e2ap_cause.h"

typedef struct ric_action_not_admitted {
  uint8_t ric_act_id;
  cause_t cause;
} ric_action_not_admitted_t;

bool eq_ric_action_not_admitted(const   ric_action_not_admitted_t* m0, const   ric_action_not_admitted_t* m1);

ric_action_not_admitted_t cp_ric_action_not_admitted(ric_action_not_admitted_t* src);

#endif

