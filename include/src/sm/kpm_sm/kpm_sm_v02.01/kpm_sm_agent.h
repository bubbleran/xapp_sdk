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


#ifndef KPM_SERVICE_MODEL_AGENT_H
#define KPM_SERVICE_MODEL_AGENT_H

#include "../../sm_agent.h"

/**
 * Allocation of ServiceModel KPM agent data structure using the Factory Pattern from Service Model generic code ()
 * Cfr: flexric/src/sm/sm_agent.h). This function will need to be called by the main program in the agent component of 
 * the client/server architecture when it wants to load the service Model KPM.
 * Adhering to spec 'SM KPM v.2.02'
 * 
 * @param[in] io structure containing defintion of read/write functions to communicate with the RAN
 * @return the agent structure just created
 */

__attribute__ ((visibility ("default")))
sm_agent_t *make_kpm_sm_agent(sm_io_ag_ran_t const* io);

#endif
