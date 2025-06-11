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

#ifndef TC_DATA_INFORMATION_ELEMENTS_H
#define TC_DATA_INFORMATION_ELEMENTS_H

/*
 * 9 Information Elements (IE) , RIC Event Trigger Definition, RIC Action Definition, RIC Indication Header, RIC Indication Message, RIC Call Process ID, RIC Control Header, RIC Control Message, RIC Control Outcome and RAN Function Definition defined by ORAN-WG3.E2SM-v01.00.00 at Section 5
 */

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "ndpi_protocol_ids.h"


static_assert(sizeof(float) == 4, "Assumption that float types are 4 bytes long invalid. Check where the float type is used"); 

//////////////////////////////////////
// RIC Event Trigger Definition
/////////////////////////////////////

typedef struct {
  uint32_t ms;
} tc_event_trigger_t;

void free_tc_event_trigger(tc_event_trigger_t* src); 

tc_event_trigger_t cp_tc_event_trigger( tc_event_trigger_t* src);

bool eq_tc_event_trigger(tc_event_trigger_t* m0, tc_event_trigger_t* m1);



//////////////////////////////////////
// RIC Action Definition 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;
} tc_action_def_t;

void free_tc_action_def(tc_action_def_t* src); 

tc_action_def_t cp_tc_action_def(tc_action_def_t* src);

bool eq_tc_action_def(tc_event_trigger_t* m0,  tc_event_trigger_t* m1);



//////////////////////////////////////
// RIC Indication Header 
/////////////////////////////////////

typedef struct{
  uint16_t rnti;
  uint16_t rb_id;
} tc_ind_hdr_t;

void free_tc_ind_hdr(tc_ind_hdr_t* src); 

tc_ind_hdr_t cp_tc_ind_hdr(tc_ind_hdr_t const* src);

bool eq_tc_ind_hdr(tc_ind_hdr_t const* m0, tc_ind_hdr_t const* m1);



//////////////////////////////////////
// RIC Indication Message 
/////////////////////////////////////

// OSI L3 filter
typedef struct{
  int64_t src_addr; // filter wildcard (i.e., -1) indicates matches all
  int64_t dst_addr;
  int32_t tos;
} L3_filter_t;

void free_L3_filter(L3_filter_t*);

bool eq_L3_filter(L3_filter_t const* m0, L3_filter_t const* m1);

L3_filter_t cp_L3_filter(L3_filter_t const*);


// OSI L4 filter
typedef struct{
  int32_t src_port;
  int32_t dst_port;
  int32_t protocol;
} L4_filter_t;

void free_L4_filter(L4_filter_t* src);

bool eq_L4_filter(L4_filter_t const* m0, L4_filter_t const* m1);

L4_filter_t cp_L4_filter(L4_filter_t const* src);


// OSI L7 filter
typedef struct{
  // NDPI
  ndpi_protocol_id_t protocol;
  uint32_t len_protocol_name;
  char* protocol_name;
  uint32_t len_category_name;
  char* category_name;
} L7_filter_t;

void free_L7_filter(L7_filter_t*);

bool eq_L7_filter(L7_filter_t const* m0, L7_filter_t const* m1);

L7_filter_t cp_L7_filter(L7_filter_t const*);


typedef struct{
  uint32_t id;
  L3_filter_t l3;
  L4_filter_t l4;
  L7_filter_t l7;
  int32_t dst_queue;
} tc_cls_osi_filter_t;

void free_tc_cls_osi_filter( tc_cls_osi_filter_t*);

bool eq_tc_cls_osi_filter(tc_cls_osi_filter_t const* m0, tc_cls_osi_filter_t const* m1);

tc_cls_osi_filter_t cp_tc_cls_osi_filter(tc_cls_osi_filter_t const*);

typedef enum {
  TC_CLS_RR,
  TC_CLS_STO,
  TC_CLS_OSI_DPI,

  TC_CLS_END
} tc_cls_e ;

typedef struct {
  uint32_t dummy;
} tc_cls_rr_t;

typedef struct {
  uint32_t dummy;
} tc_cls_sto_t; 

typedef struct{
  uint32_t id;
  int32_t dst_queue;
  L3_filter_t l3;
  L4_filter_t l4;
  L7_filter_t l7;
} tc_cls_osi_dpi_filter_t;

tc_cls_osi_dpi_filter_t cp_tc_cls_osi_dpi_filter(tc_cls_osi_dpi_filter_t const* src);

