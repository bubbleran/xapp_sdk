/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#include <assert.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "xapp_sdk_api.h"

static global_e2_node_id_sdk_t* node= NULL;

static _Atomic int dedicated_prb = 10;

static int clamp(int min, int max, int v)
{
  if(v < min) 
    return min;
  if(v > max)
    return max;
  return v;
}

static void cb_fn(float ue_thp_kbs, uint32_t ric_req_id)
{
  printf(" ue_thp_kbs %lf \n", ue_thp_kbs);

  if(ue_thp_kbs > 9999.9 && ue_thp_kbs < 15000.1)
    return;

  int new_dedicated_prb = dedicated_prb;
  if(ue_thp_kbs < 10000){
    new_dedicated_prb += 2; 
  } else if(ue_thp_kbs > 15000){
    new_dedicated_prb -= 2; 
  } else {
    assert(0!=0 && "Impossible path!");
  }

  int const min = 10;
  int const max = 100;
  dedicated_prb = clamp(min, max, new_dedicated_prb); 

  char* const sst = "0";
  char* const sd = "1";
  slice_xapp_sdk(node, sst, sd, dedicated_prb);
}

int main(int argc, char** argv)
{
  init_xapp_sdk(argc, argv);

//  arr_node_data_t arr_sli = node_data_xapp_sdk(SLICE_USE_CASE_e);
//  assert(arr_sli.sz > 0 && "At least one gNB needed for slicing");

  arr_node_data_t arr_mon = node_data_xapp_sdk(MONITOR_USE_CASE_e);
  assert(arr_mon.sz > 0 && "At least one gNB needed for monitoring");

//  assert(arr_mon.n[0].node.nb_id.nb_id == arr_sli.n[0].node.nb_id.nb_id); 

  node = &arr_mon.n[0].node;
  ue_id_e2sm_sdk_t const* ue = &arr_mon.n[0].ue_ho[0].ue;

  stop_token_t stop = ue_mntr_cb_xapp_sdk(node, ue, UE_THP_UL, PERIODICITY_1000_MS, cb_fn); 

  sleep(60);

  printf("Stopping ric_req_id %u\n", stop.ric_req_id);
  stop_cb_xapp_sdk(stop);

//  free_arr_node_data(&arr_sli);
  free_arr_node_data(&arr_mon);

  return EXIT_SUCCESS;
}

