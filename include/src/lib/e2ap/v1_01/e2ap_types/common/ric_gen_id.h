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


#ifndef RIC_GEN_ID_H
#define RIC_GEN_ID_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
  uint32_t ric_req_id; // not uint16_t to avoid padding and thus, be able to use memcmp
  uint16_t ric_inst_id;
  uint16_t ran_func_id;
} ric_gen_id_t;

bool eq_ric_gen_id(const ric_gen_id_t* m0, const  ric_gen_id_t* m1);

int cmp_ric_gen_id(const ric_gen_id_t* m0, const  ric_gen_id_t* m1);

#endif

