/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef E2SM_CCC_PARTITION_LST_H
#define E2SM_CCC_PARTITION_LST_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "e2sm_ccc_partition_flow_lst.h"

typedef struct {
  // Mandatory
  // Integer
  uint32_t p_offset_to_point_A;

  // Mandatory
  // Integer
  uint32_t p_number_of_rbs;

  // Mandatory
  // 9.3.20
  e2sm_ccc_partition_flow_lst_t partition_flow_lst;

} e2sm_ccc_partition_lst_item_t;

// 9.3.21
typedef struct{
  // [1..128]
  size_t sz_partition_lst_item;
  e2sm_ccc_partition_lst_item_t* partition_lst_item;

} e2sm_ccc_partition_lst_t;

void free_e2sm_ccc_partition_lst(e2sm_ccc_partition_lst_t* src);

bool eq_e2sm_ccc_partition_lst(e2sm_ccc_partition_lst_t const* m0, e2sm_ccc_partition_lst_t const* m1);

e2sm_ccc_partition_lst_t cp_e2sm_ccc_partition_lst(e2sm_ccc_partition_lst_t const* src);

#endif

