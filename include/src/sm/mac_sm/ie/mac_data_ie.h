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


#ifndef MAC_DATA_INFORMATION_ELEMENTS_H
#define MAC_DATA_INFORMATION_ELEMENTS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * 9 Information Elements (IE) , RIC Event Trigger Definition, RIC Action Definition, RIC Indication Header, RIC Indication Message, RIC Call Process ID, RIC Control Header, RIC Control Message, RIC Control Outcome and RAN Function Definition defined by ORAN-WG3.E2SM-v01.00.00 at Section 5
 */


#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

//////////////////////////////////////
// RIC Event Trigger Definition
/////////////////////////////////////

typedef struct {
  uint32_t ms;
} mac_event_trigger_t;

void free_mac_event_trigger(mac_event_trigger_t* src); 

mac_event_trigger_t cp_mac_event_trigger( mac_event_trigger_t const* src);

bool eq_mac_event_trigger(mac_event_trigger_t const* m0, mac_event_trigger_t const* m1);



//////////////////////////////////////
// RIC Action Definition 
/////////////////////////////////////


typedef struct {
  uint32_t dummy;  
} mac_action_def_t;

void free_mac_action_def(mac_action_def_t* src); 

mac_action_def_t cp_mac_action_def(mac_action_def_t* src);

bool eq_mac_action_def(mac_event_trigger_t* m0,  mac_event_trigger_t* m1);



//////////////////////////////////////
// RIC Indication Header 
/////////////////////////////////////


typedef struct{
  uint32_t dummy;  
} mac_ind_hdr_t;

void free_mac_ind_hdr(mac_ind_hdr_t* src); 

mac_ind_hdr_t cp_mac_ind_hdr(mac_ind_hdr_t const* src);

bool eq_mac_ind_hdr(mac_ind_hdr_t* m0, mac_ind_hdr_t* m1);

//////////////////////////////////////
// RIC Indication Message 
/////////////////////////////////////

typedef struct
{
  uint64_t dl_aggr_tbs;
  uint64_t ul_aggr_tbs;
  uint64_t dl_aggr_bytes_sdus;
  uint64_t ul_aggr_bytes_sdus;
  uint64_t dl_curr_tbs;
  uint64_t ul_curr_tbs;
  uint64_t dl_sched_rb;
  uint64_t ul_sched_rb;
 
  float pusch_snr; //: float = -64;
  float pucch_snr; //: float = -64;

  float dl_bler;
  float ul_bler;

  uint32_t dl_harq[5];
  uint32_t ul_harq[5];
  uint32_t dl_num_harq;
  uint32_t ul_num_harq;

  uint32_t rnti;
  uint32_t dl_aggr_prb; 
  uint32_t ul_aggr_prb;
  uint32_t dl_aggr_sdus;
  uint32_t ul_aggr_sdus;
  uint32_t dl_aggr_retx_prb;
  uint32_t ul_aggr_retx_prb;

  uint32_t bsr;
  uint16_t frame;
  uint16_t slot;

  uint8_t wb_cqi; 
  uint8_t dl_mcs1;
  uint8_t ul_mcs1;
  uint8_t dl_mcs2; 
  uint8_t ul_mcs2; 
  int8_t phr; 

} mac_ue_stats_impl_t;

mac_ue_stats_impl_t cp_mac_ue_stats_impl(mac_ue_stats_impl_t const* src);

typedef struct {
  uint32_t len_ue_stats;
  mac_ue_stats_impl_t* ue_stats;
  int64_t tstamp;
} mac_ind_msg_t;

void free_mac_ind_msg(mac_ind_msg_t* src); 

mac_ind_msg_t cp_mac_ind_msg(mac_ind_msg_t const* src);

bool eq_mac_ind_msg(mac_ind_msg_t* m0, mac_ind_msg_t* m1);


//////////////////////////////////////
// RIC Call Process ID 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;
} mac_call_proc_id_t;

