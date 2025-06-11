#ifndef RRC_STATE_E2SM_H
#define RRC_STATE_E2SM_H 

#include "logical_or.h"

#include <stdbool.h>
#include <stdlib.h>

// 9.3.37
typedef enum{
  RRC_CONNECTED_RRC_STATE_E2SM_RC,
  RRC_INACTIVE_RRC_STATE_E2SM_RC,
  RRC_IDLE_RRC_STATE_E2SM_RC, 
  ANY_RRC_STATE_E2SM_RC,

  END_RRC_STATE_E2SM_RC,

} rrc_state_e2sm_rc_e;

typedef struct{
  // 9.3.37
  rrc_state_e2sm_rc_e state_chngd_to;

  // 9.3.25
  // Logical OR
  logical_or_e* log_or;

} rrc_state_t ;

void free_rrc_state(rrc_state_t* src);

bool eq_rrc_state(rrc_state_t const* m0, rrc_state_t const* m1);

rrc_state_t cp_rrc_state(rrc_state_t const* src);

#endif
