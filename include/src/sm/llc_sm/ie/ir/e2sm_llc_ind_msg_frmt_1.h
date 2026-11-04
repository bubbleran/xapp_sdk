/*

Copyright (C) 2026 BubbleRAN

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see http://www.gnu.org/licenses/.
*/

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
