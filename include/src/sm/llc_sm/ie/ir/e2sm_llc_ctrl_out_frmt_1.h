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
