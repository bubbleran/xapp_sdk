/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#include <assert.h>
#include <stdlib.h>

#include "xapp_sdk_api.h"

int main(int argc, char** argv)
{
  init_xapp_sdk(argc, argv);

  arr_node_data_t arr = node_data_xapp_sdk(HAND_OVER_USE_CASE_e); 

  assert(arr.sz > 0 && arr.sz < 3 && "At least 1 or 2 gNBs needed for handover");

  size_t sum_ue = 0;
  for (size_t i = 0; i < arr.sz; ++i){
	  sum_ue += arr.n[i].sz_ue;
  }
  assert(sum_ue > 0 && "At least one UE needed");

  size_t const idx = arr.n[0].sz_ue > 0 ? 0 : 1; 
  global_e2_node_id_sdk_t const* node = &arr.n[idx].node;
  ue_id_e2sm_sdk_t const* ue = &arr.n[idx].ue_ho[0].ue;

  assert(arr.n[idx].ue_ho[0].ho.target_pci != NULL && "Target physical cell ID needed!");
  assert(arr.n[idx].ue_ho[0].ho.target_ssb_nr_arfcn != NULL && "Target ssb ARFCN needed!");

  uint16_t target_pci = arr.n[idx].ue_ho[0].ho.target_pci[0]; 
  size_t target_ssb_nr_arfcn = arr.n[idx].ue_ho[0].ho.target_ssb_nr_arfcn[0];

  ho_xapp_sdk(node, ue, target_pci, target_ssb_nr_arfcn);

  free_arr_node_data(&arr);

  return EXIT_SUCCESS;
}