void free_mac_call_proc_id( mac_call_proc_id_t* src); 

mac_call_proc_id_t cp_mac_call_proc_id( mac_call_proc_id_t* src);

bool eq_mac_call_proc_id(mac_call_proc_id_t* m0, mac_call_proc_id_t* m1);

//////////////////////////////////////
// RIC Control Header 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;
} mac_ctrl_hdr_t;

void free_mac_ctrl_hdr( mac_ctrl_hdr_t* src); 

mac_ctrl_hdr_t cp_mac_ctrl_hdr(mac_ctrl_hdr_t* src);

bool eq_mac_ctrl_hdr(mac_ctrl_hdr_t* m0, mac_ctrl_hdr_t* m1);

//////////////////////////////////////
// RIC Control Message 
/////////////////////////////////////

// mac_conf_t contains the list of all the params you may want to set thanks to its associated flag variable 'isset_*'
typedef struct {
  uint32_t rnti;     // compulsory. Used to detect which cell you want to modify
  uint8_t pusch_mcs; // set Modulation Coding Scheme (MCS) value for Physical Uplink Shared Channel. Range: [0..28]
  bool isset_pusch_mcs; 
} mac_conf_t;

typedef struct {
  uint32_t    ran_conf_len; // count how many items you have in ran_conf array
  mac_conf_t* ran_conf; 
} mac_ctrl_msg_t;


void free_mac_ctrl_msg( mac_ctrl_msg_t* src);

mac_ctrl_hdr_t cp_mac_ctrl_hdr(mac_ctrl_hdr_t* src);

mac_ctrl_msg_t cp_mac_ctrl_msg(mac_ctrl_msg_t* src);

bool eq_mac_ctrl_msg(mac_ctrl_msg_t* m0, mac_ctrl_msg_t* m1);


//////////////////////////////////////
// RIC Control Outcome 
/////////////////////////////////////

typedef enum{
  MAC_CTRL_OUT_OK,

  MAC_CTRL_OUT_KO,

  MAC_CTRL_OUT_END
} mac_ctrl_out_e;

typedef struct {
  mac_ctrl_out_e ans;  
} mac_ctrl_out_t;

void free_mac_ctrl_out(mac_ctrl_out_t* src); 

mac_ctrl_out_t cp_mac_ctrl_out(mac_ctrl_out_t* src);

bool eq_mac_ctrl_out(mac_ctrl_out_t* m0, mac_ctrl_out_t* m1);


//////////////////////////////////////
// RAN Function Definition 
/////////////////////////////////////

typedef struct {
  size_t len;
  uint8_t* buf;
} mac_func_def_t;

void free_mac_func_def(mac_func_def_t* src); 

mac_func_def_t cp_mac_func_def(mac_func_def_t const* src);

bool eq_mac_func_def(mac_func_def_t const* m0, mac_func_def_t const* m1);


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
  mac_event_trigger_t et; 
  mac_action_def_t* ad;
} mac_sub_data_t;

///////////////
// RIC Indication
///////////////

typedef struct{
  mac_ind_hdr_t hdr;
  mac_ind_msg_t msg;
  mac_call_proc_id_t* proc_id;
} mac_ind_data_t;

mac_ind_data_t cp_mac_ind_data( mac_ind_data_t const* src);

void free_mac_ind_data(mac_ind_data_t* ind);

///////////////
// RIC Control
///////////////

typedef struct{
  mac_ctrl_hdr_t hdr;
  mac_ctrl_msg_t msg;
} mac_ctrl_req_data_t;

typedef struct{
  mac_ctrl_out_t* out;
} mac_ctrl_out_data_t;

///////////////
// E2 Setup
///////////////

typedef struct{
  mac_func_def_t func_def;
} mac_e2_setup_data_t;

///////////////
// RIC Service Update
///////////////

typedef struct{
  mac_func_def_t func_def;
} mac_ric_service_update_t;

#ifdef __cplusplus
}
#endif




#endif

