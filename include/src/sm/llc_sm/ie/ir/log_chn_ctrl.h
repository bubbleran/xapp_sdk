#ifndef LOGICAL_CHANNEL_CONTROL_E2SM_LLC_MIR_H
#define LOGICAL_CHANNEL_CONTROL_E2SM_LLC_MIR_H 

#include "slot_info.h"
#include <stdbool.h>

// From 8.3.25
typedef struct{

  // Logical Channel ID 
  // Mandatory 
  // [1,32]
  uint32_t log_channel_id;

  //8.3.17
  //Starting Slot number 
  //Mandatory 
  slot_info_t slot_info; 

} log_chn_ctrl_t;

log_chn_ctrl_t cp_log_chn_ctrl(log_chn_ctrl_t const* src);

void free_log_chn_ctrl(log_chn_ctrl_t* src);

bool eq_log_chn_ctrl(log_chn_ctrl_t const* m0,log_chn_ctrl_t const* m1);

#endif
