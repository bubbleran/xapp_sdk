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


#ifndef E2AP_TIME_TO_WAIT_H
#define E2AP_TIME_TO_WAIT_H 

#include <stdbool.h>

typedef enum {
	TIMETOWAIT_V1S	= 0,
	TIMETOWAIT_V2S	= 1,
	TIMETOWAIT_V5S	= 2,
	TIMETOWAIT_V10S	= 3,
	TIMETOWAIT_V20S	= 4,
	TIMETOWAIT_V60S	= 5
	/*
	 * Enumeration is extensible
	 */
} e2ap_time_to_wait_e;

bool eq_time_to_wait(const e2ap_time_to_wait_e* m0, const e2ap_time_to_wait_e* m1);



#endif

