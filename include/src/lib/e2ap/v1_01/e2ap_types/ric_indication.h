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

#ifndef RIC_INDICATION_H
#define RIC_INDICATION_H

#include "common/ric_gen_id.h"
#include "util/byte_array.h"
#include <stdint.h> 

typedef enum {
  RIC_IND_REPORT = 0,
  RIC_IND_INSERT =1,
} ric_indication_type_e;

typedef struct ric_indication {
  ric_gen_id_t ric_id;
  uint8_t action_id;
  uint16_t* sn; // optional
  ric_indication_type_e type;
  byte_array_t hdr;
  byte_array_t msg;
  byte_array_t* call_process_id; // optional
} ric_indication_t;

bool eq_ric_indication(const ric_indication_t* m0, const ric_indication_t* m1);

ric_indication_t mv_ric_indication(ric_indication_t* ind);

#endif

