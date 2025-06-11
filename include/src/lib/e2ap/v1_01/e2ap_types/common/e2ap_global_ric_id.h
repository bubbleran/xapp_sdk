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


#ifndef E2AP_GLOBAL_RIC_H
#define E2AP_GLOBAL_RIC_H

#include "e2ap_plmn.h"
#include <stdint.h>

typedef struct{
  e2ap_plmn_t plmn;

  union{
    uint32_t double_word;
    uint8_t bytes[4];  
  } near_ric_id;

} global_ric_id_t;


bool eq_global_ric_id(const global_ric_id_t* m0, const global_ric_id_t* m1);


#endif

