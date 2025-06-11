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


#ifndef SM_READ_INTERFACE_H
#define SM_READ_INTERFACE_H

// Interface between the SM and the agent/server. 
// The SM can call the functions here defined and implemented on the RAN/server to read data.

#include "../../mac_sm/ie/mac_data_ie.h"
#include "../../rlc_sm/ie/rlc_data_ie.h"
#include "../../pdcp_sm/ie/pdcp_data_ie.h"
#include "../../slice_sm/ie/slice_data_ie.h"
#include "../../tc_sm/ie/tc_data_ie.h"
#include "../../gtp_sm/ie/gtp_data_ie.h"
#include "../../isac_sm/ie/isac_data_ie.h"
#include "../../rc_sm/ie/rc_data_ie.h"
#include "../../ccc_sm/ie/ccc_data_ie.h"
#include "../../kpm_sm/kpm_data_ie_wrapper.h"

#include "../write/subscribe_timer.h"

////////////////////
// Indication Message 
////////////////////

// Do not change the order!
typedef enum{
  MAC_STATS_V0 = 0,
  RLC_STATS_V0,
  PDCP_STATS_V0,
  SLICE_STATS_V0,
  TC_STATS_V0,
  GTP_STATS_V0, 
  KPM_STATS_V3_0, 
  RAN_CTRL_STATS_V1_03,
  CCC_STATS_V3_0,
  ISAC_STATS_V0,

  SM_AGENT_IF_READ_V0_END,
} sm_ag_if_rd_ind_e;

typedef struct{
  kpm_ind_data_t ind;
  // Non-owning pointer
  kpm_act_def_t const* act_def;
} kpm_rd_ind_data_t;

typedef struct{
  rc_ind_data_t ind;
  // Non-owning pointer
  e2sm_rc_action_def_t const* act_def;
  uint32_t ric_id;
} rc_rd_ind_data_t;

typedef struct{
  ccc_ind_data_t ind;
  // Non-owning pointer
  e2sm_ccc_action_def_t const* act_def;
  uint32_t ric_id;
} ccc_rd_ind_data_t;

// ToDo: Change it for pointers, to break the dependencies
typedef struct{
  sm_ag_if_rd_ind_e type;
// Do not change the order!
  union {
    mac_ind_data_t mac;
    rlc_ind_data_t rlc;
    pdcp_ind_data_t pdcp;
    slice_ind_data_t slice;
    tc_ind_data_t tc;
    gtp_ind_data_t gtp;
    kpm_rd_ind_data_t kpm;
    rc_rd_ind_data_t rc;
    ccc_rd_ind_data_t ccc;
    isac_ind_data_t isac;
  };
} sm_ag_if_rd_ind_t;

void free_sm_ag_if_rd_ind(sm_ag_if_rd_ind_t* d);

sm_ag_if_rd_ind_t cp_sm_ag_if_rd_ind(sm_ag_if_rd_ind_t const* d);

////////////////////
// E2 Setup 
////////////////////

typedef enum{
  MAC_AGENT_IF_E2_SETUP_ANS_V0 = 0,
  RLC_AGENT_IF_E2_SETUP_ANS_V0,
  PDCP_AGENT_IF_E2_SETUP_ANS_V0,
  SLICE_AGENT_IF_E2_SETUP_ANS_V0,
  TC_AGENT_IF_E2_SETUP_ANS_V0,
  GTP_AGENT_IF_E2_SETUP_ANS_V0,
  KPM_V3_0_AGENT_IF_E2_SETUP_ANS_V0,
  RAN_CTRL_V1_3_AGENT_IF_E2_SETUP_ANS_V0,
  CCC_V3_0_AGENT_IF_E2_SETUP_ANS_V0,
  ISAC_AGENT_IF_E2_SETUP_ANS_V0,

  SM_AGENT_IF_E2_SETUP_ANS_V0_END,
} sm_ag_if_rd_e2setup_e;

typedef struct{
  sm_ag_if_rd_e2setup_e type;
  union {
    mac_e2_setup_data_t mac;
    rlc_e2_setup_data_t rlc;
    pdcp_e2_setup_data_t pdcp;
    slice_e2_setup_data_t slice;
    tc_e2_setup_data_t tc;
    gtp_e2_setup_data_t gtp;
    kpm_e2_setup_t kpm;
    rc_e2_setup_t rc;
    ccc_e2_setup_t ccc;
    isac_e2_setup_data_t isac;
  };
} sm_ag_if_rd_e2setup_t;

////////////////////
// RIC SERVICE UPDATE 
////////////////////

typedef enum{
  MAC_AGENT_IF_RIC_SERV_UPDATE_CTRL_ANS_V0,
  RLC_AGENT_IF_RIC_SERV_UPDATE_CTRL_ANS_V0,
  PDCP_AGENT_IF_RIC_SERV_UPDATE_CTRL_ANS_V0,
  SLICE_AGENT_IF_RIC_SERV_UPDATE_CTRL_ANS_V0,
  TC_AGENT_IF_RIC_SERV_UPDATE_CTRL_ANS_V0,
  GTP_AGENT_IF_RIC_SERV_UPDATE_CTRL_ANS_V0,
  KPM_V3_0_AGENT_IF_RIC_SERV_UPDATE_CTRL_ANS_V0,
  RAN_CTRL_V1_3_AGENT_IF_RIC_SERV_UPDATE_CTRL_ANS_V0,
  CCC_V3_0_AGENT_IF_RIC_SERV_UPDATE_CTRL_ANS_V0,
  ISAC_AGENT_IF_RIC_SERV_UPDATE_CTRL_ANS_V0,

  SM_AGENT_IF_RIC_SERV_UPDATE_CTRL_ANS_V0_END,
} sm_ag_if_rd_rsu_e;

typedef struct{
  sm_ag_if_rd_rsu_e type;
  union {
    mac_ric_service_update_t mac;
    rlc_ric_service_update_t rlc;
    pdcp_ric_service_update_t pdcp;
    slice_ric_service_update_t slice;
    tc_ric_service_update_t tc;
    gtp_ric_service_update_t gtp;
    kpm_ric_service_update_t kpm;
    rc_ric_service_update_t rc;
    ccc_ric_service_update_t ccc;
    isac_ric_service_update_t isac;
  };
} sm_ag_if_rd_rsu_t;

////////////////////////////////////////
// AGENT INTERFACE READ
////////////////////////////////////////

typedef enum {
  INDICATION_MSG_AGENT_IF_ANS_V0,
  E2_SETUP_AGENT_IF_ANS_V0,
  RIC_SERV_UPDATE_AGENT_IF_ANS_V0,
  
  END_AGENT_IF_ANS_V0,
} sm_ag_if_rd_e;

typedef struct {
  uint32_t ric_req_id;
  sm_ag_if_rd_e type;
  union{
    sm_ag_if_rd_ind_t ind;
    sm_ag_if_rd_e2setup_t e2ap;
    sm_ag_if_rd_rsu_t rsu;
  };
} sm_ag_if_rd_t;

void free_sm_ag_if_rd(sm_ag_if_rd_t* src);

sm_ag_if_rd_t cp_sm_ag_if_rd(sm_ag_if_rd_t const* src);

#endif