bool eq_tc_cls_osi_dpi_filter(tc_cls_osi_dpi_filter_t const* m0, tc_cls_osi_dpi_filter_t const* m1);

void free_tc_cls_osi_dpi_filter(tc_cls_osi_dpi_filter_t* src);

typedef struct {
  int64_t tstamp;
  int32_t dst_queue;
  L3_filter_t l3;
  L4_filter_t l4;
  L7_filter_t l7;
} tc_cls_osi_dpi_pkt_t;

tc_cls_osi_dpi_pkt_t cp_tc_cls_osi_dpi_pkt(tc_cls_osi_dpi_pkt_t const* src);

bool eq_tc_cls_osi_dpi_pkt(tc_cls_osi_dpi_pkt_t const* m0, tc_cls_osi_dpi_pkt_t const* m1);

void free_tc_cls_osi_dpi_pkt(tc_cls_osi_dpi_pkt_t* src);

typedef struct{
  uint32_t len_flt;
  tc_cls_osi_dpi_filter_t* flt;
  uint32_t len_pkt;
  tc_cls_osi_dpi_pkt_t* pkt; 
} tc_cls_osi_dpi_t;

bool eq_tc_cls_osi_dpi(tc_cls_osi_dpi_t const* m0, tc_cls_osi_dpi_t const* m1);

void free_tc_cls_osi_dpi(tc_cls_osi_dpi_t* src);

// Classifier
// map input data to a category
typedef struct {
  tc_cls_e type;
  union {
    tc_cls_rr_t rr;
    tc_cls_sto_t sto;
    tc_cls_osi_dpi_t osi_dpi;
  };
} tc_cls_t;

bool eq_tc_cls(tc_cls_t const* m0, tc_cls_t const* m1);

static_assert(sizeof(float) == 4*sizeof(uint8_t), "Union mismatch as it is presumed that a float occupies 4 bytes");
typedef struct{
  uint32_t time_window_ms; 
  union{
    float bnd_flt;
    uint8_t bnd_uint[4];
  };
} tc_mtr_t;

typedef struct{
  uint32_t dropped_pkts;
} tc_drp_t;

typedef struct{
  uint32_t marked_pkts;
} tc_mrk_t ;

// Policer
typedef struct {
  uint32_t id;
  // RFC 2475

  // meter
  tc_mtr_t mtr;

  // dropper
  tc_drp_t drp;

  // marker
  tc_mrk_t mrk;

  float max_rate_kbps;
  uint32_t active;
  uint32_t dst_id;
  uint32_t dev_id;

} tc_plc_t;

// Queue
typedef enum{
  TC_QUEUE_FIFO,
  TC_QUEUE_CODEL,
  TC_QUEUE_ECN_CODEL,

  TC_QUEUE_END
} tc_queue_e; 

typedef struct{
  uint32_t bytes;
  uint32_t pkts;
  uint32_t bytes_fwd;
  uint32_t pkts_fwd;
  // dropper
  tc_drp_t drp;
  float avg_sojourn_time;
  int64_t last_sojourn_time;
} tc_queue_fifo_t;

typedef struct{
  uint32_t bytes;
  uint32_t pkts;
  uint32_t bytes_fwd;
  uint32_t pkts_fwd;
  // dropper
  tc_drp_t drp;
  float avg_sojourn_time;
  int64_t last_sojourn_time;
} tc_queue_codel_t;

typedef struct{
  uint32_t bytes;
  uint32_t pkts;
  uint32_t bytes_fwd;
  uint32_t pkts_fwd;
  // marker
  tc_mrk_t mrk;
  float avg_sojourn_time;
  int64_t last_sojourn_time;
} tc_queue_ecn_codel_t;

typedef struct{
   uint32_t id;
   tc_queue_e type;
    union{
     tc_queue_fifo_t fifo;
     tc_queue_codel_t codel;
     tc_queue_ecn_codel_t ecn;
    };
} tc_queue_t;


// Scheduler
typedef enum {
  TC_SCHED_RR,
  TC_SCHED_PRIO,

  TC_SCHED_END
} tc_sch_e; 


typedef struct{
  uint32_t dummy;
//  tc_sch_t base;
} tc_sch_rr_t; 

typedef struct{
//  tc_sch_t base;
  uint32_t len_q_prio;
  uint32_t* q_prio;
} tc_sch_prio_t; 

