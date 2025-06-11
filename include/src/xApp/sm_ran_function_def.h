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

#ifndef SM_RAN_FUNCTION_DEF_MIR_H
#define SM_RAN_FUNCTION_DEF_MIR_H

#include <stdbool.h>

#include "../sm/mac_sm/ie/mac_data_ie.h"
#include "../sm/rlc_sm/ie/rlc_data_ie.h"
#include "../sm/pdcp_sm/ie/pdcp_data_ie.h"
#include "../sm/kpm_sm/kpm_data_ie_wrapper.h"
#include "../sm/rc_sm/ie/rc_data_ie.h"
#include "../sm/gtp_sm/ie/gtp_data_ie.h"
#include "../sm/slice_sm/ie/slice_data_ie.h"
#include "../sm/tc_sm/ie/tc_data_ie.h"
#include "../sm/ccc_sm/ie/ccc_data_ie.h"
#include "../sm/isac_sm/ie/isac_data_ie.h"

typedef enum {
  KPM_RAN_FUNC_DEF_E,
  RC_RAN_FUNC_DEF_E,
  MAC_RAN_FUNC_DEF_E,
  RLC_RAN_FUNC_DEF_E,
  PDCP_RAN_FUNC_DEF_E,
  GTP_RAN_FUNC_DEF_E,
  SLICE_RAN_FUNC_DEF_E,
  TC_RAN_FUNC_DEF_E,
  CCC_RAN_FUNC_DEF_E,
  ISAC_RAN_FUNC_DEF_E,
} ran_func_def_e;

typedef struct{ 
 ran_func_def_e type;
 union {
   kpm_ran_function_def_t kpm; 
   e2sm_rc_func_def_t rc;
   mac_func_def_t mac;
   rlc_func_def_t rlc;
   pdcp_func_def_t pdcp;
   gtp_func_def_t gtp;
   slice_func_def_t slice;
   tc_func_def_t tc;
   e2sm_ccc_func_def_t ccc;
   isac_func_def_t isac;
 };
} sm_ran_function_def_t;

void free_sm_ran_function_def(sm_ran_function_def_t* src);

sm_ran_function_def_t cp_sm_ran_function_def(sm_ran_function_def_t const* src);

bool eq_sm_ran_function_def(sm_ran_function_def_t const* m0,sm_ran_function_def_t const* m1);

#endif
