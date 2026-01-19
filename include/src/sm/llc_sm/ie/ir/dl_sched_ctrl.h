#ifndef DOWNLINK_SCHEDULING_CONTROL_E2SM_LLC_MIR_H
#define DOWNLINK_SCHEDULING_CONTROL_E2SM_LLC_MIR_H 

#include "slot_info.h"
#include "dl_grant.h"
#include "pdsch_smg.h"
#include "csi_rs_precoding_bnd.h"
#include "precoder_llc.h"

#include <stdbool.h>


// From 8.3.26    
typedef struct{

  // 8.3.17
  // Slot Information 
  // Mandatory
  slot_info_t slot_info;

  // DL Grants
  // [1, 63]
  size_t sz_dl_grant;
  dl_grant_t* dl_grant; 

  // PDSCH SMGs
  // [1, 63]
  size_t sz_pdsch_smg;
  pdsch_smg_t* pdsch_smg; 

  // CSI-RS Precoding Bands
  // [0, 63]
  size_t sz_csi_rs_precoding_bnd;
  csi_rs_precoding_bnd_t* csi_rs_precoding_bnd;

  // [1, 255] 
  size_t sz_precoder;
  precoder_llc_t* precoder;

} dl_sched_ctrl_t;

dl_sched_ctrl_t cp_dl_sched_ctrl(dl_sched_ctrl_t const* src);

bool eq_dl_sched_ctrl(dl_sched_ctrl_t const* m0, dl_sched_ctrl_t const* m1);

void free_dl_sched_ctrl(dl_sched_ctrl_t* src);



#endif