void free_tc_ctrl_sch_prio(tc_sch_prio_t* prio);

tc_sch_prio_t cp_tc_sch_prio(tc_sch_prio_t const*);

bool eq_tc_sch_prio(tc_sch_prio_t const* m0, tc_sch_prio_t const* m1);



typedef struct{
  tc_sch_e type; 

  union{
    tc_sch_rr_t rr; 
    tc_sch_prio_t prio; 
  };

} tc_sch_t;


// Shaper
typedef struct{
  uint32_t id;
  uint32_t active;
  uint32_t max_rate_kbps;

// meter
  tc_mtr_t mtr;
} tc_shp_t;

typedef enum {
  TC_PCR_DUMMY,
  TC_PCR_5G_BDP,

  TC_PCR_END
} tc_pcr_e;

// Pacer
typedef struct {
  tc_pcr_e type;
  //float bndwdth_kbps; // -1 for no bandwidth
  uint32_t id;
  tc_mtr_t mtr; 

} tc_pcr_t ;

typedef struct {
  uint16_t rnti;
  uint16_t ue_id;
  uint16_t rb_id;

  // pipeline
  tc_sch_t sch;
  tc_pcr_t pcr;
  tc_cls_t cls;

  uint32_t len_q;
  tc_shp_t* shp;
  tc_plc_t* plc;
  tc_queue_t* q;
} tc_stats_t;

void free_tc_stats(tc_stats_t* src);

tc_stats_t cp_tc_stats(tc_stats_t const* src);

bool eq_tc_stats(tc_stats_t const* m0, tc_stats_t const* m1);

typedef struct {
  uint32_t len_tc_stats;
  tc_stats_t* tc_stats;
  int64_t tstamp;
} tc_ind_msg_t;

void free_tc_ind_msg(tc_ind_msg_t* src); 

tc_ind_msg_t cp_tc_ind_msg(tc_ind_msg_t const* src);

bool eq_tc_ind_msg(tc_ind_msg_t const* m0, tc_ind_msg_t const* m1);


//////////////////////////////////////
// RIC Call Process ID 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;
} tc_call_proc_id_t;

void free_tc_call_proc_id( tc_call_proc_id_t* src); 

tc_call_proc_id_t cp_tc_call_proc_id( tc_call_proc_id_t const* src);

bool eq_tc_call_proc_id(tc_call_proc_id_t* m0, tc_call_proc_id_t* m1);




//////////////////////////////////////
// RIC Control Header 
/////////////////////////////////////

typedef struct {
  uint16_t rnti;
  uint16_t rb_id;
} tc_ctrl_hdr_t;

void free_tc_ctrl_hdr( tc_ctrl_hdr_t* src); 

tc_ctrl_hdr_t cp_tc_ctrl_hdr(tc_ctrl_hdr_t const* src);

bool eq_tc_ctrl_hdr(tc_ctrl_hdr_t const* m0, tc_ctrl_hdr_t const* m1);


//////////////////////////////////////
// RIC Control Message 
/////////////////////////////////////


typedef enum{
  TC_CTRL_ACTION_SM_V0_ADD,
  TC_CTRL_ACTION_SM_V0_DEL,
  TC_CTRL_ACTION_SM_V0_MOD,

  TC_CTRL_ACTION_SM_V0_END
} tc_ctrl_act_e;


//////////////////////////
// RIC Control Message: CLASSIFIER
//////////////////////////

typedef struct{
  uint32_t dummy;
} tc_add_cls_rr_t; 

typedef struct{
  uint32_t dummy;
} tc_add_cls_sto_t; 

/*
typedef struct{
   flow_rules_t fr;
} tc_add_cls_dpi_t;

tc_add_cls_dpi_t cp_tc_add_cls_dpi(tc_add_cls_dpi_t const* src);

void free_tc_add_cls_dpi(tc_add_cls_dpi_t* src);
*/

typedef struct{
  L3_filter_t l3;
  L4_filter_t l4;
  L7_filter_t l7;

  int32_t dst_queue;
} tc_add_cls_osi_t;

tc_add_cls_osi_t cp_tc_add_cls_osi( tc_add_cls_osi_t const* src);

void free_tc_add_cls_osi(tc_add_cls_osi_t* src);

typedef struct{
  int32_t dst_queue;
  L3_filter_t l3;
  L4_filter_t l4;
  L7_filter_t l7;
} tc_add_cls_osi_dpi_t;

