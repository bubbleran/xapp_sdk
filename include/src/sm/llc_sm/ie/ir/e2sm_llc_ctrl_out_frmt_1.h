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

#ifndef E2SM_LLC_CTRL_OUT_FRMT_1_MIR_H
#define E2SM_LLC_CTRL_OUT_FRMT_1_MIR_H 

#include "dl_schd_param.h"
#include "log_chnl_hndl.h"

#include <stdbool.h>

typedef enum{
  LOGICAL_CHANNEL_HANDLING_E2SM_LLC_CTRL_PARAM_E,
  DL_SCHEDULING_PARAMETER_E2SM_LLC_CTRL_PARAM_E,
  END_E2SM_LLC_CTRL_PARAM_E
} e2sm_llc_ctrl_param_e;

// 8.2.1.8.1 
typedef struct{

  // CHOICE Control Parameter Type
  e2sm_llc_ctrl_param_e type;
  union{
    //Logical Channel Handling
    // 8.3.24
    log_chnl_hndl_t log_chnl_hndl;  

    // DL Scheduling Parameters
    // 8.3.27
    dl_schd_param_t dl_schd_param;  
  };
} e2sm_llc_ctrl_out_frmt_1_t ;

e2sm_llc_ctrl_out_frmt_1_t cp_e2sm_llc_ctrl_out_frmt_1(e2sm_llc_ctrl_out_frmt_1_t const* src);

void free_e2sm_llc_ctrl_out_frmt_1(e2sm_llc_ctrl_out_frmt_1_t* src);

bool eq_e2sm_llc_ctrl_out_frmt_1(e2sm_llc_ctrl_out_frmt_1_t const* m0,e2sm_llc_ctrl_out_frmt_1_t const* m1);


#endif
