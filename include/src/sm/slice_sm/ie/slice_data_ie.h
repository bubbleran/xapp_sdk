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

#ifndef SLICE_DATA_INFORMATION_ELEMENTS_H
#define SLICE_DATA_INFORMATION_ELEMENTS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * 9 Information Elements (IE) , RIC Event Trigger Definition, RIC Action Definition, RIC Indication Header, RIC Indication Message, RIC Call Process ID, RIC Control Header, RIC Control Message, RIC Control Outcome and RAN Function Definition defined by ORAN-WG3.E2SM-v01.00.00 at Section 5
 */

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>


static_assert(sizeof(float) == 4, "Assumption that float types are 4 bytes long invalid. Check where the float type is used"); 

//////////////////////////////////////
// RIC Event Trigger Definition
/////////////////////////////////////

typedef struct {
  uint32_t ms;
} slice_event_trigger_t;

void free_slice_event_trigger(slice_event_trigger_t* src); 

slice_event_trigger_t cp_slice_event_trigger( slice_event_trigger_t* src);

bool eq_slice_event_trigger(slice_event_trigger_t* m0, slice_event_trigger_t* m1);



//////////////////////////////////////
// RIC Action Definition 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;  
} slice_action_def_t;

void free_slice_action_def(slice_action_def_t* src); 

slice_action_def_t cp_slice_action_def(slice_action_def_t* src);

bool eq_slice_action_def(slice_event_trigger_t* m0,  slice_event_trigger_t* m1);



//////////////////////////////////////
// RIC Indication Header 
/////////////////////////////////////

typedef struct{
  uint32_t dummy;  
} slice_ind_hdr_t;

void free_slice_ind_hdr(slice_ind_hdr_t* src); 

slice_ind_hdr_t cp_slice_ind_hdr(slice_ind_hdr_t const* src);

bool eq_slice_ind_hdr(slice_ind_hdr_t* m0, slice_ind_hdr_t* m1);



//////////////////////////////////////
// RIC Indication Message 
/////////////////////////////////////


typedef enum{
  SLICE_ALG_SM_V0_NONE = 0,
  SLICE_ALG_SM_V0_STATIC = 1,
  SLICE_ALG_SM_V0_NVS = 2,
  SLICE_ALG_SM_V0_SCN19 = 3,
  SLICE_ALG_SM_V0_EDF = 4,
  SLICE_ALG_SM_V0_EEDF = 5,
  SLICE_ALG_SM_V0_PR = 6,

  SLICE_ALG_SM_V0_END
} slice_algorithm_e;


typedef struct{
  uint32_t pos_low;
  uint32_t pos_high;
} static_slice_t ;


typedef enum {
  SLICE_SM_NVS_V0_RATE,
  SLICE_SM_NVS_V0_CAPACITY,

  SLICE_SM_NVS_V0_END
} nvs_slice_conf_e;

/*
typedef struct{
 union{
  uint8_t mbps_required_byte[4]; 
  float mbps_required;
 };
 union{
 uint8_t mbps_reference_byte[4];
 float mbps_reference;
 };
} nvs_rate_t ; 
*/
  typedef union {
    uint8_t mbps_required_byte[4]; 
    float mbps_required;
  } nvs_rate_req_u;

  typedef union {
    uint8_t mbps_reference_byte[4];
    float mbps_reference;
  } nvs_rate_ref_u;


  typedef struct{
    nvs_rate_req_u u1;
    nvs_rate_ref_u u2;
  } nvs_rate_t ; 



/*
typedef struct{
  union{
  uint8_t pct_reserved_byte[4];
  float pct_reserved;
  };
} nvs_capacity_t;

typedef struct{
 nvs_slice_conf_e conf;
  union{
  nvs_rate_t rate; 
  nvs_capacity_t capacity;
  };
} nvs_slice_t ;
*/

  typedef union{
    uint8_t pct_reserved_byte[4];
    float pct_reserved;
  } nvs_capacity_u;

  typedef struct{
    nvs_capacity_u u;
  } nvs_capacity_t;

  typedef union{
    nvs_rate_t rate; 
    nvs_capacity_t capacity;
  } nvs_slice_u;


  typedef struct{
    nvs_slice_conf_e conf;
    nvs_slice_u u;
  } nvs_slice_t ;




typedef enum{
  SLICE_SCN19_SM_V0_DYNAMIC,
  SLICE_SCN19_SM_V0_FIXED,
  SLICE_SCN19_SM_V0_ON_DEMAND,

  SLICE_SCN19_SM_V0_END,
} scn19_slice_conf_e ;

