#ifndef E2SM_RC_INDICATION_HEADER_FORMAT_2_H
#define E2SM_RC_INDICATION_HEADER_FORMAT_2_H

#include "../../../../lib/sm/ie/ue_id.h"
#include <stdbool.h>

typedef struct{

  // UE ID
  // Mandatory
  // 9.3.10
  ue_id_e2sm_t ue_id;

  // RIC Insert Style Type
  // Mandatory
  // 9.3.3
  // 6.2.2.2. From common SM
  // RIC Style Type 
  // Integer
  uint32_t ric_style_type;

  // Insert Indication ID
  // Mandatory
  // 9.3.16
  // [1 - 65535]
  uint16_t ins_ind_id; 

} e2sm_rc_ind_hdr_frmt_2_t; 


e2sm_rc_ind_hdr_frmt_2_t cp_e2sm_rc_ind_hdr_frmt_2(e2sm_rc_ind_hdr_frmt_2_t const* src);

void free_e2sm_rc_ind_hdr_frmt_2(e2sm_rc_ind_hdr_frmt_2_t* src);

bool eq_e2sm_rc_ind_hdr_frmt_2(e2sm_rc_ind_hdr_frmt_2_t const* m0, e2sm_rc_ind_hdr_frmt_2_t const* m1);

#endif


