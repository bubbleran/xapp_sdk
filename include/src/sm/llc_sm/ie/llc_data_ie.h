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

#ifndef LLC_DATA_INFORMATION_ELEMENTS_H
#define LLC_DATA_INFORMATION_ELEMENTS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * 9 Information Elements (IE) , RIC Event Trigger Definition, RIC Action Definition, RIC Indication Header, RIC Indication Message, RIC Call Process ID, RIC Control Header, RIC Control Message, RIC Control Outcome and RAN Function Definition defined by ORAN-WG3.E2SM-v01.00.00 at Section 5
 */

#include <stdbool.h>
#include <stdint.h>



//////////////////////////////////////
// RIC Event Trigger Definition
/////////////////////////////////////

#include "ir/e2sm_llc_ev_trg_frmt_1.h"
#include "ir/e2sm_llc_ev_trg_frmt_2.h"

////////////////////////////////////////
//// RIC Action Definition 
///////////////////////////////////////

#include "ir/e2sm_llc_act_def_frmt_1.h"
#include "ir/e2sm_llc_act_def_frmt_2.h"

///////////////////////////////////////
//// RIC Indication Header 
///////////////////////////////////////

#include "ir/e2sm_llc_ind_hdr_frmt_1.h"

///////////////////////////////////////
//// RIC Indication Message 
///////////////////////////////////////

#include "ir/e2sm_llc_ind_msg_frmt_1.h"
#include "ir/e2sm_llc_ind_msg_frmt_2.h"

///////////////////////////////////////
//// RIC Control Header 
///////////////////////////////////////
//
#include "ir/e2sm_llc_ctrl_hdr_frmt_1.h"
//
//
///////////////////////////////////////
//// RIC Control Message 
///////////////////////////////////////
//
#include "ir/e2sm_llc_ctrl_msg_frmt_1.h"
//#include "ir/e2sm_llc_ctrl_msg_frmt_2.h"
//
//
///////////////////////////////////////
//// RIC Control Outcome 
///////////////////////////////////////
//
#include "ir/e2sm_llc_ctrl_out_frmt_1.h"
//#include "ir/e2sm_llc_ctrl_out_frmt_2.h"
//#include "ir/e2sm_llc_ctrl_out_frmt_3.h"
//
///////////////////////////////////////
//// RAN Function Definition 
///////////////////////////////////////
//
#include "../../../lib/sm/ie/ran_function_name.h"
//#include "ir/ran_func_def_ev_trig.h"
//#include "ir/ran_func_def_report.h"
//#include "ir/ran_func_def_insert.h"
//#include "ir/ran_func_def_ctrl.h"
//#include "ir/ran_func_def_policy.h"
//
//////////////////////////////////////
// RIC Event Trigger Definition
/////////////////////////////////////

typedef enum{
  FORMAT_1_E2SM_LLC_EV_TRIGGER_FORMAT ,
  FORMAT_2_E2SM_LLC_EV_TRIGGER_FORMAT ,
  END_E2SM_LLC_EV_TRIGGER_FORMAT
} e2sm_llc_ev_trigger_format_e ;

typedef struct {
  e2sm_llc_ev_trigger_format_e format;
  union{
    e2sm_llc_ev_trg_frmt_1_t frmt_1;     
    e2sm_llc_ev_trg_frmt_2_t frmt_2;     
  };
} e2sm_llc_event_trigger_t;

void free_e2sm_llc_event_trigger(e2sm_llc_event_trigger_t* src); 

e2sm_llc_event_trigger_t cp_e2sm_llc_event_trigger(e2sm_llc_event_trigger_t const* src);

bool eq_e2sm_llc_event_trigger(e2sm_llc_event_trigger_t const* m0, e2sm_llc_event_trigger_t const* m1);


//////////////////////////////////////
// RIC Action Definition 
/////////////////////////////////////

typedef enum{
  FORMAT_1_E2SM_LLC_ACT_DEF ,
  FORMAT_2_E2SM_LLC_ACT_DEF ,
  END_E2SM_LLC_ACT_DEF
} e2sm_llc_act_def_format_e; 

typedef struct {
  //  RIC Style Type
  //  Mandatory
  //  8.3.3
  // Defined in common 6.2.2.2.
  uint32_t ric_style_type; 

  e2sm_llc_act_def_format_e format;
  union{
    // 8.2.1.2 
    e2sm_llc_act_def_frmt_1_t frmt_1;
    e2sm_llc_act_def_frmt_2_t frmt_2;
  };
} e2sm_llc_action_def_t;

void free_e2sm_llc_action_def(e2sm_llc_action_def_t* src); 

