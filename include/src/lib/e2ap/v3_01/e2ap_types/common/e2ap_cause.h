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


#ifndef E2AP_CAUSE_H
#define E2AP_CAUSE_H

#include <stdbool.h>

typedef enum {
	CAUSE_NOTHING,	/* NO COMPONENTS PRESENT */
	CAUSE_RICREQUEST,
	CAUSE_RICSERVICE,
  CAUSE_E2NODE,
	CAUSE_TRANSPORT,
	CAUSE_PROTOCOL,
	CAUSE_MISC
} cause_e;

typedef enum {

  CAUSE_RIC_RAN_FUNCTION_ID_INVALID = 0,
  CAUSE_RIC_ACTION_NOT_SUPPORTED = 1,
  CAUSE_RIC_EXCESSIVE_ACTIONS = 2,
  CAUSE_RIC_DUPLICATE_ACTION = 3,
  CAUSE_RIC_DUPLICATE_EVENT_TRIGGER = 4,
  CAUSE_RIC_FUNCTION_RESOURCE_LIMIT = 5,
  CAUSE_RIC_REQUEST_ID_UNKNOWN = 6,
  CAUSE_RIC_INCONSISTENT_ACTION_SUBSEQUENT_ACTION_SEQUENCE = 7,
  CAUSE_RIC_CONTROL_MESSAGE_INVALID = 8,
  CAUSE_RIC_CALL_PROCESS_ID_INVALID = 9,
  CAUSE_RIC_CONTROL_TIMER_EXPIRED = 10,
  CAUSE_RIC_CONTROL_FAILED_TO_EXECUTE = 11,
  CAUSE_RIC_SYSTEM_NOT_READY = 12,
  CAUSE_RIC_UNSPECIFIED = 13
} cause_RIC_e;

typedef enum {
	CAUSE_RICSERVICE_FUNCTION_NOT_REQUIRED	= 0,
	CAUSE_RICSERVICE_EXCESSIVE_FUNCTIONS	= 1,
	CAUSE_RICSERVICE_RIC_RESOURCE_LIMIT	= 2
} cause_RIC_service_e;

typedef enum{
  CAUSE_E2NODE_COMPONENT_UNKNOWN = 0
} cause_e2node_e;

typedef enum {
	CAUSE_TRANSPORT_UNSPECIFIED	= 0,
	CAUSE_TRANSPORT_TRANSPORT_RESOURCE_UNAVAILABLE	= 1
} cause_transport_e;

typedef enum {
	CAUSE_PROTOCOL_TRANSFER_SYNTAX_ERROR	= 0,
	CAUSE_PROTOCOL_ABSTRACT_SYNTAX_ERROR_REJECT	= 1,
	CAUSE_PROTOCOL_ABSTRACT_SYNTAX_ERROR_IGNORE_AND_NOTIFY	= 2,
	CAUSE_PROTOCOL_MESSAGE_NOT_COMPATIBLE_WITH_RECEIVER_STATE	= 3,
	CAUSE_PROTOCOL_SEMANTIC_ERROR	= 4,
	CAUSE_PROTOCOL_ABSTRACT_SYNTAX_ERROR_FALSELY_CONSTRUCTED_MESSAGE	= 5,
	CAUSE_PROTOCOL_UNSPECIFIED	= 6
} cause_protocol_e;

typedef enum {
	CAUSE_MISC_CONTROL_PROCESSING_OVERLOAD	= 0,
	CAUSE_MISC_HARDWARE_FAILURE	= 1,
	CAUSE_MISC_OM_INTERVENTION	= 2,
	CAUSE_MISC_UNSPECIFIED	= 3
} cause_misc_e;

/* Cause */
typedef struct {
	 cause_e present;
	union {
		cause_RIC_e	ricRequest;
		cause_RIC_service_e ricService;
    cause_e2node_e e2Node;
		cause_transport_e	transport;
		cause_protocol_e protocol;
		cause_misc_e	misc;
		};
} cause_t;

bool eq_cause(const cause_t* m0, const cause_t* m1);

cause_t cp_cause(cause_t const* src);

#endif
