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


#ifndef PLMN_IDENTITY_H
#define PLMN_IDENTITY_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stdbool.h>
#include <stdint.h>



typedef struct {
  uint16_t mcc;
  uint16_t mnc;
  uint8_t mnc_digit_len;
} e2sm_plmn_t;

void free_e2sm_plmn( e2sm_plmn_t* src); // 6.2.3.1

bool eq_e2sm_plmn(const e2sm_plmn_t* m0, const e2sm_plmn_t* m1);

e2sm_plmn_t cp_e2sm_plmn(const  e2sm_plmn_t* src);

int cmp_e2sm_plmn(const  e2sm_plmn_t* m0, const  e2sm_plmn_t* m1);

#ifdef __cplusplus
}
#endif


#endif

// done
