/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef CCC_DATA_INFORMATION_ELEMENTS_H
#define CCC_DATA_INFORMATION_ELEMENTS_H

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

#include "ir/e2sm_ccc_ev_trg_frmt_1.h"
#include "ir/e2sm_ccc_ev_trg_frmt_2.h"
#include "ir/e2sm_ccc_ev_trg_frmt_3.h"


//////////////////////////////////////
// RIC Action Definition 
/////////////////////////////////////

#include "ir/e2sm_ccc_act_def_frmt_1.h"
#include "ir/e2sm_ccc_act_def_frmt_2.h"

/////////////////////////////////////
// RIC Indication Header 
/////////////////////////////////////

#include "ir/e2sm_ccc_ind_hdr_frmt_1.h"

/////////////////////////////////////
// RIC Indication Message 
/////////////////////////////////////

#include "ir/e2sm_ccc_ind_msg_frmt_1.h"
#include "ir/e2sm_ccc_ind_msg_frmt_2.h"

/////////////////////////////////////
// RIC Control Header 
/////////////////////////////////////

#include "ir/e2sm_ccc_ctrl_hdr_frmt_1.h"

/////////////////////////////////////
// RIC Control Message 
/////////////////////////////////////

#include "ir/e2sm_ccc_ctrl_msg_frmt_1.h"
#include "ir/e2sm_ccc_ctrl_msg_frmt_2.h"

/////////////////////////////////////
// RIC Control Outcome 
/////////////////////////////////////

#include "ir/e2sm_ccc_ctrl_out_frmt_1.h"
#include "ir/e2sm_ccc_ctrl_out_frmt_2.h"

/////////////////////////////////////
// RAN Function Definition 
/////////////////////////////////////

#include "../../../lib/sm/ie/ran_function_name.h"
#include "ir/supported_services.h"
#include "ir/func_def_ran_conf.h"

//////////////////////////////////////
// RIC Event Trigger Definition
/////////////////////////////////////

typedef enum{
  FORMAT_1_E2SM_CCC_EV_TRIGGER_FORMAT ,
  FORMAT_2_E2SM_CCC_EV_TRIGGER_FORMAT ,
  FORMAT_3_E2SM_CCC_EV_TRIGGER_FORMAT ,

  END_E2SM_CCC_EV_TRIGGER_FORMAT
} e2sm_ccc_ev_trigger_format_e ;

typedef struct {
  e2sm_ccc_ev_trigger_format_e format;
  union{
    e2sm_ccc_ev_trg_frmt_1_t frmt_1; // 9.2.1.1.1
    e2sm_ccc_ev_trg_frmt_2_t frmt_2; // 9.2.1.1.2
    e2sm_ccc_ev_trg_frmt_3_t frmt_3; // 9.2.1.1.3
  };
} e2sm_ccc_event_trigger_t;

void free_e2sm_ccc_event_trigger(e2sm_ccc_event_trigger_t* src);

e2sm_ccc_event_trigger_t cp_e2sm_ccc_event_trigger(e2sm_ccc_event_trigger_t const* src);

bool eq_e2sm_ccc_event_trigger(e2sm_ccc_event_trigger_t const* m0, e2sm_ccc_event_trigger_t const* m1);


//////////////////////////////////////
// RIC Action Definition 
/////////////////////////////////////

typedef enum{
  FORMAT_1_E2SM_CCC_ACT_DEF,
  FORMAT_2_E2SM_CCC_ACT_DEF,

  END_E2SM_CCC_ACT_DEF

} e2sm_ccc_act_def_format_e;

typedef struct {
  //  RIC Style Type
  //  Mandatory
  //  9.3.3
  //  Defined in common 6.2.2.2.
  uint32_t ric_style_type; 

  e2sm_ccc_act_def_format_e format;
  union{
    e2sm_ccc_act_def_frmt_1_t frmt_1; // 9.2.1.2.1
    e2sm_ccc_act_def_frmt_2_t frmt_2; // 9.2.1.2.2
  };
} e2sm_ccc_action_def_t;

void free_e2sm_ccc_action_def(e2sm_ccc_action_def_t* src);

e2sm_ccc_action_def_t cp_e2sm_ccc_action_def(e2sm_ccc_action_def_t const* src);

bool eq_e2sm_ccc_action_def(e2sm_ccc_action_def_t* m0,  e2sm_ccc_action_def_t* m1);



//////////////////////////////////////
// RIC Indication Header 
/////////////////////////////////////

