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



#ifndef PDCP_DATA_INFORMATION_ELEMENTS_H
#define PDCP_DATA_INFORMATION_ELEMENTS_H

#ifdef __cplusplus
extern "C" {
#endif


/*
 * 9 Information Elements (IE) , RIC Event Trigger Definition, RIC Action Definition, RIC Indication Header, RIC Indication Message, RIC Call Process ID, RIC Control Header, RIC Control Message, RIC Control Outcome and RAN Function Definition defined by ORAN-WG3.E2SM-v01.00.00 at Section 5
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


//////////////////////////////////////
// RIC Event Trigger Definition
/////////////////////////////////////

typedef struct {
  uint32_t ms;
} pdcp_event_trigger_t;

void free_pdcp_event_trigger(pdcp_event_trigger_t* src); 

pdcp_event_trigger_t cp_pdcp_event_trigger( pdcp_event_trigger_t* src);

bool eq_pdcp_event_trigger(pdcp_event_trigger_t* m0, pdcp_event_trigger_t* m1);

//////////////////////////////////////
// RIC Action Definition 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;  
} pdcp_action_def_t;

void free_pdcp_action_def(pdcp_action_def_t* src); 

pdcp_action_def_t cp_pdcp_action_def(pdcp_action_def_t* src);

bool eq_pdcp_action_def(pdcp_event_trigger_t* m0,  pdcp_event_trigger_t* m1);

//////////////////////////////////////
// RIC Indication Header 
/////////////////////////////////////

typedef struct{
  uint32_t dummy;  
} pdcp_ind_hdr_t;

void free_pdcp_ind_hdr(pdcp_ind_hdr_t* src); 

pdcp_ind_hdr_t cp_pdcp_ind_hdr(pdcp_ind_hdr_t const* src);

bool eq_pdcp_ind_hdr(pdcp_ind_hdr_t* m0, pdcp_ind_hdr_t* m1);

//////////////////////////////////////
// RIC Indication Message 
/////////////////////////////////////

typedef struct{
  uint32_t txpdu_pkts;     /* aggregated number of tx packets */
  uint32_t txpdu_bytes;    /* aggregated bytes of tx packets */
  uint32_t txpdu_sn;       /* current sequence number of last tx packet (or TX_NEXT) */
  uint32_t rxpdu_pkts;     /* aggregated number of rx packets */
  uint32_t rxpdu_bytes;    /* aggregated bytes of rx packets */
  uint32_t rxpdu_sn;       /* current sequence number of last rx packet (or  RX_NEXT) */
  uint32_t rxpdu_oo_pkts;       /* aggregated number of out-of-order rx pkts  (or RX_REORD) */
  uint32_t rxpdu_oo_bytes; /* aggregated amount of out-of-order rx bytes */
  uint32_t rxpdu_dd_pkts;  /* aggregated number of duplicated discarded packets */
  uint32_t rxpdu_dd_bytes; /* aggregated amount of discarded packets' bytes */
  uint32_t rxpdu_ro_count; /* this state variable indicates the COUNT value */
  uint32_t txsdu_pkts;     /* number of SDUs delivered */
  uint32_t txsdu_bytes;    /* number of bytes of SDUs delivered */
  uint32_t rxsdu_pkts;     /* number of SDUs received */
  uint32_t rxsdu_bytes;    /* number of bytes of SDUs received */
  uint32_t rnti;
  uint8_t  mode;               /* 0: PDCP AM, 1: PDCP UM, 2: PDCP TM */
  uint8_t  rbid;
} pdcp_radio_bearer_stats_t;

typedef struct {
  uint32_t len;
  pdcp_radio_bearer_stats_t* rb; 
  int64_t tstamp;

//  uint16_t frame;
//  uint8_t slot;
} pdcp_ind_msg_t;

void free_pdcp_ind_msg(pdcp_ind_msg_t* msg);

pdcp_ind_msg_t cp_pdcp_ind_msg(pdcp_ind_msg_t const* src);

bool eq_pdcp_ind_msg(pdcp_ind_msg_t* m0, pdcp_ind_msg_t* m1); 

