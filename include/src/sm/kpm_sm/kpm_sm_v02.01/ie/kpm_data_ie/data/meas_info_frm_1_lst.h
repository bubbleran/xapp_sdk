#ifndef MEASUREMENT_INFORMATION_FORMAT_1_LIST_KPM_V2_01_H
#define MEASUREMENT_INFORMATION_FORMAT_1_LIST_KPM_V2_01_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "label_info_lst.h"
#include "meas_type.h"


/* Intermediate structure for 8.2.1.2.1  E2SM-KPM Action Definition Format 1 */ 
typedef struct{

  meas_type_t meas_type;
 
  size_t label_info_lst_len;  // [1, 2147483647]
  label_info_lst_t* label_info_lst;  // 8.3.11

} meas_info_format_1_lst_t;

meas_info_format_1_lst_t cp_meas_info_format_1_lst(meas_info_format_1_lst_t const* src);

void free_meas_info_frm_1(meas_info_format_1_lst_t* src);

bool eq_meas_info_frm_1(meas_info_format_1_lst_t const * m0, meas_info_format_1_lst_t const * m1);

#ifdef __cplusplus
}
#endif

#endif

// done
