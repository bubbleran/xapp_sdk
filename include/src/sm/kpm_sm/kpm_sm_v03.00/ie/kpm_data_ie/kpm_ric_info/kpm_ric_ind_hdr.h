#ifndef RIC_INDICATION_HEADER_KPM_V3_H
#define RIC_INDICATION_HEADER_KPM_V3_H

#ifdef __cplusplus
extern "C" {
#endif

#include "kpm_ric_ind_hdr_frm_1.h"


typedef enum {
  FORMAT_1_INDICATION_HEADER,

  END_INDICATION_HEADER

} format_ind_hdr_e;


// 8.2.1.3    RIC INDICATION HEADER IE

typedef struct {
  format_ind_hdr_e type;
  union {
    kpm_ric_ind_hdr_format_1_t kpm_ric_ind_hdr_format_1;
  };

} kpm_ind_hdr_t;

void free_kpm_ind_hdr(kpm_ind_hdr_t * src);

bool eq_kpm_ind_hdr(kpm_ind_hdr_t const * m0, kpm_ind_hdr_t const * m1);

kpm_ind_hdr_t cp_kpm_ind_hdr(kpm_ind_hdr_t const* src);

#ifdef __cplusplus
}
#endif

#endif

// done
