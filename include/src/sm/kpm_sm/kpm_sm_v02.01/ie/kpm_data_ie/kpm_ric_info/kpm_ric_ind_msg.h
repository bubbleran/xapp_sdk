#ifndef KPM_V2_01_RIC_INDICATION_MESSAGE_H
#define KPM_V2_01_RIC_INDICATION_MESSAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "kpm_ric_ind_msg_frm_1.h"
#include "kpm_ric_ind_msg_frm_2.h"
#include "kpm_ric_ind_msg_frm_3.h"

//  8.2.1.4   RIC INDICATION MESSAGE IE

typedef enum {
    FORMAT_1_INDICATION_MESSAGE,
    FORMAT_2_INDICATION_MESSAGE,
    FORMAT_3_INDICATION_MESSAGE,

    END_INDICATION_MESSAGE,
} format_ind_msg_e;

typedef struct {
  format_ind_msg_e type;
  union {
    kpm_ind_msg_format_1_t frm_1; // 8.2.1.4.1
    kpm_ind_msg_format_2_t frm_2; // 8.2.1.4.2
    kpm_ind_msg_format_3_t frm_3; // 8.2.1.4.3
  };
} kpm_ind_msg_t;

void free_kpm_ind_msg(kpm_ind_msg_t * src);

bool eq_kpm_ind_msg(kpm_ind_msg_t const * m0, kpm_ind_msg_t const * m1);

kpm_ind_msg_t cp_kpm_ind_msg(kpm_ind_msg_t const* src);


#ifdef __cplusplus
}
#endif

#endif

// done