/*
typedef struct{
  union{
  uint8_t pct_reserved_byte[4];
  float pct_reserved;
  };
  union{
  uint8_t log_delta_byte;
  float log_delta;
  };
  uint32_t tau;
} scn19_on_demand_t ;
*/

  typedef struct{
    float pct_reserved;
    float log_delta;
    uint32_t tau;
  } scn19_on_demand_t ;



/*
typedef struct{
  scn19_slice_conf_e conf;
  union{
    nvs_rate_t dynamic;
    static_slice_t fixed;
    scn19_on_demand_t on_demand;
  };
} scn19_slice_t;
*/

  typedef union{
    nvs_rate_t dynamic;
    static_slice_t fixed;
    scn19_on_demand_t on_demand;
  } scn19_slice_u;

  typedef struct{
    scn19_slice_conf_e conf;
    scn19_slice_u u;
  } scn19_slice_t;






typedef struct{
  int32_t deadline;
  int32_t guaranteed_prbs;
  int16_t max_replenish;
  int8_t len_over;
  int32_t* over;
} edf_slice_t ;


typedef enum {
  SLICE_SM_EEDF_V0_STATIC,
  SLICE_SM_EEDF_V0_RATE,

  SLICE_SM_EEDF_V0_END
} eedf_slice_conf_e;

typedef enum {
  EEDF_STATIC_HARD,
  EEDF_STATIC_SOFT
} eedf_static_type_t;

typedef struct{
  int16_t reserved_prbs;
  eedf_static_type_t reserved_type;
} eedf_static_t;

typedef struct{
  int32_t deadline;
  int32_t guaranteed_rate;
} eedf_rate_t;

typedef union{
  eedf_static_t fixed;
  eedf_rate_t rate; 
} eedf_slice_u;

typedef struct{
  eedf_slice_conf_e conf;
  eedf_slice_u u;
} eedf_slice_t ;

typedef struct{
  uint8_t max_ratio;
  uint8_t min_ratio;
  uint8_t dedicated_ratio;
} pr_slice_t;

/*
typedef struct{
  slice_algorithm_e type; 
  union{
    static_slice_t sta;
    nvs_slice_t nvs;
    scn19_slice_t scn19;
    edf_slice_t edf;
  } ;
} slice_params_t;
*/

  typedef union{
    static_slice_t sta;
    nvs_slice_t nvs;
    scn19_slice_t scn19;
    edf_slice_t edf;
    eedf_slice_t eedf;
    pr_slice_t pr;
  } slice_params_u;


  typedef struct{
    slice_algorithm_e type; 
    slice_params_u u;
  } slice_params_t;






typedef struct{
	uint32_t id;

  uint32_t len_label;
  char* label;

  uint32_t len_sched;
  char* sched;

  slice_params_t params;
} fr_slice_t ;

typedef struct{
  uint32_t len_slices;
  fr_slice_t* slices;

  uint32_t len_sched_name;
  char* sched_name;
} ul_dl_slice_conf_t ;

typedef struct{
  ul_dl_slice_conf_t dl;
  ul_dl_slice_conf_t ul;
} slice_conf_t ;

typedef struct{
  uint32_t dl_id;
  uint32_t ul_id;
  uint16_t rnti;
}ue_slice_assoc_t; 

typedef struct{
  uint32_t len_ue_slice;
  ue_slice_assoc_t * ues; 
} ue_slice_conf_t;


typedef struct {
  slice_conf_t slice_conf;
  ue_slice_conf_t ue_slice_conf;
  int64_t tstamp;
} slice_ind_msg_t;

void free_slice_ind_msg(slice_ind_msg_t* src); 

slice_ind_msg_t cp_slice_ind_msg(slice_ind_msg_t const* src);

slice_conf_t cp_slice_conf(slice_conf_t const* src);

ue_slice_conf_t cp_ue_slice_conf(ue_slice_conf_t const* src);

bool eq_slice_ind_msg(slice_ind_msg_t const* m0, slice_ind_msg_t const* m1);



//////////////////////////////////////
// RIC Call Process ID 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;
} slice_call_proc_id_t;

void free_slice_call_proc_id( slice_call_proc_id_t* src); 

slice_call_proc_id_t cp_slice_call_proc_id( slice_call_proc_id_t* src);

