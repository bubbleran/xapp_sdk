/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef e2sm_ccc_partition_flow_lst_H
#define e2sm_ccc_partition_flow_lst_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../../../lib/3gpp/ie/plmn_identity.h"
#include "../../../../lib/3gpp/ie/s_nssai.h"
#include "e2sm_ccc_5qi_lst.h"

typedef struct {
  // Mandatory
  // 9.3.12
  // E2SM 6.2.3.1
  e2sm_plmn_t plmn_id;

  // Mandatory
  // 9.3.13
  // E2SM 6.2.3.12
  s_nssai_e2sm_t s_nssai;

  // 9.3.19
  // Optional
  e2sm_ccc_5qi_lst_t* lst_5qi;

} e2sm_ccc_partition_flow_lst_item_t;

// 9.3.20
typedef struct{
  // [1..128]
  size_t sz_partition_flow_lst_item;
  e2sm_ccc_partition_flow_lst_item_t* partition_flow_lst_item;

} e2sm_ccc_partition_flow_lst_t;

void free_e2sm_ccc_partition_flow_lst(e2sm_ccc_partition_flow_lst_t* src);

bool eq_e2sm_ccc_partition_flow_lst(e2sm_ccc_partition_flow_lst_t const* m0, e2sm_ccc_partition_flow_lst_t const* m1);

e2sm_ccc_partition_flow_lst_t cp_e2sm_ccc_partition_flow_lst(e2sm_ccc_partition_flow_lst_t const* src);

#endif

