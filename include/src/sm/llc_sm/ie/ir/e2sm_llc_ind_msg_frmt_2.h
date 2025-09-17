#ifndef E2SM_LLC_INF_MSG_FRMT_2_MIR_H
#define E2SM_LLC_INF_MSG_FRMT_2_MIR_H 

#include "lower_measure.h"
#include <stdbool.h>

// 8.2.1.4.2
typedef struct{
  // [1,63]
  size_t sz_lower_measure;
  lower_measure_t* lower_measure;
} e2sm_llc_ind_msg_frmt_2_t; 

e2sm_llc_ind_msg_frmt_2_t cp_e2sm_llc_ind_msg_frmt_2(e2sm_llc_ind_msg_frmt_2_t const* src);

void free_e2sm_llc_ind_msg_frmt_2(e2sm_llc_ind_msg_frmt_2_t* src);

bool eq_e2sm_llc_ind_msg_frmt_2(e2sm_llc_ind_msg_frmt_2_t const* m0, e2sm_llc_ind_msg_frmt_2_t const* m1);

#endif
