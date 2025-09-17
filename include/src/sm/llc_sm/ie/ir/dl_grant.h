#ifndef DOWNLINK_GRANT_E2SM_LLC_MIR_H
#define DOWNLINK_GRANT_E2SM_LLC_MIR_H 

#include "../../../../lib/sm/ie/ue_id.h"
#include "log_chann_llc.h"
#include "dci_1_0_llc.h"
#include "dci_1_1_llc.h"
#include <stdbool.h>

typedef enum{
  DCI_1_0_DL_CTRL_INFO_E,
  DCI_1_1_DL_CTRL_INFO_E,
  SEMI_PERSISTENT_DL_CTRL_INFO_E,
  END_DL_CTRL_INFO_E,
} dl_ctrl_info_e; 

// From 8.3.26    
typedef struct{

  // Grant ID 
  // Mandatory
  // [1,64]
  uint32_t grant_id;

  // BWP ID
  // Optional
  // [0,4]
  uint32_t* bwp_id;

  //8.3.8
  //UE ID 
  //Mandatory 
  ue_id_e2sm_t ue_id;

  // List of Logical Channels
  // [1,63]
  size_t sz_log_chann_llc;
  log_chann_llc_t* log_chann_llc;

  // Downlink Control Information Type
  dl_ctrl_info_e dl_ctrl_info_type;  
  union{
    dci_1_0_llc_t dci_1_0;
    dci_1_1_llc_t dci_1_1;
  };
 
} dl_grant_t; 

dl_grant_t cp_dl_grant(dl_grant_t const* src);  

void free_dl_grant(dl_grant_t* src);

bool eq_dl_grant(dl_grant_t const* m0,  dl_grant_t const* m1);


#endif
