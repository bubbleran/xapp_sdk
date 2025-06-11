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


#ifndef E2_NODE_CONNECTION_UPDATE_ACK_H
#define E2_NODE_CONNECTION_UPDATE_ACK_H 

#include "common/e2ap_connection_update_item.h"
#include "common/e2ap_connection_setup_failed.h"

typedef struct{
  e2_connection_update_item_t* setup;
  size_t len_setup;

  e2_connection_setup_failed_t* failed;
  size_t len_failed;

} e2_node_connection_update_ack_t;


#endif

