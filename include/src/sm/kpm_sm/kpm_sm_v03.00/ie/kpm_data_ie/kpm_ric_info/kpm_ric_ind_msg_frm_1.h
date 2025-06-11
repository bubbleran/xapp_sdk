#ifndef RIC_INDICATION_MESSAGE_FORMAT_1_KPM_V3_H
#define RIC_INDICATION_MESSAGE_FORMAT_1_KPM_V3_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "../data/meas_data_lst.h"
#include "../data/meas_info_frm_1_lst.h"

//  8.2.1.4.1  E2SM-KPM Indication Message Format 1

typedef struct {
    size_t                    meas_data_lst_len; // [1, 65535]
    meas_data_lst_t          *meas_data_lst;

    size_t                    meas_info_lst_len; // [0, 65535]
    meas_info_format_1_lst_t *meas_info_lst;    // OPTIONAL, meas_info_lst_len can be zero

    uint32_t                 *gran_period_ms;  // 8.3.8  -  OPTIONAL

} kpm_ind_msg_format_1_t;

void free_kpm_ind_msg_frm_1(kpm_ind_msg_format_1_t* src);

bool eq_kpm_ind_msg_frm_1(kpm_ind_msg_format_1_t const* m0, kpm_ind_msg_format_1_t const* m1);

kpm_ind_msg_format_1_t cp_kpm_ind_msg_frm_1(kpm_ind_msg_format_1_t const* src);


#ifdef __cplusplus
}
#endif

#endif

// done
