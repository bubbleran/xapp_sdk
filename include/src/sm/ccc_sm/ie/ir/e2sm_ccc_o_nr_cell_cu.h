/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef E2SM_CCC_O_NR_CELL_CU_H
#define E2SM_CCC_O_NR_CELL_CU_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "e2sm_ccc_plmn_info.h"

// 8.8.2.1
typedef struct{
  // Integer
  uint32_t cell_local_id;

  // plMNInfoList
  // 9.3.15
  // [1..65536]
  size_t sz_plmn_info_lst;
  e2sm_ccc_plmn_info_t* plmn_info_lst;

} e2sm_ccc_o_nr_cell_cu_t;

void free_e2sm_ccc_o_nr_cell_cu(e2sm_ccc_o_nr_cell_cu_t* src);

bool eq_e2sm_ccc_o_nr_cell_cu(e2sm_ccc_o_nr_cell_cu_t const* m0, e2sm_ccc_o_nr_cell_cu_t const* m1);

e2sm_ccc_o_nr_cell_cu_t cp_e2sm_ccc_o_nr_cell_cu(e2sm_ccc_o_nr_cell_cu_t const* src);

#endif