tc_add_cls_osi_dpi_t cp_tc_add_cls_osi_dpi(tc_add_cls_osi_dpi_t const* src);

void free_tc_add_cls_osi_dpi(tc_add_cls_osi_dpi_t* src);

typedef struct {
  tc_cls_e type;
  union {
    tc_add_cls_rr_t rr;
    tc_add_cls_sto_t sto;
    tc_add_cls_osi_t osi;
//   tc_add_cls_dpi_t dpi;
    tc_add_cls_osi_dpi_t osi_dpi;
  }; 
} tc_add_ctrl_cls_t ;

tc_add_ctrl_cls_t cp_tc_add_ctrl_cls(tc_add_ctrl_cls_t const* src);

void free_tc_add_ctrl_cls(tc_add_ctrl_cls_t* src);

typedef struct{
  uint32_t dummy;
} tc_mod_cls_rr_t;

typedef struct{ 
  uint32_t dummy;
} tc_mod_cls_sto_t;

typedef struct {
  tc_cls_osi_filter_t filter;
} tc_mod_cls_osi_t;

/*
typedef struct {
   flow_rules_t fr;
} tc_mod_cls_dpi_t;
*/

typedef struct {
 tc_cls_osi_dpi_filter_t flt;
} tc_mod_cls_osi_dpi_t;

typedef struct{
  tc_cls_e type;
  union {
    tc_mod_cls_rr_t rr;
    tc_mod_cls_sto_t sto;
    tc_mod_cls_osi_t osi;
    //tc_mod_cls_dpi_t dpi;
    tc_mod_cls_osi_dpi_t osi_dpi;
  }; 
} tc_mod_ctrl_cls_t ;

void free_tc_mod_ctrl_cls(tc_mod_ctrl_cls_t* src);

tc_mod_ctrl_cls_t cp_tc_mod_ctrl_cls(tc_mod_ctrl_cls_t const* src);

typedef struct{
  uint32_t dummy;
} tc_del_cls_rr_t;

typedef struct {
  uint32_t dummy;
} tc_del_cls_sto_t;

typedef struct{
  uint32_t filter_id;
} tc_del_cls_osi_t ;

/*
typedef struct{
  uint32_t filter_id;
  flow_rules_t fr;
} tc_del_cls_dpi_t;
tc_del_cls_dpi_t cp_tc_del_cls_dpi(tc_del_cls_dpi_t const* src);
*/

typedef struct{
  uint32_t filter_id;
} tc_del_cls_osi_dpi_t;

tc_del_cls_osi_dpi_t cp_tc_del_cls_osi_dpi(tc_del_cls_osi_dpi_t  const* src);

typedef struct 
{
  tc_cls_e type;
  union {
    tc_del_cls_rr_t rr;
    tc_del_cls_sto_t sto;
    tc_del_cls_osi_t osi;
    //tc_del_cls_dpi_t dpi;
    tc_del_cls_osi_dpi_t osi_dpi; 
  } ; 
} tc_del_ctrl_cls_t ;

void free_tc_del_ctrl_cls_t(tc_del_ctrl_cls_t* src); 

tc_del_ctrl_cls_t cp_tc_del_ctrl_cls(tc_del_ctrl_cls_t const* src);

typedef struct{
  tc_ctrl_act_e act;
  union{
    tc_add_ctrl_cls_t add;
    tc_mod_ctrl_cls_t mod;
    tc_del_ctrl_cls_t del;
  };
} tc_ctrl_cls_t;

tc_ctrl_cls_t cp_tc_ctrl_cls(tc_ctrl_cls_t const* src);

void free_tc_ctrl_cls(tc_ctrl_cls_t* cls);

//////////////////////////
// RIC Control Message: END CLASSIFIER
//////////////////////////


//////////////////////////
// RIC Control Message: POLICER
//////////////////////////

typedef struct{
  uint32_t dummy;
} tc_add_ctrl_plc_t;

typedef struct{
  uint32_t id;
  uint32_t drop_rate_kbps;  
  uint32_t dev_id;
  uint32_t dev_rate_kbps;  
  uint32_t active;
} tc_mod_ctrl_plc_t;

tc_mod_ctrl_plc_t cp_tc_mod_ctrl_plc(tc_mod_ctrl_plc_t const* src);
  
typedef struct{
  uint32_t id;
} tc_del_ctrl_plc_t; 

