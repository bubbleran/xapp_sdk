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


#ifndef E2X_DATA_INFORMATION_ELEMENTS_H
#define E2X_DATA_INFORMATION_ELEMENTS_H

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

typedef enum{
  PERIODIC_E2X_SM_EVENT,
  APERIODIC_E2X_SM_EVENT,

  END_E2X_EVENT,
} e2x_event_trigger_e;

typedef struct{
  uint32_t periodicity_ms;
} periodic_event_uni_t;

typedef struct{
  size_t len; 
  uint8_t* data;
} aperiodic_event_uni_t ;

typedef struct {
  e2x_event_trigger_e type;
  union{
    periodic_event_uni_t per;
    aperiodic_event_uni_t aper;
  };
} e2x_event_trigger_t;

void free_e2x_event_trigger(e2x_event_trigger_t* src); 

e2x_event_trigger_t cp_e2x_event_trigger( e2x_event_trigger_t const* src);

bool eq_e2x_event_trigger(e2x_event_trigger_t const* m0, e2x_event_trigger_t const* m1);

//////////////////////////////////////
// RIC Action Definition 
/////////////////////////////////////

typedef struct {
  size_t len; 
  uint8_t* data;
} e2x_action_def_t;

void free_e2x_action_def(e2x_action_def_t* src); 

e2x_action_def_t cp_e2x_action_def(e2x_action_def_t* src);

bool eq_e2x_action_def( e2x_action_def_t* m0, e2x_action_def_t* m1);



//////////////////////////////////////
// RIC Indication Header 
/////////////////////////////////////

typedef struct{
  uint32_t dummy;  
} e2x_ind_hdr_t;

void free_e2x_ind_hdr(e2x_ind_hdr_t* src); 

e2x_ind_hdr_t cp_e2x_ind_hdr(e2x_ind_hdr_t const* src);

bool eq_e2x_ind_hdr(e2x_ind_hdr_t const* m0, e2x_ind_hdr_t const* m1);

//////////////////////////////////////
// RIC Indication Message 
/////////////////////////////////////

typedef struct {
  int64_t tstamp;
  uint64_t len;
  uint8_t* data; 
} e2x_ind_msg_t;

void free_e2x_ind_msg(e2x_ind_msg_t* src); 

// Need to return a ptr as using flexible array member 
e2x_ind_msg_t cp_e2x_ind_msg(e2x_ind_msg_t const* src);

bool eq_e2x_ind_msg(e2x_ind_msg_t const* m0, e2x_ind_msg_t const* m1);


//////////////////////////////////////
// RIC Call Process ID 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;
} e2x_call_proc_id_t;

void free_e2x_call_proc_id( e2x_call_proc_id_t* src); 

e2x_call_proc_id_t cp_e2x_call_proc_id(e2x_call_proc_id_t* src);

bool eq_e2x_call_proc_id(e2x_call_proc_id_t const* m0, e2x_call_proc_id_t const* m1);

//////////////////////////////////////
// RIC Control Header 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;
} e2x_ctrl_hdr_t;

void free_e2x_ctrl_hdr(e2x_ctrl_hdr_t* src); 

e2x_ctrl_hdr_t cp_e2x_ctrl_hdr(e2x_ctrl_hdr_t const* src);

bool eq_e2x_ctrl_hdr(e2x_ctrl_hdr_t const* m0, e2x_ctrl_hdr_t const* m1);

//////////////////////////////////////
// RIC Control Message 
/////////////////////////////////////

typedef struct {
  size_t len;
  uint8_t* data;
} e2x_ctrl_msg_t;

void free_e2x_ctrl_msg(e2x_ctrl_msg_t* src);

e2x_ctrl_msg_t cp_e2x_ctrl_msg(e2x_ctrl_msg_t const* src);

bool eq_e2x_ctrl_msg(e2x_ctrl_msg_t const* m0, e2x_ctrl_msg_t const* m1);


//////////////////////////////////////
// RIC Control Outcome 
/////////////////////////////////////

typedef struct {
  size_t len_data;
  uint8_t* data;
} e2x_ctrl_out_t;

void free_e2x_ctrl_out(e2x_ctrl_out_t* src); 

e2x_ctrl_out_t cp_e2x_ctrl_out(e2x_ctrl_out_t const* src);

bool eq_e2x_ctrl_out(e2x_ctrl_out_t const* m0, e2x_ctrl_out_t const* m1);


//////////////////////////////////////
// RAN Function Definition 
/////////////////////////////////////

typedef struct {
  size_t len;
  uint8_t* buf;
} e2x_func_def_t;

void free_e2x_func_def(e2x_func_def_t* src); 

e2x_func_def_t cp_e2x_func_def(e2x_func_def_t const* src);

bool eq_e2x_func_def(e2x_func_def_t const* m0, e2x_func_def_t const* m1);


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
  e2x_event_trigger_t et; 
  e2x_action_def_t* ad;
} e2x_sub_data_t;

e2x_sub_data_t cp_e2x_sub_data(e2x_sub_data_t const* src);

void free_e2x_sub_data(e2x_sub_data_t* src);

bool eq_e2x_sub_data(e2x_sub_data_t const* m0, e2x_sub_data_t const* m1);

///////////////
// RIC Indication
///////////////

typedef struct{
  e2x_ind_hdr_t hdr;
  e2x_ind_msg_t msg; // needed for flexible array member
  e2x_call_proc_id_t* proc_id;
} e2x_ind_data_t;

e2x_ind_data_t cp_e2x_ind_data(e2x_ind_data_t const* src);

void free_e2x_ind_data(e2x_ind_data_t* ind);

bool eq_e2x_ind_data(e2x_ind_data_t const* m0, e2x_ind_data_t const* m1);

///////////////
// RIC Control
///////////////

typedef struct{
  e2x_ctrl_hdr_t hdr;
  e2x_ctrl_msg_t msg;
} e2x_ctrl_req_data_t;

bool eq_e2x_ctrl_req_data(e2x_ctrl_req_data_t const* m0, e2x_ctrl_req_data_t const* m1);


typedef struct{
  e2x_ctrl_out_t* out;
} e2x_ctrl_out_data_t;

///////////////
// E2 Setup
///////////////

typedef struct{
  e2x_func_def_t func_def;
} e2x_e2_setup_data_t;

///////////////
// RIC Service Update
///////////////

typedef struct{
  e2x_func_def_t func_def;
} e2x_ric_service_update_t;

#ifdef __cplusplus
}
#endif

#endif

