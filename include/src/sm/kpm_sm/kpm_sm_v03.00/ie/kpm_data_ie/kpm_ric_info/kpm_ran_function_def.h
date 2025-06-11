#ifndef RAN_FUNCTION_DEFINITION_KPM_V3_H
#define RAN_FUNCTION_DEFINITION_KPM_V3_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../../../../../../lib/sm/ie/ran_function_name.h"
#include "kpm_ric_event_trigger_def.h"
#include "kpm_ric_action_def.h"
#include "kpm_ric_ind_hdr.h"
#include "kpm_ric_ind_msg.h"

typedef struct {
    style_ric_event_trigger_e style_type; // 8.3.3
    byte_array_t style_name;  // 8.3.4
    format_ric_event_trigger_e format_type;  // 8.3.5
} ric_event_trigger_style_item_t;


typedef struct {
    byte_array_t name; // 8.3.9
    uint16_t *id; // 8.3.10  -  OPTIONAL
    bin_range_def_t *bin_range_def;  // 8.3.26  -  OPTIONAL; not yet implemented in ASN.1
} meas_info_for_action_lst_t;

typedef struct {
    ric_service_report_e report_style_type;  // 8.3.3
    byte_array_t report_style_name;  // 8.3.4
    format_action_def_e act_def_format_type;  // 8.3.5

    size_t meas_info_for_action_lst_len;  // [1, 65535]
    meas_info_for_action_lst_t *meas_info_for_action_lst;

    format_ind_hdr_e ind_hdr_format_type;  // 8.3.5
    format_ind_msg_e ind_msg_format_type;  // 8.3.5


} ric_report_style_item_t;

// Table 7.8-1: for more information about style-format mapping




/* 8.2.2.1  RAN Function Definition IE */

typedef struct {
    ran_function_name_t name;  // 8.3.2

    size_t sz_ric_event_trigger_style_list;  // [0, 63]
    ric_event_trigger_style_item_t *ric_event_trigger_style_list;

    size_t sz_ric_report_style_list;  // [0, 63]
    ric_report_style_item_t *ric_report_style_list;

} kpm_ran_function_def_t;


void free_kpm_ran_function_def(kpm_ran_function_def_t* src);

bool eq_kpm_ran_function_def(kpm_ran_function_def_t const * m0, kpm_ran_function_def_t const * m1);

kpm_ran_function_def_t cp_kpm_ran_function_def( kpm_ran_function_def_t  const* src);


#ifdef __cplusplus
}
#endif

#endif

// done
