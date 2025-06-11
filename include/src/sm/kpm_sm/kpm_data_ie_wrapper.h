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


#ifndef KPM_DATA_IE_WRAPPER_H
#define KPM_DATA_IE_WRAPPER_H 

#ifdef KPM_V2_01
#include "kpm_sm_v02.01/ie/kpm_data_ie.h"
#elif defined(KPM_V2_03)
#include "kpm_sm_v02.03/ie/kpm_data_ie.h"
#elif defined(KPM_V3_00)
#include "kpm_sm_v03.00/ie/kpm_data_ie.h"
#else
_Static_assert(0!=0, "Unknown KPM version");
#endif

#endif
