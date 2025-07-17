#ifndef NG_ENB_h
#define NG_ENB_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "guami.h"
#include "global_ng_enb_id.h"
#include "global_ng_ran_node_id.h"

typedef struct {
    uint64_t amf_ue_ngap_id;  // 6.2.3.16
    guami_t guami;  // 6.2.3.17 

    // 6.2.3.22
    // C-if CU DU separated
    // ng-eNB-CU UE W1AP ID
    uint32_t *ng_enb_cu_ue_w1ap_id;

    // 6.2.3.19
    // C- ifDCSetup
    // M-NG-RAN node UE XnAP ID
    uint32_t *ng_ran_node_ue_xnap_id;

    // OPTIONAL
    // This IE shall not be used. Global NG-RAN Node ID IE shall replace this IE
    global_ng_enb_id_t *global_ng_enb_id;

    // Global NG-RAN Node ID
    // C-ifDCSetup
    // 6.2.3.2
    global_ng_ran_node_id_t *global_ng_ran_node_id;

} ng_enb_e2sm_t;

void free_ng_enb_ue_id_e2sm(ng_enb_e2sm_t * src);

bool eq_ng_enb_ue_id_e2sm(ng_enb_e2sm_t const * m0, ng_enb_e2sm_t const * m1);

ng_enb_e2sm_t cp_ng_enb_ue_id_e2sm(const ng_enb_e2sm_t * src);

#ifdef __cplusplus
}
#endif

#endif

// done
