#ifndef MEASUREMENT_INFORMATION_FORMAT_3_LIST_KPM_V2_H
#define MEASUREMENT_INFORMATION_FORMAT_3_LIST_KPM_V2_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>

#include "meas_type.h"
#include "bin_range_def.h"
#include "matching_cond_frm_3_lst.h"

/* Intermediate structure for  8.2.1.2.3  E2SM-KPM Action Definition Format 3 */
typedef struct {
    meas_type_t meas_type;

    size_t matching_cond_lst_len;  // [1, 32768]
    matching_condition_format_3_lst_t *matching_cond_lst;

    bin_range_def_t *bin_range_def; // 8.3.26  -  OPTIONAL

} meas_info_format_3_lst_t;

void free_meas_info_frm_3(meas_info_format_3_lst_t* src);

bool eq_meas_info_frm_3(meas_info_format_3_lst_t const * m0, meas_info_format_3_lst_t const * m1);

meas_info_format_3_lst_t cp_meas_info_frm_3(const meas_info_format_3_lst_t * src);

#ifdef __cplusplus
}
#endif

#endif

// done
