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

#include "../include/src/xApp/e42_xapp_api.h"
#include "../include/src/util/alg_ds/alg/defer.h"
#include "../include/src/util/e2ap_ngran_types.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  assert(argc == 2 && "Configuration file needed. i.e., ./hw conf.yaml");

  //Init the xApp
  init_xapp_api(argv[1]);
  sleep(1);

  e2_node_arr_xapp_t nodes = e2_nodes_xapp_api();
  defer({ free_e2_node_arr_xapp(&nodes); });

  assert(nodes.len > 0);

  printf("Connected E2 nodes = %d\n", nodes.len);
  for (size_t i = 0; i < nodes.len; i++) {
    e2ap_ngran_node_t ran_type = nodes.n[i].id.type;
    if (E2AP_NODE_IS_MONOLITHIC(ran_type))
      printf("E2 node %ld info: nb_id %d, mcc %d, mnc %d, mnc_digit_len %d, ran_type %s\n",
             i,
             nodes.n[i].id.nb_id.nb_id,
             nodes.n[i].id.plmn.mcc,
             nodes.n[i].id.plmn.mnc,
             nodes.n[i].id.plmn.mnc_digit_len,
             get_e2ap_ngran_name(ran_type));
    else
      printf("E2 node %ld info: nb_id %d, mcc %d, mnc %d, mnc_digit_len %d, ran_type %s, cu_du_id %lu\n",
             i,
             nodes.n[i].id.nb_id.nb_id,
             nodes.n[i].id.plmn.mcc,
             nodes.n[i].id.plmn.mnc,
             nodes.n[i].id.plmn.mnc_digit_len,
             get_e2ap_ngran_name(ran_type),
             *nodes.n[i].id.cu_du_id);

    printf("E2 node %ld supported RAN function's IDs:", i);
    for (size_t j = 0; j < nodes.n[i].len_rf; j++)
      printf(", %d", nodes.n[i].rf[j].id);
    printf("\n");
  }

  printf("Hello World\n");

  //Stop the xApp
  while(try_stop_xapp_api() == false)
    usleep(1000);

  printf("Test xApp run SUCCESSFULLY\n");
}