e2sm_llc_action_def_t cp_e2sm_llc_action_def(e2sm_llc_action_def_t const* src);

bool eq_e2sm_llc_action_def(e2sm_llc_action_def_t const* m0,  e2sm_llc_action_def_t const* m1);


//////////////////////////////////////
// RIC Indication Header 
/////////////////////////////////////

//typedef enum{
//  FORMAT_1_E2SM_LLC_IND_HDR ,
//  END_E2SM_LLC_IND_HDR
//} e2sm_llc_ind_hdr_format_e; 

typedef struct{
//  e2sm_llc_ind_hdr_format_e format;
//  union{
    e2sm_llc_ind_hdr_frmt_1_t frmt_1; // 8.2.1.3.1 
//  };
} e2sm_llc_ind_hdr_t;

void free_e2sm_llc_ind_hdr(e2sm_llc_ind_hdr_t* src); 

e2sm_llc_ind_hdr_t cp_e2sm_llc_ind_hdr(e2sm_llc_ind_hdr_t const* src);

bool eq_e2sm_llc_ind_hdr(e2sm_llc_ind_hdr_t const* m0, e2sm_llc_ind_hdr_t const* m1);


//////////////////////////////////////
// RIC Indication Message 
/////////////////////////////////////
//
typedef enum{
  FORMAT_1_E2SM_LLC_IND_MSG ,
  FORMAT_2_E2SM_LLC_IND_MSG ,
  END_E2SM_LLC_IND_MSG
} e2sm_llc_ind_msg_format_e ;

// 8.2.1.4
typedef struct {
  e2sm_llc_ind_msg_format_e format; 
  union{
    e2sm_llc_ind_msg_frmt_1_t frmt_1; // 8.2.1.4.1
    e2sm_llc_ind_msg_frmt_2_t frmt_2; // 8.2.1.4.2
  };
} e2sm_llc_ind_msg_t;

void free_e2sm_llc_ind_msg(e2sm_llc_ind_msg_t* src); 

e2sm_llc_ind_msg_t cp_e2sm_llc_ind_msg(e2sm_llc_ind_msg_t const* src);

bool eq_e2sm_llc_ind_msg(e2sm_llc_ind_msg_t const* m0, e2sm_llc_ind_msg_t const* m1);


//////////////////////////////////////
// RIC Call Process ID 
/////////////////////////////////////

// 9.2.1.5.1
typedef struct {
//  // RIC Call Process ID
//  // Mandatory
//  // 9.3.18
//  // [ 1 - 4294967295]
//  uint32_t ric_cpid;

  int dummy;
} e2sm_llc_cpid_t;

void free_e2sm_llc_cpid(e2sm_llc_cpid_t* src); 

e2sm_llc_cpid_t cp_e2sm_llc_cpid(e2sm_llc_cpid_t const* src);

bool eq_e2sm_llc_cpid(e2sm_llc_cpid_t const* m0, e2sm_llc_cpid_t const* m1);


//////////////////////////////////////
// RIC Control Header 
/////////////////////////////////////

//typedef enum{
//  FORMAT_1_E2SM_RC_CTRL_HDR,
//  FORMAT_2_E2SM_RC_CTRL_HDR,
//  END_E2SM_RC_CTRL_HDR,
//} e2sm_llc_ctrl_hdr_e; 

typedef struct {
//  e2sm_llc_ctrl_hdr_e format; 
//  union{
    e2sm_llc_ctrl_hdr_frmt_1_t frmt_1; // 9.2.1.6.1 
//  };
} e2sm_llc_ctrl_hdr_t;

void free_e2sm_llc_ctrl_hdr(e2sm_llc_ctrl_hdr_t* src); 

e2sm_llc_ctrl_hdr_t cp_e2sm_llc_ctrl_hdr(e2sm_llc_ctrl_hdr_t const* src);

bool eq_e2sm_llc_ctrl_hdr(e2sm_llc_ctrl_hdr_t const* m0, e2sm_llc_ctrl_hdr_t const* m1);


//////////////////////////////////////
// RIC Control Message 
/////////////////////////////////////

//typedef enum{
//  FORMAT_1_E2SM_LLC_CTRL_MSG,
//  FORMAT_2_E2SM_LLC_CTRL_MSG,
//  END_E2SM_LLC_CTRL_MSG,
//} e2sm_llc_ctrl_msg_e; 

// 8.2.1.7
typedef struct {
//  e2sm_llc_ctrl_msg_e format; 
//  union{
    e2sm_llc_ctrl_msg_frmt_1_t frmt_1; 
//  };
} e2sm_llc_ctrl_msg_t;

void free_e2sm_llc_ctrl_msg(e2sm_llc_ctrl_msg_t* src); 

