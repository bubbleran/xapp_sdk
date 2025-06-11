#ifndef ACTION_DEFINITION_FORMAT_1_KPM_V2_H
#define ACTION_DEFINITION_FORMAT_1_KPM_V2_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>

#include "../data/meas_info_frm_1_lst.h"
#include "../data/meas_bin_range_info_lst.h"
#include "../../../../../../lib/sm/ie/cell_global_id.h"


// 8.2.1.2.1  E2SM-KPM Action Definition Format 1
typedef struct{

  size_t meas_info_lst_len;  // [1, 65535]
  meas_info_format_1_lst_t *meas_info_lst; 
 
  uint32_t gran_period_ms;  // 8.3.8 [0, 4294967295]

  cell_global_id_t* cell_global_id; // 8.3.20 - OPTIONAL

  size_t meas_bin_range_info_lst_len; // [0, 65535]
  meas_bin_range_info_lst_t *meas_bin_info_lst;


} kpm_act_def_format_1_t ;

void free_kpm_action_def_frm_1(kpm_act_def_format_1_t* src);

bool eq_kpm_action_def_frm_1(kpm_act_def_format_1_t const * m0, kpm_act_def_format_1_t const * m1);

kpm_act_def_format_1_t cp_kpm_action_def_frm_1(const kpm_act_def_format_1_t * src);

#ifdef __cplusplus
}
#endif

#endif

// done