typedef enum{
  FORMAT_1_E2SM_CCC_IND_HDR ,

  END_E2SM_CCC_IND_HDR
} e2sm_ccc_ind_hdr_format_e;

typedef struct{
  e2sm_ccc_ind_hdr_format_e format;
  union{
    e2sm_ccc_ind_hdr_frmt_1_t frmt_1; // 9.2.1.3.1
  };
} e2sm_ccc_ind_hdr_t;

void free_e2sm_ccc_ind_hdr(e2sm_ccc_ind_hdr_t* src);

e2sm_ccc_ind_hdr_t cp_e2sm_ccc_ind_hdr(e2sm_ccc_ind_hdr_t const* src);

bool eq_e2sm_ccc_ind_hdr(e2sm_ccc_ind_hdr_t const* m0, e2sm_ccc_ind_hdr_t const* m1);


//////////////////////////////////////
// RIC Indication Message 
/////////////////////////////////////

typedef enum{
  FORMAT_1_E2SM_CCC_IND_MSG ,
  FORMAT_2_E2SM_CCC_IND_MSG ,

  END_E2SM_CCC_IND_MSG

} e2sm_ccc_ind_msg_format_e ;


// 9.2.1.4
typedef struct {
  e2sm_ccc_ind_msg_format_e format;
  union{
    e2sm_ccc_ind_msg_frmt_1_t frmt_1; // 9.2.1.4.1
    e2sm_ccc_ind_msg_frmt_2_t frmt_2; // 9.2.1.4.2
  };

} e2sm_ccc_ind_msg_t;

void free_e2sm_ccc_ind_msg(e2sm_ccc_ind_msg_t* src);

e2sm_ccc_ind_msg_t cp_e2sm_ccc_ind_msg(e2sm_ccc_ind_msg_t const* src);

bool eq_e2sm_ccc_ind_msg(e2sm_ccc_ind_msg_t const* m0, e2sm_ccc_ind_msg_t const* m1);


//////////////////////////////////////
// RIC Call Process ID 
/////////////////////////////////////

// 7.6.2.4	CONTROL Service RIC Call Process ID IE contents
typedef struct {
  // Empty
  uint32_t dummy;
} e2sm_ccc_cpid_t;

void free_e2sm_ccc_cpid(e2sm_ccc_cpid_t* src);

e2sm_ccc_cpid_t cp_e2sm_ccc_cpid(e2sm_ccc_cpid_t const* src);

bool eq_e2sm_ccc_cpid(e2sm_ccc_cpid_t const* m0, e2sm_ccc_cpid_t const* m1);


//////////////////////////////////////
// RIC Control Header 
/////////////////////////////////////

typedef enum{
  FORMAT_1_E2SM_CCC_CTRL_HDR,

  END_E2SM_CCC_CTRL_HDR,
} e2sm_ccc_ctrl_hdr_e;

typedef struct {
  e2sm_ccc_ctrl_hdr_e format;
  union{
    e2sm_ccc_ctrl_hdr_frmt_1_t frmt_1; // 9.2.1.6.1
  };
} e2sm_ccc_ctrl_hdr_t;

void free_e2sm_ccc_ctrl_hdr( e2sm_ccc_ctrl_hdr_t* src);

e2sm_ccc_ctrl_hdr_t cp_e2sm_ccc_ctrl_hdr(e2sm_ccc_ctrl_hdr_t const* src);

bool eq_e2sm_ccc_ctrl_hdr(e2sm_ccc_ctrl_hdr_t const* m0, e2sm_ccc_ctrl_hdr_t const* m1);


//////////////////////////////////////
// RIC Control Message 
/////////////////////////////////////

typedef enum{
  FORMAT_1_E2SM_CCC_CTRL_MSG,
  FORMAT_2_E2SM_CCC_CTRL_MSG,
  END_E2SM_CCC_CTRL_MSG,
} e2sm_ccc_ctrl_msg_e;


typedef struct {
  e2sm_ccc_ctrl_msg_e format;
  union{
    e2sm_ccc_ctrl_msg_frmt_1_t frmt_1; // 9.2.1.7.1
    e2sm_ccc_ctrl_msg_frmt_2_t frmt_2; // 9.2.1.7.2
  };
} e2sm_ccc_ctrl_msg_t;

void free_e2sm_ccc_ctrl_msg(e2sm_ccc_ctrl_msg_t* src);

e2sm_ccc_ctrl_msg_t cp_e2sm_ccc_ctrl_msg(e2sm_ccc_ctrl_msg_t const* src);

bool eq_e2sm_ccc_ctrl_msg(e2sm_ccc_ctrl_msg_t const* m0, e2sm_ccc_ctrl_msg_t const* m1);



