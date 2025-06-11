#ifndef MATCHING_CONDITION_FORMAT_4_LIST_KPM_V2_01_H
#define MATCHING_CONDITION_FORMAT_4_LIST_KPM_V2_01_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>

#include "test_info_lst.h"
#include "enum_value.h"

/* Intermediate structure for  8.2.1.2.4  E2SM-KPM Action Definition Format 4 */

typedef struct {
    test_info_lst_t test_info_lst;  // 8.3.22

    enum_value_e *logical_OR;  // 8.3.25  -  OPTIONAL; not yet implemented in ASN.1

} matching_condition_format_4_lst_t;

void free_matching_cond_frm_4(matching_condition_format_4_lst_t* src);

bool eq_matching_cond_frm_4(matching_condition_format_4_lst_t const * m0, matching_condition_format_4_lst_t const * m1);

matching_condition_format_4_lst_t cp_matching_cond_frm_4(const matching_condition_format_4_lst_t * src);

#ifdef __cplusplus
}
#endif

#endif

// done
