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
#ifndef KPM_SERVICE_MODEL_ID_H
#define KPM_SERVICE_MODEL_ID_H 

#include <stdint.h>
/*
 * Service Model ID (SM_KPM_ID) is needed for the agent as well as for the ric to ensure that they match. 
 * ID number chosen checking the already used one and adding one number. cfr. the other SMs in this package.
 */
static const uint16_t SM_KPM_ID = 2; 

static const uint16_t SM_KPM_REV = 3; 

// O-RAN.WG3.E2SM-KPM-R003-v03.00, $7.2
#define SM_KPM_STR "ORAN-E2SM-KPM"

#define SM_KPM_DESCRIPTION "KPM Monitor"

// iso(1) identified-organization(3) dod(6) internet(1) private(4) enterprise(1) oran(53148) e2(1) version3(3) e2sm(2) e2sm-KPMMON-IEs (2)
// FYI, ORAN identification `O-RAN Alliance e.V.`, is associated to number 53148.
#define SM_KPM_OID "1.3.6.1.4.1.53148.1.3.2.2"

#endif
