#ifndef GLOBAL_ENB_ID_H
#define GLOBAL_ENB_ID_H

#ifdef __cplusplus
extern "C" {
#endif

#include "plmn_identity.h"

#include <stdbool.h>

//  6.2.3.9 Global eNB ID

typedef enum {
    MACRO_ENB_TYPE_ID,
    HOME_ENB_TYPE_ID,
    SHORT_MACRO_ENB_TYPE_ID,
    LONG_MACRO_ENB_TYPE_ID,

    END_ENB_TYPE_ID

} enb_type_id_e;


typedef struct {
    e2sm_plmn_t plmn_id;

    enb_type_id_e type;
    union {
        uint32_t macro_enb_id; // BIT STRING (SIZE(20))
        uint32_t home_enb_id;  // // BIT STRING (SIZE(28))
        uint32_t short_macro_enb_id;  // BIT STRING (SIZE(18))
        uint32_t long_macro_enb_id;  // BIT STRING (SIZE(21))
    };
    

} global_enb_id_t;

global_enb_id_t cp_global_enb_ue_id_e2sm(  global_enb_id_t const* src);

bool eq_global_enb_id(global_enb_id_t const * m0, global_enb_id_t const * m1);

#ifdef __cplusplus
}
#endif

#endif

// done
