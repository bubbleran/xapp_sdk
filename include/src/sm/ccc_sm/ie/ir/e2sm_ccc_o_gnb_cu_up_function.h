/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef E2SM_CCC_O_GNB_CU_UP_FUNCTION_H
#define E2SM_CCC_O_GNB_CU_UP_FUNCTION_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "e2sm_ccc_plmn_info.h"

// 8.8.1.3
typedef struct{
  // Integer
  // [0..4294967295]
  uint32_t gnb_id;

  // Integer
  // [22..32]
  uint8_t gnb_id_len;

  // Integer
  // [0..(2^36 - 1)]
  uint64_t gnb_cu_up_id:36;

  // plMNInfoList
  // 9.3.15
  // [1..65536]
  size_t sz_plmn_info_lst;
  e2sm_ccc_plmn_info_t* plmn_info_lst;

} e2sm_ccc_o_gnb_cu_up_function_t;

void free_e2sm_ccc_o_gnb_cu_up_function(e2sm_ccc_o_gnb_cu_up_function_t* src);

bool eq_e2sm_ccc_o_gnb_cu_up_function(e2sm_ccc_o_gnb_cu_up_function_t const* m0, e2sm_ccc_o_gnb_cu_up_function_t const* m1);

e2sm_ccc_o_gnb_cu_up_function_t cp_e2sm_ccc_o_gnb_cu_up_function(e2sm_ccc_o_gnb_cu_up_function_t const* src);

#endif

