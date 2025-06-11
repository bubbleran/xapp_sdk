#ifndef E2SM_RAN_CONTROL_ACTION_DEFINITION_FORMAT_4
#define E2SM_RAN_CONTROL_ACTION_DEFINITION_FORMAT_4

#include "../../../../lib/sm/ie/ue_id.h"
#include "seq_ins_style_multiple_action.h"

#include <stdbool.h>
#include <stdlib.h>

// 9.2.1.2.4
typedef struct{
  // Sequence of Insert Styles for
  // Multiple Actions
  // [1-4]
  size_t sz_seq_ins_style;
  seq_ins_style_t* seq_ins_style;

  // UE ID
  // Optional
  // 9.3.10
  ue_id_e2sm_t* ue_id;

} e2sm_rc_act_def_frmt_4_t;

void free_e2sm_rc_act_def_frmt_4(e2sm_rc_act_def_frmt_4_t* src);

bool eq_e2sm_rc_act_def_frmt_4(e2sm_rc_act_def_frmt_4_t const* m0, e2sm_rc_act_def_frmt_4_t const* m1);

e2sm_rc_act_def_frmt_4_t cp_e2sm_rc_act_def_frmt_4(e2sm_rc_act_def_frmt_4_t const* src);

#endif

