#ifndef E2SM_LLC_CTRL_MSG_FRMT_1_MIR_H
#define E2SM_LLC_CTRL_MSG_FRMT_1_MIR_H 

#include "list_logical_channel_ue_id.h"
#include "list_dl_sched_ctrl.h"

#include <stdbool.h>

typedef enum{
  LOGICAL_CHANNEL_HANDLING_CONTROL_LLC_CTRL_MSG_FRMT_1_E,
  DL_SCHEDULING_CONTROL_LLC_CTRL_MSG_FRMT_1_E,
  END_LLC_CTRL_MSG_FRMT_1_E
} ctrl_type_llc_ctrl_msg_frmt_1_e;

typedef struct{
  ctrl_type_llc_ctrl_msg_frmt_1_e type;
  union{
    // 8.3.25
    lst_logical_channel_ue_id_t lst_log; 
    // 8.3.26
    lst_dl_sched_ctrl_t lst_dl_sched_ctrl;
  };

} e2sm_llc_ctrl_msg_frmt_1_t;

e2sm_llc_ctrl_msg_frmt_1_t cp_e2sm_llc_ctrl_msg_frmt_1(e2sm_llc_ctrl_msg_frmt_1_t const* src);

void free_e2sm_llc_ctrl_msg_frmt_1(e2sm_llc_ctrl_msg_frmt_1_t* src);

bool eq_e2sm_llc_ctrl_msg_frmt_1(e2sm_llc_ctrl_msg_frmt_1_t const* m0, e2sm_llc_ctrl_msg_frmt_1_t const* m1);

#endif