e2sm_llc_ctrl_msg_t cp_e2sm_llc_ctrl_msg(e2sm_llc_ctrl_msg_t const* src);

bool eq_e2sm_llc_ctrl_msg(e2sm_llc_ctrl_msg_t const* m0, e2sm_llc_ctrl_msg_t const* m1);



//////////////////////////////////////
// RIC Control Outcome 
/////////////////////////////////////

//typedef enum{
//  FORMAT_1_E2SM_RC_CTRL_OUT,
//  FORMAT_2_E2SM_RC_CTRL_OUT,
//  FORMAT_3_E2SM_RC_CTRL_OUT,
//  END_E2SM_RC_CTRL_OUT,
//} e2sm_llc_ctrl_out_e; 
//
typedef struct {
//  e2sm_llc_ctrl_out_e format; 
//  union{
     e2sm_llc_ctrl_out_frmt_1_t frmt_1; // 8.2.1.8.1 
//     e2sm_llc_ctrl_out_frmt_2_t frmt_2; // 9.2.1.8.2
//     e2sm_llc_ctrl_out_frmt_3_t frmt_3; // 9.2.1.8.3
//  };
} e2sm_llc_ctrl_out_t;

void free_e2sm_llc_ctrl_out(e2sm_llc_ctrl_out_t* src); 

e2sm_llc_ctrl_out_t cp_e2sm_llc_ctrl_out( e2sm_llc_ctrl_out_t const* src);

bool eq_e2sm_llc_ctrl_out(e2sm_llc_ctrl_out_t const* m0, e2sm_llc_ctrl_out_t const* m1);


//////////////////////////////////////
// RAN Function Definition 
/////////////////////////////////////

typedef struct {
  //  RAN Function Name
  //  Mandatory
  //  8.3.2
  //  6.2.2.1.
  ran_function_name_t name;

  // RAN Function Definition for EVENT TRIGGER
  // Optional
  // 8.2.2.2 
  //ran_func_def_ev_trig_llc_t* ev_trig;
  // RAN Function Definition for REPORT
  // Optional
  // 8.2.2.3
  //ran_func_def_report_llc_t* report;
  // RAN Function Definition for CONTROL
  // Optional
  // 8.2.2.5
  //ran_func_def_ctrl_llc_t* ctrl;
} e2sm_llc_func_def_t;

void free_e2sm_llc_func_def( e2sm_llc_func_def_t* src); 

e2sm_llc_func_def_t cp_e2sm_llc_func_def(e2sm_llc_func_def_t const* src);

bool eq_e2sm_llc_func_def(e2sm_llc_func_def_t const* m0, e2sm_llc_func_def_t const* m1);

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
  e2sm_llc_event_trigger_t et; 
  // [1-16]
  size_t sz_ad;
  e2sm_llc_action_def_t* ad;
} llc_sub_data_t;

void free_llc_sub_data(llc_sub_data_t* ind);

bool eq_llc_sub_data(llc_sub_data_t const* m0, llc_sub_data_t const* m1);

llc_sub_data_t cp_llc_sub_data(llc_sub_data_t const* src);

///////////////
// RIC Indication
///////////////

typedef struct{
  e2sm_llc_ind_hdr_t hdr;
  e2sm_llc_ind_msg_t msg;
//  e2sm_llc_cpid_t* proc_id;
} llc_ind_data_t;

void free_llc_ind_data(llc_ind_data_t* ind);

bool eq_llc_ind_data(llc_ind_data_t const* m0, llc_ind_data_t const* m1);

llc_ind_data_t cp_llc_ind_data(llc_ind_data_t const* src);

///////////////
// RIC Control
///////////////

typedef struct{
  e2sm_llc_ctrl_hdr_t hdr;
  e2sm_llc_ctrl_msg_t msg;
} llc_ctrl_req_data_t;

void free_llc_ctrl_req_data(llc_ctrl_req_data_t* src);

bool eq_llc_ctrl_req_data(llc_ctrl_req_data_t const* m0, llc_ctrl_req_data_t  const* m1);

llc_ctrl_req_data_t cp_llc_ctrl_req_data(llc_ctrl_req_data_t const* src);


typedef struct{
  e2sm_llc_ctrl_out_t* out;
} llc_ctrl_out_data_t;

///////////////
// E2 Setup
///////////////

typedef struct{
  e2sm_llc_func_def_t ran_func_def;
} llc_e2_setup_t;

///////////////
// RIC Service Update
///////////////

typedef struct{
  e2sm_llc_func_def_t func_def;
} llc_ric_service_update_t;

#ifdef __cplusplus
}
#endif

#endif

