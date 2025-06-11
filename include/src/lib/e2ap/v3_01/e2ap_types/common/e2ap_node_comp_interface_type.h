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


#ifndef E2AP_NODE_COMP_INTERFACE_TYPE_MIR_H
#define E2AP_NODE_COMP_INTERFACE_TYPE_MIR_H

// 9.2.26
typedef enum{
  NG_E2AP_NODE_COMP_INTERFACE_TYPE = 0, 
  XN_E2AP_NODE_COMP_INTERFACE_TYPE = 1, 
  E1_E2AP_NODE_COMP_INTERFACE_TYPE = 2,
  F1_E2AP_NODE_COMP_INTERFACE_TYPE = 3, 
  W1_E2AP_NODE_COMP_INTERFACE_TYPE = 4, 
  S1_E2AP_NODE_COMP_INTERFACE_TYPE = 5, 
  X2_E2AP_NODE_COMP_INTERFACE_TYPE = 6,

  END_E2AP_NODE_COMP_INTERFACE_TYPE
} e2ap_node_comp_interface_type_e;

#endif
