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

#ifndef RLC_DATA_INFORMATION_ELEMENTS_H
#define RLC_DATA_INFORMATION_ELEMENTS_H

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
} rlc_event_trigger_t;

void free_rlc_event_trigger(rlc_event_trigger_t* src); 

rlc_event_trigger_t cp_rlc_event_trigger( rlc_event_trigger_t* src);

bool eq_rlc_event_trigger(rlc_event_trigger_t* m0, rlc_event_trigger_t* m1);



//////////////////////////////////////
// RIC Action Definition 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;  
} rlc_action_def_t;

void free_rlc_action_def(rlc_action_def_t* src); 

rlc_action_def_t cp_rlc_action_def(rlc_action_def_t* src);

bool eq_rlc_action_def(rlc_event_trigger_t* m0,  rlc_event_trigger_t* m1);



//////////////////////////////////////
// RIC Indication Header 
/////////////////////////////////////

typedef struct{
  uint32_t dummy;  
} rlc_ind_hdr_t;

void free_rlc_ind_hdr(rlc_ind_hdr_t* src); 

rlc_ind_hdr_t cp_rlc_ind_hdr(rlc_ind_hdr_t const* src);

bool eq_rlc_ind_hdr(rlc_ind_hdr_t* m0, rlc_ind_hdr_t* m1);


//////////////////////////////////////
// RIC Indication Message 
/////////////////////////////////////

typedef struct {
  /* PDU stats */
  /* TX */
  uint32_t txpdu_pkts;         /* aggregated number of transmitted RLC PDUs */
  uint32_t txpdu_bytes;        /* aggregated amount of transmitted bytes in RLC PDUs */
  uint32_t txpdu_wt_ms;        /* TODO: aggregated head-of-line tx packet waiting time to be transmitted (i.e. send to the MAC layer) */
  uint32_t txpdu_dd_pkts;      /* aggregated number of dropped or discarded tx packets by RLC */
  uint32_t txpdu_dd_bytes;     /* aggregated amount of bytes dropped or discarded tx packets by RLC */
  uint32_t txpdu_retx_pkts;    /* aggregated number of tx pdus/pkts to be re-transmitted (only applicable to RLC AM) */
  uint32_t txpdu_retx_bytes;   /* aggregated amount of bytes to be re-transmitted (only applicable to RLC AM) */
  uint32_t txpdu_segmented;    /* aggregated number of segmentations */
  uint32_t txpdu_status_pkts;  /* aggregated number of tx status pdus/pkts (only applicable to RLC AM) */
  uint32_t txpdu_status_bytes; /* aggregated amount of tx status bytes  (only applicable to RLC AM) */
  uint32_t txbuf_occ_bytes;    /* (IMPLEMENTED) transmitting bytes currently in buffer */
  uint32_t txbuf_occ_pkts;     /* TODO: current tx buffer occupancy in terms of number of packets (average: NOT IMPLEMENTED) */

  /* txbuf_wd_ms: the time window for which the txbuf  occupancy value is obtained - NOT IMPLEMENTED */

  /* RX */
  uint32_t rxpdu_pkts;         /* aggregated number of received RLC PDUs */
  uint32_t rxpdu_bytes;        /* amount of bytes received by the RLC */
  uint32_t rxpdu_dup_pkts;     /* aggregated number of duplicate packets */
  uint32_t rxpdu_dup_bytes;    /* aggregated amount of duplicated bytes */
  uint32_t rxpdu_dd_pkts;      /* aggregated number of rx packets dropped or discarded by RLC */
  uint32_t rxpdu_dd_bytes;     /* aggregated amount of rx bytes dropped or discarded by RLC */
  uint32_t rxpdu_ow_pkts;      /* aggregated number of out of window received RLC pdu */
  uint32_t rxpdu_ow_bytes;     /* aggregated number of out of window bytes received RLC pdu */
  uint32_t rxpdu_status_pkts;  /* aggregated number of rx status pdus/pkts (only applicable to RLC AM) */
  uint32_t rxpdu_status_bytes; /* aggregated amount of rx status bytes  (only applicable to RLC AM) */
  /* rxpdu_rotout_ms: flag indicating rx reordering  timeout in ms - NOT IMPLEMENTED */
  /* rxpdu_potout_ms: flag indicating the poll retransmit time out in ms - NOT IMPLEMENTED */
  /* rxpdu_sptout_ms: flag indicating status prohibit timeout in ms - NOT IMPLEMENTED */
  uint32_t rxbuf_occ_bytes;    /* (IMPLEMENTED) received bytes currently in buffer */
  uint32_t rxbuf_occ_pkts;     /* TODO: current rx buffer occupancy in terms of number of packets (average: NOT IMPLEMENTED) */


  /* SDU stats */
  /* TX */
  uint32_t txsdu_pkts;         /* number of SDUs delivered */
  uint64_t txsdu_bytes;        /* (UPDATED) number of SDUs bytes successfully transmitted so far (counter) */
  /* Average time for an SDU to be passed to MAC:
   * Actually measures the time it takes for THE FULL SDU to be passed to MAC FOR THE FIRST TIME.
   * Since the MAC schedules in advance, it does not measure the time of
   * transmission over the air, just the time to reach the MAC layer.
   * => to control it, 'txsdu_hol_waittime' that measures the current HOL-delay is added.
   */
  double txsdu_avg_time_to_tx; /* (100ms-windowed) per-packet sojourn (SDU to PDU) in microseconds */
  uint32_t txsdu_wt_us;        /* HOL delay of the current radio bearer, in microseconds */


  /* RX */
  uint32_t rxsdu_pkts;         /* number of SDUs received */
  uint64_t rxsdu_bytes;        /* (UPDATED) number of SDUs bytes arrived so far (counter) */
  uint32_t rxsdu_dd_pkts;      /* number of dropped or discarded SDUs */
  uint32_t rxsdu_dd_bytes;     /* number of bytes of SDUs dropped or discarded */

  uint32_t rnti;
  uint8_t mode;               /* 0: RLC AM, 1: RLC UM, 2: RLC TM */
  uint8_t rbid;

} rlc_radio_bearer_stats_t;

