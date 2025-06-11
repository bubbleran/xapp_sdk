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

#ifndef SUBSCRIBE_TIMER_EUR_H
#define SUBSCRIBE_TIMER_EUR_H

#include "../../kpm_sm/kpm_data_ie_wrapper.h"
#include "../../ccc_sm/ie/ccc_data_ie.h"
#include <stdint.h>
#include <stdlib.h>

typedef enum{
  KPM_V3_0_SUB_DATA_ENUM,
  RAN_CONTROL_V1_3_SUB_DATA_ENUM,
  CCC_V3_0_SUB_DATA_ENUM,
  NONE_SUB_DATA_ENUM,

  END_SUB_DATA_ENUM,
} sub_data_e;

typedef struct{
  int64_t ms;
  sub_data_e type;
  // Number of elements.
  // Just one is supported
  size_t sz;
  void* act_def; // e.g., kpm_act_def_t. e2sm_ccc_action_def_t
} subscribe_timer_t;

void free_subscribe_timer(subscribe_timer_t* src);

#endif