//////////////////////////////////////
// RIC Call Process ID 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;
} pdcp_call_proc_id_t;

void free_pdcp_call_proc_id( pdcp_call_proc_id_t* src); 

pdcp_call_proc_id_t cp_pdcp_call_proc_id( pdcp_call_proc_id_t* src);

bool eq_pdcp_call_proc_id(pdcp_call_proc_id_t* m0, pdcp_call_proc_id_t* m1);


//////////////////////////////////////
// RIC Control Header 
/////////////////////////////////////


typedef struct {
  uint32_t dummy;
} pdcp_ctrl_hdr_t;

void free_pdcp_ctrl_hdr( pdcp_ctrl_hdr_t* src); 

pdcp_ctrl_hdr_t cp_pdcp_ctrl_hdr(pdcp_ctrl_hdr_t* src);

bool eq_pdcp_ctrl_hdr(pdcp_ctrl_hdr_t* m0, pdcp_ctrl_hdr_t* m1);

//////////////////////////////////////
// RIC Control Message 
/////////////////////////////////////

typedef struct {
  uint32_t action;
} pdcp_ctrl_msg_t;

void free_pdcp_ctrl_msg( pdcp_ctrl_msg_t* src); 

pdcp_ctrl_msg_t cp_pdcp_ctrl_msg(pdcp_ctrl_msg_t* src);

bool eq_pdcp_ctrl_msg(pdcp_ctrl_msg_t* m0, pdcp_ctrl_msg_t* m1);

//////////////////////////////////////
// RIC Control Outcome 
/////////////////////////////////////

typedef enum{
  PDCP_CTRL_OUT_OK,


  PDCP_CTRL_OUT_END
} pdcp_ctrl_out_e;

typedef struct {
  pdcp_ctrl_out_e ans;  
} pdcp_ctrl_out_t;

void free_pdcp_ctrl_out(pdcp_ctrl_out_t* src); 

pdcp_ctrl_out_t cp_pdcp_ctrl_out(pdcp_ctrl_out_t* src);

bool eq_pdcp_ctrl_out(pdcp_ctrl_out_t* m0, pdcp_ctrl_out_t* m1);


//////////////////////////////////////
// RAN Function Definition 
/////////////////////////////////////

typedef struct {
  uint8_t* buf;
  size_t len;
} pdcp_func_def_t;

void free_pdcp_func_def(pdcp_func_def_t* src); 

pdcp_func_def_t cp_pdcp_func_def(pdcp_func_def_t const* src);

bool eq_pdcp_func_def(pdcp_func_def_t const* m0, pdcp_func_def_t const* m1);

/////////////////////////////////////////////////
//////////////////////////////////////////////////
/////////////////////////////////////////////////


/*
 * O-RAN defined 5 Procedures: RIC Subscription, RIC Indication, RIC Control, E2 Setup and RIC Service Update 
 * */


///////////////
/// RIC Subscription
///////////////

typedef struct{
  pdcp_event_trigger_t et; 
  pdcp_action_def_t* ad;
} pdcp_sub_data_t;


///////////////
// RIC Indication
///////////////

typedef struct{
  pdcp_ind_hdr_t hdr;
  pdcp_ind_msg_t msg;
  pdcp_call_proc_id_t* proc_id;
} pdcp_ind_data_t;

void free_pdcp_ind_data(pdcp_ind_data_t* ind);

pdcp_ind_data_t cp_pdcp_ind_data(pdcp_ind_data_t const* src);


///////////////
// RIC Control
///////////////

typedef struct{
  pdcp_ctrl_hdr_t hdr;
  pdcp_ctrl_msg_t msg;
} pdcp_ctrl_req_data_t;

typedef struct{
  pdcp_ctrl_out_t* out;
} pdcp_ctrl_out_data_t;

///////////////
// E2 Setup
///////////////

typedef struct{
  pdcp_func_def_t func_def;
} pdcp_e2_setup_data_t;

///////////////
// RIC Service Update
///////////////

typedef struct{
  pdcp_func_def_t func_def;
} pdcp_ric_service_update_t;

#ifdef __cplusplus
}
#endif

#endif

