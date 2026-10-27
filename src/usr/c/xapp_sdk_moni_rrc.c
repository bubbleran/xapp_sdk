#include "xapp_sdk_api.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void dl_cb_fn(const char* val, size_t len, uint32_t ric_req_id)
{
  printf("ric_req_id %u DL-DCCH: \n %.*s\n", ric_req_id, (int)len, val);
}

void ul_cb_fn(const char* val, size_t len, uint32_t ric_req_id)
{
  printf("ric_req_id %u UL-DCCH: \n %.*s\n", ric_req_id, (int)len, val);
}


int main(int argc, char** argv)
{
  init_xapp_sdk(argc, argv);

  arr_node_data_t arr = node_data_xapp_sdk(MONITOR_USE_CASE_e); 
  assert(arr.sz > 0 && "No E2 Node connected");

  global_e2_node_id_sdk_t const* node = &arr.n[0].node;

  stop_token_t stop0 = e2_node_mntr_async_xapp_sdk(node, DL_DCCH_RRC, dl_cb_fn); 
  stop_token_t stop1 = e2_node_mntr_async_xapp_sdk(node, UL_DCCH_RRC, ul_cb_fn); 

  sleep(10);

  printf("Stopping ric_req_id %u\n", stop0.ric_req_id);
  stop_cb_xapp_sdk(stop0);
  printf("Stopping ric_req_id %u\n", stop1.ric_req_id);
  stop_cb_xapp_sdk(stop1);

  sleep(1);

  free_arr_node_data(&arr);

  printf("Test xApp run SUCCESSFULLY\n");
  return EXIT_SUCCESS;
}



