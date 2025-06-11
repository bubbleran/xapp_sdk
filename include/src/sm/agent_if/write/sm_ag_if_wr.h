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


#ifndef E2AP_SM_WR_IF_H
#define E2AP_SM_WR_IF_H 

#include "subscribe_timer.h"
#include "../../pdcp_sm/ie/pdcp_data_ie.h"
#include "../../rlc_sm/ie/rlc_data_ie.h"
#include "../../mac_sm/ie/mac_data_ie.h"
#include "../../slice_sm/ie/slice_data_ie.h"
#include "../../tc_sm/ie/tc_data_ie.h"
#include "../../gtp_sm/ie/gtp_data_ie.h"
#include "../../isac_sm/ie/isac_data_ie.h"
#include "../../kpm_sm/kpm_data_ie_wrapper.h"
#include "../../rc_sm/ie/rc_data_ie.h"
#include "../../ccc_sm/ie/ccc_data_ie.h"

//////////////////////
//////////////////////
// Control
//////////////////////
//////////////////////


typedef enum{
  MAC_CTRL_REQ_V0 = 0,
  RLC_CTRL_REQ_V0 = 1,
  PDCP_CTRL_REQ_V0 = 2,
  SLICE_CTRL_REQ_V0 = 3,
  TC_CTRL_REQ_V0 = 4,
  GTP_CTRL_REQ_V0 = 5,
  RAN_CONTROL_CTRL_V1_03 = 6,
  CCC_CTRL_REQ_V3_0 = 7,
  ISAC_CTRL_REQ_V0 = 8,
  SM_AGENT_IF_WRITE_CTRL_V0_END,
} sm_ag_if_ctrl_e;

typedef struct{
  sm_ag_if_ctrl_e type;
  union{
    mac_ctrl_req_data_t mac_ctrl;
    rlc_ctrl_req_data_t rlc_ctrl;
    pdcp_ctrl_req_data_t pdcp_req_ctrl;
    slice_ctrl_req_data_t slice_req_ctrl;
    tc_ctrl_req_data_t tc_req_ctrl;
    gtp_ctrl_req_data_t gtp_ctrl;
    rc_ctrl_req_data_t rc_ctrl;
    ccc_ctrl_req_data_t ccc_ctrl;
    isac_ctrl_req_data_t isac_ctrl;
  };
}  sm_ag_if_wr_ctrl_t;


//////////////////////
//////////////////////
// Subscription 
//////////////////////
//////////////////////

typedef enum{
  MAC_SUBS_V0 = 0, 
  RLC_SUBS_V0, 
  PDCP_SUBS_V0, 
  SLICE_SUBS_V0, 
  TC_SUBS_V0, 
  GTP_SUBS_V0, 
  KPM_SUBS_V3_0, 
  RAN_CTRL_SUBS_V1_03,
  CCC_SUBS_V3_0,
  ISAC_SUBS_V0, 
  SM_AGENT_IF_WRITE_SUBS_V0_END,
} sm_ag_if_subs_e;

typedef struct{ 
  uint32_t ric_req_id;
  rc_sub_data_t rc;
} wr_rc_sub_data_t;

typedef struct{
  uint32_t ric_req_id;
  ccc_sub_data_t ccc;
} wr_ccc_sub_data_t;

typedef struct{
  uint32_t ric_req_id;
  isac_sub_data_t isac;
} wr_isac_sub_data_t;

typedef struct{
  sm_ag_if_subs_e type;
  union{
    mac_sub_data_t mac;
    rlc_sub_data_t rlc;
    pdcp_sub_data_t pdcp;
    slice_sub_data_t slice;
    tc_sub_data_t tc;
    gtp_sub_data_t gtp;
    kpm_sub_data_t kpm;
    wr_rc_sub_data_t wr_rc;
    wr_ccc_sub_data_t wr_ccc;
    wr_isac_sub_data_t wr_isac;
  };
} sm_ag_if_wr_subs_t;


//////////////////////
//////////////////////
// Write interface 
//////////////////////
//////////////////////

typedef enum{
 CONTROL_SM_AG_IF_WR,
 SUBSCRIPTION_SM_AG_IF_WR,
 END_SM_AG_IF_WR,
} sm_ag_if_wr_e; 

typedef struct {
  sm_ag_if_wr_e type;
  union{
    sm_ag_if_wr_ctrl_t ctrl;
    sm_ag_if_wr_subs_t subs;
  }; 
} sm_ag_if_wr_t;

#endif
