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

#ifndef SM_INPUT_OUTPUT_H
#define SM_INPUT_OUTPUT_H

#include "agent_if/read/sm_ag_if_rd.h"
#include "agent_if/write/sm_ag_if_wr.h"
#include "agent_if/ans/sm_ag_if_ans.h"
#include "../util/e2ap_ngran_types.h"

// Read
typedef bool (*read_ind_fp)(void* data);
typedef void (*read_e2_setup_fp)(void* data);
typedef void (*read_rsu_fp)(void* data);

// Write
typedef sm_ag_if_ans_t (*write_ctrl_fp)(void const* data);
typedef sm_ag_if_ans_t (*write_subs_fp)(void const* data);


// The SM agent uses these functions to communicate with the RAN and with the server.
typedef struct{
 // void (*read)(sm_ag_if_rd_t* data);
 // sm_ag_if_ans_t (*write)(sm_ag_if_wr_t const* data);

  // Read per SM
  read_ind_fp read_ind_tbl[SM_AGENT_IF_READ_V0_END];
  read_e2_setup_fp read_setup_tbl[SM_AGENT_IF_E2_SETUP_ANS_V0_END];
  read_rsu_fp read_rsu_tbl; //[0];

#if defined(E2AP_V2) || defined (E2AP_V3)
  // Read RAN 
  void (*read_setup_ran)(void* data, const e2ap_ngran_node_t node_type);
#endif

  // Write SM
  write_ctrl_fp write_ctrl_tbl[SM_AGENT_IF_WRITE_CTRL_V0_END];
  write_subs_fp write_subs_tbl[SM_AGENT_IF_WRITE_SUBS_V0_END];
} sm_io_ag_ran_t;

typedef struct{
  // Read
  read_ind_fp read_ind;
  read_e2_setup_fp read_setup;
  read_rsu_fp read_rsu;

  // Write
  write_ctrl_fp write_ctrl;
  write_subs_fp write_subs;

} sm_io_ag_sm_t;

#endif