bool eq_slice_call_proc_id(slice_call_proc_id_t* m0, slice_call_proc_id_t* m1);




//////////////////////////////////////
// RIC Control Header 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;
} slice_ctrl_hdr_t;

void free_slice_ctrl_hdr( slice_ctrl_hdr_t* src); 

slice_ctrl_hdr_t cp_slice_ctrl_hdr(slice_ctrl_hdr_t* src);

bool eq_slice_ctrl_hdr(slice_ctrl_hdr_t const* m0, slice_ctrl_hdr_t const* m1);


//////////////////////////////////////
// RIC Control Message 
/////////////////////////////////////

typedef enum{
  SLICE_CTRL_SM_V0_ADD,
  SLICE_CTRL_SM_V0_DEL,
  SLICE_CTRL_SM_V0_UE_SLICE_ASSOC,

  SLICE_CTRL_SM_V0_END
} slice_ctrl_msg_e ;

typedef struct{
 uint32_t len_dl;
 uint32_t* dl;
 uint32_t len_ul;
 uint32_t* ul;
} del_slice_conf_t; 
/*
typedef struct {
  slice_ctrl_msg_e type; 
  union{
    slice_conf_t add_mod_slice;
    del_slice_conf_t del_slice;
    ue_slice_conf_t ue_slice;
  };
} slice_ctrl_msg_t;
*/

  typedef union{
    slice_conf_t add_mod_slice;
    del_slice_conf_t del_slice;
    ue_slice_conf_t ue_slice;
  } slice_ctrl_msg_u;

  typedef struct {
    slice_ctrl_msg_e type; 
    slice_ctrl_msg_u u;
  } slice_ctrl_msg_t;




void free_slice_ctrl_msg( slice_ctrl_msg_t* src); 

slice_ctrl_msg_t cp_slice_ctrl_msg(slice_ctrl_msg_t* src);

bool eq_slice_ctrl_msg(slice_ctrl_msg_t const* m0, slice_ctrl_msg_t const* m1);


//////////////////////////////////////
// RIC Control Outcome 
/////////////////////////////////////

typedef enum{
  SLICE_CTRL_OUT_OK,
  SLICE_CTRL_OUT_ERROR,

  SLICE_ANS_END
} slice_ctrl_out_e;

typedef struct {
  slice_ctrl_out_e ans;
  uint32_t len_diag;
  char* diagnostic; // human-readable diagnostic for northbound
} slice_ctrl_out_t;

void free_slice_ctrl_out(slice_ctrl_out_t* src); 

slice_ctrl_out_t cp_slice_ctrl_out(slice_ctrl_out_t* src);

bool eq_slice_ctrl_out(slice_ctrl_out_t* m0, slice_ctrl_out_t* m1);



//////////////////////////////////////
// RAN Function Definition 
/////////////////////////////////////

typedef struct {
  uint32_t len_supported_alg;
  slice_algorithm_e* supported_alg;
} slice_func_def_t;

void free_slice_func_def( slice_func_def_t* src); 

slice_func_def_t cp_slice_func_def(slice_func_def_t const* src);

bool eq_slice_func_def(slice_func_def_t const* m0, slice_func_def_t const* m1);


/*
void slice_free_ind_msg(slice_ind_msg_t* msg);

void slice_free_ctrl_msg(slice_ctrl_msg_t* msg);

void slice_free_ctrl_out(slice_ctrl_out_t* out);
*/

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
  slice_event_trigger_t et; 
  slice_action_def_t* ad;
} slice_sub_data_t;

///////////////
// RIC Indication
///////////////

typedef struct{
  slice_ind_hdr_t hdr;
  slice_ind_msg_t msg;
  slice_call_proc_id_t* proc_id;
} slice_ind_data_t;

void free_slice_ind_data(slice_ind_data_t* ind);

slice_ind_data_t cp_slice_ind_data(slice_ind_data_t const* src);

///////////////
// RIC Control
///////////////

typedef struct{
  slice_ctrl_hdr_t hdr;
  slice_ctrl_msg_t msg;
} slice_ctrl_req_data_t;

typedef struct{
  slice_ctrl_out_t* out;
} slice_ctrl_out_data_t;

///////////////
// E2 Setup
///////////////

typedef struct{
  slice_func_def_t func_def;
} slice_e2_setup_data_t;

///////////////
// RIC Service Update
///////////////

typedef struct{
  slice_func_def_t func_def;
} slice_ric_service_update_t;


#ifdef __cplusplus
}
#endif


#endif