typedef struct {
  rlc_radio_bearer_stats_t* rb; 
  uint32_t len;

  int64_t tstamp;
} rlc_ind_msg_t;

void free_rlc_ind_msg(rlc_ind_msg_t* src); 

rlc_ind_msg_t cp_rlc_ind_msg(rlc_ind_msg_t const* src);

bool eq_rlc_ind_msg(rlc_ind_msg_t* m0, rlc_ind_msg_t* m1);


//////////////////////////////////////
// RIC Call Process ID 
/////////////////////////////////////

typedef struct {
  uint32_t dummy;
} rlc_call_proc_id_t;

void free_rlc_call_proc_id( rlc_call_proc_id_t* src); 

rlc_call_proc_id_t cp_rlc_call_proc_id( rlc_call_proc_id_t* src);

bool eq_rlc_call_proc_id(rlc_call_proc_id_t* m0, rlc_call_proc_id_t* m1);



//////////////////////////////////////
// RIC Control Header 
/////////////////////////////////////


typedef struct {
  uint32_t dummy;
} rlc_ctrl_hdr_t;

void free_rlc_ctrl_hdr( rlc_ctrl_hdr_t* src); 

rlc_ctrl_hdr_t cp_rlc_ctrl_hdr(rlc_ctrl_hdr_t* src);

bool eq_rlc_ctrl_hdr(rlc_ctrl_hdr_t* m0, rlc_ctrl_hdr_t* m1);



//////////////////////////////////////
// RIC Control Message 
/////////////////////////////////////


typedef struct {
  uint32_t action;
} rlc_ctrl_msg_t;

void free_rlc_ctrl_msg( rlc_ctrl_msg_t* src); 

rlc_ctrl_msg_t cp_rlc_ctrl_msg(rlc_ctrl_msg_t* src);

bool eq_rlc_ctrl_msg(rlc_ctrl_msg_t* m0, rlc_ctrl_msg_t* m1);



//////////////////////////////////////
// RIC Control Outcome 
/////////////////////////////////////

typedef enum{
  RLC_CTRL_OUT_OK,

  RLC_CTRL_OUT_END
} rlc_ctrl_out_e;


typedef struct {
  rlc_ctrl_out_e ans;
} rlc_ctrl_out_t;

void free_rlc_ctrl_out(rlc_ctrl_out_t* src); 

rlc_ctrl_out_t cp_rlc_ctrl_out(rlc_ctrl_out_t* src);

bool eq_rlc_ctrl_out(rlc_ctrl_out_t* m0, rlc_ctrl_out_t* m1);


//////////////////////////////////////
// RAN Function Definition 
/////////////////////////////////////

typedef struct {
  uint8_t* buf;
  size_t len;
} rlc_func_def_t;

void free_rlc_func_def( rlc_func_def_t* src); 

rlc_func_def_t cp_rlc_func_def(rlc_func_def_t const* src);

bool eq_rlc_func_def(rlc_func_def_t const* m0, rlc_func_def_t const* m1);

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
  rlc_event_trigger_t et; 
  rlc_action_def_t* ad;
} rlc_sub_data_t;

///////////////
// RIC Indication
///////////////

typedef struct{
  rlc_ind_hdr_t hdr;
  rlc_ind_msg_t msg;
  rlc_call_proc_id_t* proc_id;
} rlc_ind_data_t;

void free_rlc_ind_data(rlc_ind_data_t* ind);

rlc_ind_data_t cp_rlc_ind_data(rlc_ind_data_t const* src);

///////////////
// RIC Control
///////////////

typedef struct{
  rlc_ctrl_hdr_t hdr;
  rlc_ctrl_msg_t msg;
} rlc_ctrl_req_data_t;

typedef struct{
  rlc_ctrl_out_t* out;
} rlc_ctrl_out_data_t;

///////////////
// E2 Setup
///////////////

typedef struct{
  rlc_func_def_t func_def;
} rlc_e2_setup_data_t;

///////////////
// RIC Service Update
///////////////

typedef struct{
  rlc_func_def_t func_def;
} rlc_ric_service_update_t;


#ifdef __cplusplus
}
#endif

#endif

