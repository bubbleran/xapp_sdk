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


#ifndef RLC_SERVICE_MODEL_ID_H
#define RLC_SERVICE_MODEL_ID_H 


/*
 * Service Model ID needed for the agent as well as for the ric to ensure that they match. 
 */

#include <stdint.h>

static
const uint16_t SM_RLC_ID = 143; 

__attribute__((unused)) static
const char* SM_RLC_STR = "RLC_STATS_V0"; 

static
const uint16_t SM_RLC_REV = 1; 

__attribute__((unused)) static
const char SM_RLC_SHORT_NAME[] = "E2SM-RLC";

//iso(0) identified-organization(0)
//dod(0) internet(0) private(0)
//enterprise(0) 53148 e2(0)
// version1 (1) e2sm(143) e2sm-RC-
// IEs (0)

__attribute__((unused)) static
const char SM_RLC_OID[] = "0.0.0.0.0.0.0.0.1.143.0"; 

__attribute__((unused)) static
const char SM_RLC_DESCRIPTION[] = "RLC Service Model";

#endif

