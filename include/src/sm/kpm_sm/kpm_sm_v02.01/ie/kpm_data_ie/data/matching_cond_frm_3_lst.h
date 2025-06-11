#ifndef MATCHING_CONDITION_FORMAT_3_LIST_KPM_V2_01_H
#define MATCHING_CONDITION_FORMAT_3_LIST_KPM_V2_01_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>

#include "label_info_lst.h"
#include "test_info_lst.h"
#include "enum_value.h"

/* Intermediate structure for  8.2.1.2.3  E2SM-KPM Action Definition Format 3 */

typedef struct {
    enum {LABEL_INFO, TEST_INFO, END_INFO} cond_type;
    union {
        label_info_lst_t label_info_lst;  // 8.3.11
        test_info_lst_t test_info_lst;  // 8.3.22
    };

#if defined KPM_V2_03 || defined KPM_V3_00 
    enum_value_e *logical_OR;  // 8.3.25  -  OPTIONAL 
#endif
} matching_condition_format_3_lst_t;

void free_matching_cond_frm_3(matching_condition_format_3_lst_t* src);

bool eq_matching_cond_frm_3(matching_condition_format_3_lst_t const * m0, matching_condition_format_3_lst_t const * m1);

matching_condition_format_3_lst_t cp_kpm_matching_cond_frm_3(matching_condition_format_3_lst_t const* src);

#ifdef __cplusplus
}
#endif

#endif

// done