//////////////////////////////////////
// RIC Control Outcome 
/////////////////////////////////////

typedef enum{
  FORMAT_1_E2SM_CCC_CTRL_OUT,
  FORMAT_2_E2SM_CCC_CTRL_OUT,
  END_E2SM_CCC_CTRL_OUT,
} e2sm_ccc_ctrl_out_e;

typedef struct {
  e2sm_ccc_ctrl_out_e format;
  union{
     e2sm_ccc_ctrl_out_frmt_1_t frmt_1; // 9.2.1.8.1
     e2sm_ccc_ctrl_out_frmt_2_t frmt_2; // 9.2.1.8.2
  };
} e2sm_ccc_ctrl_out_t;

void free_e2sm_ccc_ctrl_out(e2sm_ccc_ctrl_out_t* src);

e2sm_ccc_ctrl_out_t cp_e2sm_ccc_ctrl_out( e2sm_ccc_ctrl_out_t const* src);

bool eq_e2sm_ccc_ctrl_out(e2sm_ccc_ctrl_out_t const* m0, e2sm_ccc_ctrl_out_t const* m1);


//////////////////////////////////////
// RAN Function Definition 
/////////////////////////////////////

typedef struct {
  // Cell global id
  // Mandatory
  // 9.3.6
  cell_global_id_t cell_global_id;

  // List of Supported Cell-level RAN Configuration Structures
  // [0..1024]
  size_t sz_func_def_ran_conf;
  func_def_ran_conf_t* func_def_ran_conf;

} func_def_cells_t;

typedef struct {
  //  RAN Function Name
  //  Mandatory
  //  9.3.2
  //  9.2.2.1.
  ran_function_name_t name;

  //  List of supported Node-level RAN configuration Structures
  //  [0..1024]
  size_t sz_func_def_ran_conf;
  func_def_ran_conf_t* func_def_ran_conf;

  // List of cells
  // [0..1024]
  size_t sz_func_def_cells;
  func_def_cells_t* func_def_cells;

} e2sm_ccc_func_def_t;

void free_e2sm_ccc_func_def( e2sm_ccc_func_def_t* src);

e2sm_ccc_func_def_t cp_e2sm_ccc_func_def(e2sm_ccc_func_def_t const* src);

bool eq_e2sm_ccc_func_def(e2sm_ccc_func_def_t const* m0, e2sm_ccc_func_def_t const* m1);

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
  e2sm_ccc_event_trigger_t et;

  // O-RAN.WG3.E2AP
  // 9.1.1.1
  // [1-16]
  size_t sz_ad;
  e2sm_ccc_action_def_t* ad;
} ccc_sub_data_t;

void free_ccc_sub_data(ccc_sub_data_t* ind);

bool eq_ccc_sub_data(ccc_sub_data_t const* m0, ccc_sub_data_t const* m1);

ccc_sub_data_t cp_ccc_sub_data(ccc_sub_data_t const* src);

///////////////
// RIC Indication
///////////////

typedef struct{
  e2sm_ccc_ind_hdr_t hdr;
  e2sm_ccc_ind_msg_t msg;
} ccc_ind_data_t;

void free_ccc_ind_data(ccc_ind_data_t* ind);

bool eq_ccc_ind_data(ccc_ind_data_t const* m0, ccc_ind_data_t const* m1);

ccc_ind_data_t cp_ccc_ind_data(ccc_ind_data_t const* src);

///////////////
// RIC Control
///////////////

typedef struct{
  e2sm_ccc_ctrl_hdr_t hdr;
  e2sm_ccc_ctrl_msg_t msg;
} ccc_ctrl_req_data_t;

void free_ccc_ctrl_req_data(ccc_ctrl_req_data_t* src);

bool eq_ccc_ctrl_req_data(ccc_ctrl_req_data_t const* m0, ccc_ctrl_req_data_t  const* m1);

ccc_ctrl_req_data_t cp_ccc_ctrl_req_data(ccc_ctrl_req_data_t const* src);


typedef struct{
  e2sm_ccc_ctrl_out_t* out;
} ccc_ctrl_out_data_t;

///////////////
// E2 Setup
///////////////

typedef struct{
  e2sm_ccc_func_def_t ran_func_def;
} ccc_e2_setup_t;

///////////////
// RIC Service Update
///////////////

typedef struct{
  e2sm_ccc_func_def_t func_def;
} ccc_ric_service_update_t;


#ifdef __cplusplus
}
#endif

#endif

