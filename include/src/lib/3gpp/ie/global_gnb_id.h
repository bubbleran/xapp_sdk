#ifndef GLOBAL_GNB_ID_H
#define GLOBAL_GNB_ID_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "e2ap_gnb_id.h"
#include "plmn_identity.h"

// 
// 9.2.2.1

typedef enum {
    GNB_TYPE_ID,
    END_TYPE_ID
} gnb_type_id_e;

typedef struct {
    e2sm_plmn_t plmn_id;
    gnb_type_id_e type;
    union {
       e2ap_gnb_id_t gnb_id; 
    };
} global_gnb_id_t;

global_gnb_id_t cp_global_gnb_id(global_gnb_id_t const* src);

bool eq_global_gnb_id(global_gnb_id_t const * m0, global_gnb_id_t const * m1);

#ifdef __cplusplus
}
#endif

#endif

// done
