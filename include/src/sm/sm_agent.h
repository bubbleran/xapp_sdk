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

#ifndef MIR_SM_AGENT_H
#define MIR_SM_AGENT_H

#include <stddef.h>
#include <stdint.h>

#include "sm_io.h"
#include "sm_proc_data.h"
#include "sm_alloc.h"

typedef struct sm_agent_s sm_agent_t;

typedef enum{
  PERIODIC_ON_INDICATION_EVENT,
  APERIODIC_ON_INDICATION_EVENT,

  END_ON_INDICATIONI_EVENT
} on_indication_ev_e;

typedef struct{
   on_indication_ev_e type;
  union{
    void* act_def; // used by periodic events
    void* ind_data; // used by aperiodic events
  };
} on_ind_t;

typedef struct{

  // @return granularity in ms or -1 if no periodic timer needed
  sm_ag_if_ans_subs_t (*on_subscription)(sm_agent_t const* sm, sm_subs_data_t const* data);

  exp_ind_data_t (*on_indication)(sm_agent_t const* sm, on_ind_t on_ind);

  sm_ctrl_out_data_t (*on_control)(sm_agent_t const* sm, sm_ctrl_req_data_t const* data);

  sm_e2_setup_data_t (*on_e2_setup)(sm_agent_t const* sm);

  sm_ric_service_update_data_t (*on_ric_service_update)(sm_agent_t const* sm);

#ifdef E2AP_V3
  sm_ric_query_out_data_t (*on_ric_query)(sm_agent_t const* sm, sm_ric_query_data_t const* data);

  void (*on_subscription_mod)(sm_agent_t const* sm,sm_sub_mod_data_t const*);
#endif

} sm_e2ap_procedures_agent_t;

// SM General Information
typedef struct{

  // Definition
  char const* (*def)(void);

  // ID
  uint16_t (*id)(void);

  // Revision
  uint16_t (*rev)(void);

  // OID
  char const* (*oid)(void);

} sm_e2ap_info_t;

typedef struct sm_agent_s {

  // 5 Procedures stored at the SO
  sm_e2ap_procedures_agent_t proc; 

  // Functions provided to the SM. Implemented in the RAN.
   sm_io_ag_sm_t io;

  // Free function
  void (*free_sm)(sm_agent_t* sm_agent);

  void (*free_act_def)(sm_agent_t* sm_agent, void* act_def);

  // Allocation functions
  sm_alloc_t alloc;

  // Shared Object handle
  void* handle;

  // SM Information function;
  sm_e2ap_info_t info;

} sm_agent_t;


#endif


