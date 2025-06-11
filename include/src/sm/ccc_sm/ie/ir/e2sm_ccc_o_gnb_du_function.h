/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef E2SM_CCC_O_GNB_DU_FUNCTION_H
#define E2SM_CCC_O_GNB_DU_FUNCTION_H

#include <stdint.h>
#include <stdbool.h>

// 8.8.1.1
typedef struct{
  // Integer
  // [0..(2^36 - 1)]
  uint64_t gnb_du_id:36;

  // String
  char * gnb_du_name;

  // Integer
  // [0..4294967295]
  uint32_t gnb_id;

  // Integer
  // [22..32]
  uint8_t gnb_id_len;

} e2sm_ccc_o_gnb_du_function_t;

void free_e2sm_ccc_o_gnb_du_function(e2sm_ccc_o_gnb_du_function_t* src);

bool eq_e2sm_ccc_o_gnb_du_function(e2sm_ccc_o_gnb_du_function_t const* m0, e2sm_ccc_o_gnb_du_function_t const* m1);

e2sm_ccc_o_gnb_du_function_t cp_e2sm_ccc_o_gnb_du_function(e2sm_ccc_o_gnb_du_function_t const* src);

#endif