typedef struct{
  tc_ctrl_act_e act;
  union{
    tc_add_ctrl_plc_t add;
    tc_mod_ctrl_plc_t mod;
    tc_del_ctrl_plc_t del;
  };
} tc_ctrl_plc_t;

tc_ctrl_plc_t cp_tc_ctrl_plc(tc_ctrl_plc_t const* src);

//////////////////////////
// RIC Control Message: END POLICER
//////////////////////////

//////////////////////////
// RIC Control Message: QUEUE 
//////////////////////////

typedef struct{
  uint32_t dummy;
} tc_ctrl_queue_fifo_t;

typedef struct{
  uint32_t target_ms;
  uint32_t interval_ms; 
} tc_ctrl_queue_codel_t;

typedef struct{
  uint32_t target_ms;
  uint32_t interval_ms; 
} tc_ctrl_queue_ecn_codel_t;

typedef struct{
  tc_queue_e type;
   union{
      tc_ctrl_queue_fifo_t fifo;
      tc_ctrl_queue_codel_t codel;
      tc_ctrl_queue_ecn_codel_t ecn;
  };
} tc_add_ctrl_queue_t;

typedef struct{
  uint32_t id;
  tc_queue_e type;
   union{
      tc_ctrl_queue_fifo_t fifo;
      tc_ctrl_queue_codel_t codel;
      tc_ctrl_queue_ecn_codel_t ecn;
  };
} tc_mod_ctrl_queue_t;

typedef struct{
  uint32_t id;
  tc_queue_e type;
} tc_del_ctrl_queue_t;

typedef struct{
  tc_ctrl_act_e act;
  union{
   tc_add_ctrl_queue_t add;
   tc_mod_ctrl_queue_t mod;
   tc_del_ctrl_queue_t del;
  };
} tc_ctrl_queue_t; 

//////////////////////////
// RIC Control Message: END QUEUE
//////////////////////////

//////////////////////////
// RIC Control Message: SCHEDULER 
//////////////////////////

typedef struct{
  uint32_t dummy;
} tc_add_ctrl_sch_t;

typedef struct{
  tc_sch_e type;
  union{
    tc_sch_prio_t prio; 
    tc_sch_rr_t rr;
  };
} tc_mod_ctrl_sch_t;

void free_tc_mod_ctrl_sch(tc_mod_ctrl_sch_t* src);

tc_mod_ctrl_sch_t cp_tc_mod_ctrl_sch(tc_mod_ctrl_sch_t const* src);

typedef struct{
  uint32_t dummy;
} tc_del_ctrl_sch_t;

typedef struct{
  tc_ctrl_act_e act;
  union{
   tc_add_ctrl_sch_t add;
   tc_mod_ctrl_sch_t mod;
   tc_del_ctrl_sch_t del;
  };
} tc_ctrl_sch_t;

void free_tc_ctrl_sch(tc_ctrl_sch_t* sch);

//////////////////////////
// RIC Control Message: END SCHEDULER
//////////////////////////

//////////////////////////
// RIC Control Message: SHAPER 
//////////////////////////

typedef struct{
  uint32_t dummy;
} tc_add_ctrl_shp_t ;

typedef struct{
  uint32_t id;
  uint32_t time_window_ms; 
  uint32_t max_rate_kbps;
  uint32_t active;
} tc_mod_ctrl_shp_t ;

tc_mod_ctrl_shp_t cp_tc_mod_ctrl_shp(tc_mod_ctrl_shp_t const* );  

typedef struct{
  uint32_t id;
}tc_del_ctrl_shp_t;

typedef struct{
  tc_ctrl_act_e act;
  union{
    tc_add_ctrl_shp_t add;
    tc_mod_ctrl_shp_t mod;
    tc_del_ctrl_shp_t del;
  };
} tc_ctrl_shp_t;

tc_ctrl_shp_t cp_tc_ctrl_shp(tc_ctrl_shp_t const* src);

void free_tc_ctrl_shp(tc_ctrl_shp_t* shp);


//////////////////////////
// RIC Control Message: END SHAPER
//////////////////////////

//////////////////////////
// RIC Control Message: PACER 
//////////////////////////


typedef struct{
  uint32_t drb_sz;
  int64_t tstamp;
} tc_pcr_5g_bdp_t;

 tc_pcr_5g_bdp_t cp_tc_pcr_5g_bdp( tc_pcr_5g_bdp_t const* src);

