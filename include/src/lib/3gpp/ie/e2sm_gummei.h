#ifndef E2SM_GUMMEI_H
#define E2SM_GUMMEI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "plmn_identity.h"

//  6.2.3.18  GUMMEI  -  This IE indicates the globally unique MME identity.

typedef struct {

    // all are mandatory

    e2sm_plmn_t plmn_id;

    uint16_t mme_group_id;

    uint8_t mme_code;


} e2sm_gummei_t;


e2sm_gummei_t cp_e2sm_gummei(e2sm_gummei_t const* src);

bool eq_e2sm_gummei(e2sm_gummei_t const * m0, e2sm_gummei_t const * m1);

#ifdef __cplusplus
}
#endif

#endif

// done
