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



#ifndef E2AP_MSG_FREE_H
#define E2AP_MSG_FREE_H

#include "../type_defs.h"


///////////////////////////////////////////////////////////////////////////////////////////////////
// O-RAN E2APv01.01: Messages for Global Procedures ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
// RIC -> E2
void e2ap_free_subscription_request_msg(e2ap_msg_t* msg);
void e2ap_free_subscription_request(ric_subscription_request_t* sr);

// E2 -> RIC 
void e2ap_free_subscription_response_msg(e2ap_msg_t* msg);
void e2ap_free_subscription_response(ric_subscription_response_t* sr);

//E2 -> RIC 
void e2ap_free_subscription_failure_msg(e2ap_msg_t* msg);
void e2ap_free_subscription_failure(ric_subscription_failure_t* sf);

//RIC -> E2
void e2ap_free_subscription_delete_request_msg(e2ap_msg_t* msg);
void e2ap_free_subscription_delete_request(ric_subscription_delete_request_t* dr);

// E2 -> RIC
void e2ap_free_subscription_delete_response_msg(e2ap_msg_t* msg);
void e2ap_free_subscription_delete_response(ric_subscription_delete_response_t* dr);

//E2 -> RIC
void e2ap_free_subscription_delete_failure_msg(e2ap_msg_t* msg);
void e2ap_free_subscription_delete_failure(ric_subscription_delete_failure_t* df);

// E2 -> RIC
void e2ap_free_indication_msg(e2ap_msg_t* msg);
void e2ap_free_indication(ric_indication_t* ind);

// RIC -> E2
void e2ap_free_control_request_msg(e2ap_msg_t* msg);
void e2ap_free_control_request(ric_control_request_t* ric_req);

// E2 -> RIC
void e2ap_free_control_ack_msg(e2ap_msg_t* msg);
void e2ap_free_control_ack(ric_control_acknowledge_t* c_ack);

// E2 -> RIC
void e2ap_free_control_failure_msg(e2ap_msg_t* msg);
void e2ap_free_control_failure(ric_control_failure_t* cf); 
  

///////////////////////////////////////////////////////////////////////////////////////////////////
// O-RAN E2APv01.01: Messages for Global Procedures ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// RIC <-> E2 
void e2ap_free_error_indication_msg(e2ap_msg_t* msg);
void e2ap_free_error_indication(e2ap_error_indication_t* ei);

// E2 -> RIC
void e2ap_free_setup_request_msg(e2ap_msg_t* msg);
void e2ap_free_setup_request(e2_setup_request_t* sr);

// RIC -> E2
void e2ap_free_setup_response_msg(e2ap_msg_t* msg);
void e2ap_free_setup_response(e2_setup_response_t* sr);

// RIC -> E2
void e2ap_free_setup_failure_msg(e2ap_msg_t* msg);
void e2ap_free_setup_failure(e2_setup_failure_t* sf);

// RIC <-> E2
void e2ap_free_reset_request_msg(e2ap_msg_t* msg);
void e2ap_free_reset_request(e2ap_reset_request_t* rr);

// RIC <-> E2
void e2ap_free_reset_response_msg(e2ap_msg_t* msg);
void e2ap_free_reset_response(e2ap_reset_response_t* rr);
  
// E2 -> RIC
void e2ap_free_service_update_msg(e2ap_msg_t* msg);
void e2ap_free_service_update(ric_service_update_t* su);

// RIC -> E2
void e2ap_free_service_update_ack_msg(e2ap_msg_t* msg);
void e2ap_free_service_update_ack(ric_service_update_ack_t* su);

// RIC -> E2
void e2ap_free_service_update_failure_msg(e2ap_msg_t* msg);
void e2ap_free_service_update_failure(ric_service_update_failure_t* uf);

// RIC -> E2
void e2ap_free_service_query_msg(e2ap_msg_t* msg);
void e2ap_free_service_query(ric_service_query_t* sq);

// E2 -> RIC
void e2ap_free_node_configuration_update_msg(e2ap_msg_t* msg);
void e2ap_free_node_configuration_update(e2_node_configuration_update_t* cu);


// RIC -> E2
void e2ap_free_node_configuration_update_ack_msg(e2ap_msg_t* msg);
void e2ap_free_node_configuration_update_ack(e2_node_configuration_update_ack_t* cua);

// RIC -> E2
void e2ap_free_node_configuration_update_failure_msg(e2ap_msg_t* msg);
void e2ap_free_node_configuration_update_failure(e2_node_configuration_update_failure_t* cuf);

// RIC -> E2
void e2ap_free_node_connection_update_msg(e2ap_msg_t* msg);
void e2ap_free_node_connection_update(e2_node_connection_update_t* cu);

// E2 -> RIC
void e2ap_free_node_connection_update_ack_msg(e2ap_msg_t* msg);
void e2ap_free_node_connection_update_ack(e2_node_connection_update_ack_t* ca);

// E2 -> RIC
void e2ap_free_node_connection_update_failure_msg(e2ap_msg_t* msg);
void e2ap_free_node_connection_update_failure(e2_node_connection_update_failure_t* cf);

// xApp -> iApp
void e2ap_free_e42_setup_request_msg(e2ap_msg_t* msg);
void e2ap_free_e42_setup_request(e42_setup_request_t* sr);

// xApp -> iApp
void e2ap_free_e42_setup_response_msg(e2ap_msg_t* msg);
void e2ap_free_e42_setup_response(e42_setup_response_t* sr);

// xApp -> iApp
void e2ap_free_e42_ric_subscription_request_msg(e2ap_msg_t* msg);
void e2ap_free_e42_ric_subscription_request(e42_ric_subscription_request_t* sr);

// xApp -> iApp
void e2ap_free_e42_ric_subscription_delete_request_msg(e2ap_msg_t* msg);
void e2ap_free_e42_ric_subscription_delete_request(e42_ric_subscription_delete_request_t* e42_sr);

// xApp -> iApp
void e2ap_free_e42_ric_control_request_msg(e2ap_msg_t* msg);
void e2ap_free_e42_ric_control_request(e42_ric_control_request_t* ctrl);

// xApp -> iApp
void e2ap_free_e42_update_e2_node_msg(e2ap_msg_t* msg);
//void e2ap_free_e42_update_e2_node(e42_update_e2_node_t* sr);

#endif

