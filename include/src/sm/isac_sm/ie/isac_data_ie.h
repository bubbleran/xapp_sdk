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


#ifndef ISAC_DATA_INFORMATION_ELEMENTS_H
#define ISAC_DATA_INFORMATION_ELEMENTS_H

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
  PERIODIC_ISAC_EVENT,
  APERIODIC_ISAC_EVENT,

  END_ISAC_EVENT,
} isac_event_trigger_e;

typedef enum{
  SRS_ISAC_EVENT_TRIGGER_APER,

  END_ISAC_EVENT_TRIGGER_APER,
} isac_event_trigger_aper_e; 

typedef struct {
  isac_event_trigger_e type;
  union{
    uint32_t periodic_ms;
    isac_event_trigger_aper_e aper;
  };
} isac_event_trigger_t;

void free_isac_event_trigger(isac_event_trigger_t* src); 

isac_event_trigger_t cp_isac_event_trigger( isac_event_trigger_t const* src);

bool eq_isac_event_trigger(isac_event_trigger_t const* m0, isac_event_trigger_t const* m1);

//////////////////////////////////////
// RIC Action Definition 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;  
} isac_action_def_t;

void free_isac_action_def(isac_action_def_t* src); 

isac_action_def_t cp_isac_action_def(isac_action_def_t* src);

bool eq_isac_action_def(isac_event_trigger_t* m0, isac_event_trigger_t* m1);



//////////////////////////////////////
// RIC Indication Header 
/////////////////////////////////////

typedef struct{
  uint32_t dummy;  
} isac_ind_hdr_t;

void free_isac_ind_hdr(isac_ind_hdr_t* src); 

isac_ind_hdr_t cp_isac_ind_hdr(isac_ind_hdr_t const* src);

bool eq_isac_ind_hdr(isac_ind_hdr_t const* m0, isac_ind_hdr_t const* m1);

//////////////////////////////////////
// RIC Indication Message 
/////////////////////////////////////

typedef struct {
  int64_t tstamp;
  uint64_t len_srs_iq;
  // Flexible Array Member
  int16_t srs_iq[]; // Estimated. IQ samples size is 4*len (re, im, noise_re, noise_im) 
} isac_ind_msg_t;

void free_isac_ind_msg(isac_ind_msg_t* src); 

// Need to return a ptr as using flexible array member 
isac_ind_msg_t* cp_isac_ind_msg(isac_ind_msg_t const* src);

bool eq_isac_ind_msg(isac_ind_msg_t const* m0, isac_ind_msg_t const* m1);


//////////////////////////////////////
// RIC Call Process ID 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;
} isac_call_proc_id_t;

void free_isac_call_proc_id( isac_call_proc_id_t* src); 

isac_call_proc_id_t cp_isac_call_proc_id(isac_call_proc_id_t* src);

bool eq_isac_call_proc_id(isac_call_proc_id_t const* m0, isac_call_proc_id_t const* m1);

//////////////////////////////////////
// RIC Control Header 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;
} isac_ctrl_hdr_t;

void free_isac_ctrl_hdr(isac_ctrl_hdr_t* src); 

isac_ctrl_hdr_t cp_isac_ctrl_hdr(isac_ctrl_hdr_t* src);

bool eq_isac_ctrl_hdr(isac_ctrl_hdr_t* m0, isac_ctrl_hdr_t* m1);

//////////////////////////////////////
// RIC Control Message 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;
} isac_ctrl_msg_t;

void free_isac_ctrl_msg(isac_ctrl_msg_t* src);

isac_ctrl_hdr_t cp_isac_ctrl_hdr(isac_ctrl_hdr_t* src);

isac_ctrl_msg_t cp_isac_ctrl_msg(isac_ctrl_msg_t* src);

bool eq_isac_ctrl_msg(isac_ctrl_msg_t* m0, isac_ctrl_msg_t* m1);


//////////////////////////////////////
// RIC Control Outcome 
/////////////////////////////////////

typedef enum{
  ISAC_CTRL_OUT_OK,

  ISAC_CTRL_OUT_KO,

  ISAC_CTRL_OUT_END
} isac_ctrl_out_e;

typedef struct {
  isac_ctrl_out_e ans;  
} isac_ctrl_out_t;

void free_isac_ctrl_out(isac_ctrl_out_t* src); 

isac_ctrl_out_t cp_isac_ctrl_out(isac_ctrl_out_t* src);

bool eq_isac_ctrl_out(isac_ctrl_out_t* m0, isac_ctrl_out_t* m1);


//////////////////////////////////////
// RAN Function Definition 
/////////////////////////////////////

typedef struct {
  size_t len;
  uint8_t* buf;
} isac_func_def_t;

void free_isac_func_def(isac_func_def_t* src); 

isac_func_def_t cp_isac_func_def(isac_func_def_t const* src);

bool eq_isac_func_def(isac_func_def_t const* m0, isac_func_def_t const* m1);


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
  isac_event_trigger_t et; 
  isac_action_def_t* ad;
} isac_sub_data_t;

isac_sub_data_t cp_isac_sub_data(isac_sub_data_t const* src);

void free_isac_sub_data(isac_sub_data_t* src);

bool eq_isac_sub_data(isac_sub_data_t const* m0, isac_sub_data_t const* m1);

///////////////
// RIC Indication
///////////////

typedef struct{
  isac_ind_hdr_t hdr;
  isac_ind_msg_t* msg; // needed for flexible array member
  isac_call_proc_id_t* proc_id;
} isac_ind_data_t;

isac_ind_data_t cp_isac_ind_data(isac_ind_data_t const* src);

void free_isac_ind_data(isac_ind_data_t* ind);

bool eq_isac_ind_data(isac_ind_data_t const* m0, isac_ind_data_t const* m1);

///////////////
// RIC Control
///////////////

typedef struct{
  isac_ctrl_hdr_t hdr;
  isac_ctrl_msg_t msg;
} isac_ctrl_req_data_t;

typedef struct{
  isac_ctrl_out_t* out;
} isac_ctrl_out_data_t;

///////////////
// E2 Setup
///////////////

typedef struct{
  isac_func_def_t func_def;
} isac_e2_setup_data_t;

///////////////
// RIC Service Update
///////////////

typedef struct{
  isac_func_def_t func_def;
} isac_ric_service_update_t;

#ifdef __cplusplus
}
#endif

#endif

