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

#ifndef GTP_DATA_INFORMATION_ELEMENTS_H
#define GTP_DATA_INFORMATION_ELEMENTS_H

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
} gtp_event_trigger_t;

void free_gtp_event_trigger(gtp_event_trigger_t* src); 

gtp_event_trigger_t cp_gtp_event_trigger( gtp_event_trigger_t* src);

bool eq_gtp_event_trigger(gtp_event_trigger_t* m0, gtp_event_trigger_t* m1);



//////////////////////////////////////
// RIC Action Definition 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;  
} gtp_action_def_t;

void free_gtp_action_def(gtp_action_def_t* src); 

gtp_action_def_t cp_gtp_action_def(gtp_action_def_t* src);

bool eq_gtp_action_def(gtp_event_trigger_t* m0,  gtp_event_trigger_t* m1);



//////////////////////////////////////
// RIC Indication Header 
/////////////////////////////////////

typedef struct{
  uint32_t dummy;  
} gtp_ind_hdr_t;

void free_gtp_ind_hdr(gtp_ind_hdr_t* src); 

gtp_ind_hdr_t cp_gtp_ind_hdr(gtp_ind_hdr_t const* src);

bool eq_gtp_ind_hdr(gtp_ind_hdr_t* m0, gtp_ind_hdr_t* m1);


//////////////////////////////////////
// RIC Indication Message 
/////////////////////////////////////

typedef struct {
  // ngu tunnel stats
  uint32_t rnti; // user id
  uint32_t teidgnb; // tunnel id from gnb
  uint32_t teidupf; // tunnel id from upf
  uint8_t qfi; // QoS flow indicator
} gtp_ngu_t_stats_t;

typedef struct {
  uint32_t len;
  gtp_ngu_t_stats_t* ngut;

  int64_t tstamp;
} gtp_ind_msg_t;

void free_gtp_ind_msg(gtp_ind_msg_t* src); 

gtp_ind_msg_t cp_gtp_ind_msg(gtp_ind_msg_t const* src);

bool eq_gtp_ind_msg(gtp_ind_msg_t* m0, gtp_ind_msg_t* m1);


//////////////////////////////////////
// RIC Call Process ID 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;
} gtp_call_proc_id_t;

void free_gtp_call_proc_id( gtp_call_proc_id_t* src); 

gtp_call_proc_id_t cp_gtp_call_proc_id( gtp_call_proc_id_t* src);

bool eq_gtp_call_proc_id(gtp_call_proc_id_t* m0, gtp_call_proc_id_t* m1);



//////////////////////////////////////
// RIC Control Header 
/////////////////////////////////////


typedef struct {
  uint32_t dummy;
} gtp_ctrl_hdr_t;

void free_gtp_ctrl_hdr( gtp_ctrl_hdr_t* src); 

gtp_ctrl_hdr_t cp_gtp_ctrl_hdr(gtp_ctrl_hdr_t* src);

bool eq_gtp_ctrl_hdr(gtp_ctrl_hdr_t* m0, gtp_ctrl_hdr_t* m1);



//////////////////////////////////////
// RIC Control Message 
/////////////////////////////////////


typedef struct {
  uint32_t action;
} gtp_ctrl_msg_t;

void free_gtp_ctrl_msg( gtp_ctrl_msg_t* src); 

gtp_ctrl_msg_t cp_gtp_ctrl_msg(gtp_ctrl_msg_t* src);

bool eq_gtp_ctrl_msg(gtp_ctrl_msg_t* m0, gtp_ctrl_msg_t* m1);



//////////////////////////////////////
// RIC Control Outcome 
/////////////////////////////////////

typedef enum{
  GTP_CTRL_OUT_OK,

  GTP_CTRL_OUT_END
} gtp_ctrl_out_e;


typedef struct {
  gtp_ctrl_out_e ans;
} gtp_ctrl_out_t;

void free_gtp_ctrl_out(gtp_ctrl_out_t* src); 

gtp_ctrl_out_t cp_gtp_ctrl_out(gtp_ctrl_out_t* src);

bool eq_gtp_ctrl_out(gtp_ctrl_out_t* m0, gtp_ctrl_out_t* m1);


//////////////////////////////////////
// RAN Function Definition 
/////////////////////////////////////

typedef struct {
  uint8_t* buf;
  size_t len;
} gtp_func_def_t;

void free_gtp_func_def(gtp_func_def_t* src); 

gtp_func_def_t cp_gtp_func_def(gtp_func_def_t const* src);

bool eq_gtp_func_def(gtp_func_def_t const* m0, gtp_func_def_t const* m1);

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
  gtp_event_trigger_t et; 
  gtp_action_def_t* ad;
} gtp_sub_data_t;

///////////////
// RIC Indication
///////////////

typedef struct{
  gtp_ind_hdr_t hdr;
  gtp_ind_msg_t msg;
  gtp_call_proc_id_t* proc_id;
} gtp_ind_data_t;

void free_gtp_ind_data(gtp_ind_data_t* ind);

gtp_ind_data_t cp_gtp_ind_data(gtp_ind_data_t const* src);

///////////////
// RIC Control
///////////////

typedef struct{
  gtp_ctrl_hdr_t hdr;
  gtp_ctrl_msg_t msg;
} gtp_ctrl_req_data_t;

typedef struct{
  gtp_ctrl_out_t* out;
} gtp_ctrl_out_data_t;

///////////////
// E2 Setup
///////////////

typedef struct{
  gtp_func_def_t func_def;
} gtp_e2_setup_data_t;

///////////////
// RIC Service Update
///////////////

typedef struct{
  gtp_func_def_t func_def;
} gtp_ric_service_update_t;


#ifdef __cplusplus
}
#endif

#endif

