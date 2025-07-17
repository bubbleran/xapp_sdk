#ifndef NG_ENB_DU_h
#define NG_ENB_DU_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    // 6.2.3.22
    // C-if CU DU separated
    // ng-eNB-CU UE W1AP ID
    uint32_t ng_enb_cu_ue_w1ap_id;

} ng_enb_du_e2sm_t;

void free_ng_enb_du_ue_id_e2sm(ng_enb_du_e2sm_t * src);

bool eq_ng_enb_du_ue_id_e2sm(ng_enb_du_e2sm_t const * m0, ng_enb_du_e2sm_t const * m1);

ng_enb_du_e2sm_t cp_ng_enb_du_ue_id_e2sm(const ng_enb_du_e2sm_t * src);

#ifdef __cplusplus
}
#endif

#endif

// done
