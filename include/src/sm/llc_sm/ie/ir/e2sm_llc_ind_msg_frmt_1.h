#ifndef E2SM_LLC_INF_MSG_FRMT_1_MIR_H
#define E2SM_LLC_INF_MSG_FRMT_1_MIR_H 

#include "slot_tstamp.h"
#include "csi_llc.h"
#include "srs_llc.h"

#include <stdbool.h>

typedef enum{
  SRS_LL_INFO_TYPE_E,
  CSI_LL_INFO_TYPE_E,
  END_LL_INFO_TYPE_E 
} ll_info_type_e ;

// 8.2.1.4.1
typedef struct{

  //8.3.18
  //Slot Time Stamp 
  //Mandatory
  slot_tstamp_t slot_tstamp;

  // Lower Layers Information Type
  // Mandatory
  ll_info_type_e ll_info_type;
  union{
    // 8.3.19
    srs_llc_t srs; 
    // 8.3.20
    csi_llc_t csi;
  };

} e2sm_llc_ind_msg_frmt_1_t; 


e2sm_llc_ind_msg_frmt_1_t cp_e2sm_llc_ind_msg_frmt_1(e2sm_llc_ind_msg_frmt_1_t const* src); 

bool eq_e2sm_llc_ind_msg_frmt_1(e2sm_llc_ind_msg_frmt_1_t const* m0,  e2sm_llc_ind_msg_frmt_1_t const* m1 );

void free_e2sm_llc_ind_msg_frmt_1(e2sm_llc_ind_msg_frmt_1_t* src);


#endif
