#ifndef CSI_UE_ID_E2SM_LLC_MIR_H
#define CSI_UE_ID_E2SM_LLC_MIR_H 

#include "../../../../lib/sm/ie/ue_id.h"
#include "csi_report.h"
#include <stdbool.h>


typedef enum{
  PUCCH_UCI_CHANNEL_E, 
  PUSCH_UCI_CHANNEL_E,
  END_UCI_CHANNEL_E 
} uci_channel_e; 

// From 8.3.20
typedef struct{
  // 8.3.8
  // Mandatory
  ue_id_e2sm_t ue_id;

  // Channel carrying the UCI 
  // Mandatory
  uci_channel_e channel;

  // [1,255]
  size_t sz_csi_report;
  csi_report_t* csi_report;

} csi_ue_id_t;

csi_ue_id_t cp_csi_ue_id(csi_ue_id_t const* src); 

void free_csi_ue_id(csi_ue_id_t* src); 

bool eq_csi_ue_id(csi_ue_id_t const* m0, csi_ue_id_t const* m1); 

#endif
