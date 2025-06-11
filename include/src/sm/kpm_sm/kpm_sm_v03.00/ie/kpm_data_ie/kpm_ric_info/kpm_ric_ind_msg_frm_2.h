#ifndef RIC_INDICATION_MESSAGE_FORMAT_2_KPM_V3_H
#define RIC_INDICATION_MESSAGE_FORMAT_2_KPM_V3_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdbool.h>

#include "../data/meas_data_lst.h"
#include "../data/meas_info_cond_ue_lst.h"


//  8.2.1.4.2  E2SM-KPM Indication Message Format 2

typedef struct {
    size_t                    meas_data_lst_len; // [1, 65535]
    meas_data_lst_t          *meas_data_lst;

    size_t                    meas_info_cond_ue_lst_len;  // [1, 65535]
    meas_info_cond_ue_lst_t  *meas_info_cond_ue_lst;

    uint32_t                 *gran_period_ms;  // 8.3.8  -  OPTIONAL  (1..4294967295)

} kpm_ind_msg_format_2_t;

void free_kpm_ind_msg_frm_2(kpm_ind_msg_format_2_t* src);

bool eq_kpm_ind_msg_frm_2(kpm_ind_msg_format_2_t const* m0, kpm_ind_msg_format_2_t const* m1);

kpm_ind_msg_format_2_t cp_kpm_ind_msg_frm_2(kpm_ind_msg_format_2_t const* src);

#ifdef __cplusplus
}
#endif

#endif

// done
