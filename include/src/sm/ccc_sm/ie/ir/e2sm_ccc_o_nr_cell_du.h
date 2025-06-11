/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef e2sm_ccc_o_nr_cell_du_H
#define e2sm_ccc_o_nr_cell_du_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "e2sm_ccc_plmn_info.h"
#include "e2sm_ccc_o_bwp.h"
#include "e2sm_ccc_partition_lst.h"

typedef enum{
  ENABLED_OPERATIONAL_STATE,
  DISABLED_OPERATIONAL_STATE,
  END_OPERATIONAL_STATE
}operational_state_e;

typedef enum{
  LOCKED_ADMINISTRATIVE_STATE,
  SHUTTING_DOWN_ADMINISTRATIVE_STATE,
  UNLOCKED_ADMINISTRATIVE_STATE,
  END_ADMINISTRATIVE_STATE
}administrative_state_e;

typedef enum{
  IDLE_CELL_STATE,
  INACTIVE_CELL_STATE,
  ACTIVE_CELL_STATE,
  END_CELL_STATE,
}cell_state_e;

typedef enum{
  SSB_PERIODICITY_5,
  SSB_PERIODICITY_10,
  SSB_PERIODICITY_20,
  SSB_PERIODICITY_40,
  SSB_PERIODICITY_80,
  SSB_PERIODICITY_160,
  SSB_PERIODICITY_END,
}ssb_periodicity_e;


typedef enum{
  SSB_SUB_CARRIER_SPACING_15,
  SSB_SUB_CARRIER_SPACING_30,
  SSB_SUB_CARRIER_SPACING_120,
  SSB_SUB_CARRIER_SPACING_240,
  SSB_SUB_CARRIER_SPACING_END,
}ssb_sub_carrier_spacing_e;

typedef enum{
  SSB_DURATION_1,
  SSB_DURATION_2,
  SSB_DURATION_3,
  SSB_DURATION_4,
  SSB_DURATION_5,
  SSB_DURATION_END,
}ssb_duration_e;

// 8.8.2.2
typedef struct{
  // Integer
  uint32_t cell_local_id;

  operational_state_e operational_state;

  administrative_state_e administrative_state;

  cell_state_e cell_state;
  // Integer
  // [0..503]
  uint16_t nr_pci;
  // Integer
  // [0..16777215]
  uint32_t nr_tac;
  // Integer
  uint32_t arfcn_dl;
  // Integer
  uint32_t arfcn_ul;
  // Integer
  uint32_t arfcn_sul;
  // Integer
  // [0..3279165]
  uint32_t ssb_frequency;

  ssb_periodicity_e ssb_periodicity;

  ssb_sub_carrier_spacing_e ssb_sub_carrier_spacing;
  // Integer
  // [0..159]
  uint8_t ssb_off_set;

  ssb_duration_e ssb_duration;
  // Integer
  uint32_t bS_Channel_BwDL;
  /// Integer
  uint32_t bS_Channel_BwUL;
  // Integer
  uint32_t bS_Channel_BwSUL;
  // plMNInfoList
  // 9.3.15
  // [1..65536]
  size_t sz_plmn_info_lst;
  e2sm_ccc_plmn_info_t* plmn_info_lst;
  // bWPList
  // 9.3.18
  // [1...256]
  // 8.8.2.3
  size_t sz_bwp_lst;
  e2sm_ccc_o_bwp_t* bwp_lst;
  // 9.3.21
  // partition list
  e2sm_ccc_partition_lst_t partition_lst;

} e2sm_ccc_o_nr_cell_du_t;

void free_e2sm_ccc_o_nr_cell_du(e2sm_ccc_o_nr_cell_du_t* src);

bool eq_e2sm_ccc_o_nr_cell_du(e2sm_ccc_o_nr_cell_du_t const* m0, e2sm_ccc_o_nr_cell_du_t const* m1);

e2sm_ccc_o_nr_cell_du_t cp_e2sm_ccc_o_nr_cell_du(e2sm_ccc_o_nr_cell_du_t const* src);

#endif

