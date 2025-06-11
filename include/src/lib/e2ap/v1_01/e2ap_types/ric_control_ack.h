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



#ifndef RIC_CONTROL_ACK_H
#define RIC_CONTROL_ACK_H

#include "common/ric_gen_id.h"
#include "util/byte_array.h"

typedef enum {
  RIC_CONTROL_STATUS_SUCCESS = 0,
  RIC_CONTROL_STATUS_REJECTED = 1,
  RIC_CONTROL_STATUS_FAILED = 2, 
} ric_control_status_t;

typedef struct {
  ric_gen_id_t ric_id;
  byte_array_t* call_process_id; // optional
  ric_control_status_t status;
  byte_array_t* control_outcome; // optional
} ric_control_acknowledge_t;

bool eq_ric_control_ack_req(const ric_control_acknowledge_t* m0, const ric_control_acknowledge_t* m1);

#endif