typedef struct{
  uint32_t dummy;
} tc_pcr_dummy_t; 

typedef struct{
  uint32_t dummy;
} tc_add_ctrl_pcr_t; 

typedef struct{
  tc_pcr_e type;
  union{
    tc_pcr_5g_bdp_t bdp;
    tc_pcr_dummy_t dummy;
  };
} tc_mod_ctrl_pcr_t;

tc_mod_ctrl_pcr_t cp_tc_mod_ctrl_pcr(tc_mod_ctrl_pcr_t const* );

typedef struct{
  uint32_t dummy;
} tc_del_ctrl_pcr_t ;


typedef struct {
  tc_ctrl_act_e act;
  union{
    tc_add_ctrl_pcr_t add;
    tc_mod_ctrl_pcr_t mod;
    tc_del_ctrl_pcr_t del;
  };
} tc_ctrl_pcr_t;

//////////////////////////
// RIC Control Message: END PACER 
//////////////////////////


typedef enum{
  TC_CTRL_SM_V0_CLS,
  TC_CTRL_SM_V0_PLC,
  TC_CTRL_SM_V0_QUEUE,
  TC_CTRL_SM_V0_SCH,
  TC_CTRL_SM_V0_SHP,
  TC_CTRL_SM_V0_PCR,

  TC_CTRL_SM_V0_END
} tc_ctrl_msg_e;


typedef struct {
  tc_ctrl_msg_e type; 
  union{
      tc_ctrl_cls_t cls;
      tc_ctrl_plc_t plc;
      tc_ctrl_queue_t q;
      tc_ctrl_sch_t sch;
      tc_ctrl_shp_t shp;
      tc_ctrl_pcr_t pcr;
  };
} tc_ctrl_msg_t;

void free_tc_ctrl_msg( tc_ctrl_msg_t* src); 

tc_ctrl_msg_t cp_tc_ctrl_msg(tc_ctrl_msg_t const* src);

bool eq_tc_ctrl_msg(tc_ctrl_msg_t const* m0, tc_ctrl_msg_t const* m1);


//////////////////////////////////////
// RIC Control Outcome 
/////////////////////////////////////

typedef enum{
  TC_CTRL_OUT_OK,


  TC_CTRL_OUT_END
} tc_ctrl_out_e;

typedef struct {
  tc_ctrl_out_e out; 
//  uint32_t len_diag;
//  char* diagnostic; // human-readable diagnostic for northbound
} tc_ctrl_out_t;

void free_tc_ctrl_out(tc_ctrl_out_t* src); 

tc_ctrl_out_t cp_tc_ctrl_out(tc_ctrl_out_t const* src);

bool eq_tc_ctrl_out(tc_ctrl_out_t* m0, tc_ctrl_out_t* m1);



//////////////////////////////////////
// RAN Function Definition 
/////////////////////////////////////

typedef struct {
  uint8_t* buf;
  size_t len;
} tc_func_def_t;

void free_tc_func_def( tc_func_def_t* src); 

tc_func_def_t cp_tc_func_def(tc_func_def_t const* src);

bool eq_tc_func_def(tc_func_def_t const* m0, tc_func_def_t const* m1);



void tc_free_ind_msg(tc_ind_msg_t* msg);

void tc_free_ctrl_msg(tc_ctrl_msg_t* msg);

void tc_free_ctrl_out(tc_ctrl_out_t* out);

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
  tc_event_trigger_t et; 
  tc_action_def_t* ad;
} tc_sub_data_t;

///////////////
// RIC Indication
///////////////

typedef struct{
  tc_ind_hdr_t hdr;
  tc_ind_msg_t msg;
  tc_call_proc_id_t* proc_id;
} tc_ind_data_t;

void free_tc_ind_data(tc_ind_data_t* ind);

tc_ind_data_t cp_tc_ind_data(tc_ind_data_t const* src);


///////////////
// RIC Control
///////////////

typedef struct{
  tc_ctrl_hdr_t hdr;
  tc_ctrl_msg_t msg;
} tc_ctrl_req_data_t;

typedef struct{
  tc_ctrl_out_t* out;
} tc_ctrl_out_data_t;

///////////////
// E2 Setup
///////////////

typedef struct{
  tc_func_def_t func_def;
} tc_e2_setup_data_t;

///////////////
// RIC Service Update
///////////////

typedef struct{
  tc_func_def_t func_def;
} tc_ric_service_update_t;

#endif
