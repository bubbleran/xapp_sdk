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
 

#ifndef E2_NODE_ARR_XAPP_H
#define E2_NODE_ARR_XAPP_H 

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "e2_node_connected_xapp.h"

typedef struct{
  uint8_t len;
  e2_node_connected_xapp_t* n;
} e2_node_arr_xapp_t;

void free_e2_node_arr_xapp(e2_node_arr_xapp_t*);

#ifdef __cplusplus
}
#endif

#endif

