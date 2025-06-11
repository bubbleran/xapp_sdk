#ifndef RIC_INDICATION_MESSAGE_FORMAT_3_KPM_V2_01_H
#define RIC_INDICATION_MESSAGE_FORMAT_3_KPM_V2_01_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

#include "../../../../../../lib/sm/ie/ue_id.h"
#include "kpm_ric_ind_msg_frm_1.h"

typedef struct {
    ue_id_e2sm_t ue_meas_report_lst;  // 8.3.24

    kpm_ind_msg_format_1_t ind_msg_format_1;  // 8.2.1.4.1; measurement data per ue

} meas_report_per_ue_t;


//  8.2.1.4.3  E2SM-KPM Indication Message Format 3

typedef struct {
    size_t ue_meas_report_lst_len;  // [1, 65535]

    meas_report_per_ue_t *meas_report_per_ue;

} kpm_ind_msg_format_3_t;

void free_kpm_ind_msg_frm_3(kpm_ind_msg_format_3_t * src);

bool eq_kpm_ind_msg_frm_3(kpm_ind_msg_format_3_t const * m0, kpm_ind_msg_format_3_t const * m1);

kpm_ind_msg_format_3_t cp_kpm_ind_msg_frm_3(const kpm_ind_msg_format_3_t * src);

#ifdef __cplusplus
}
#endif

#endif

// done
