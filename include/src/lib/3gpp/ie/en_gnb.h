#ifndef EN_GNB_h
#define EN_GNB_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "global_enb_id.h"

typedef struct {

    // 6.2.3.23
    // Mandatory
    // MeNB UE X2AP ID
    uint16_t enb_ue_x2ap_id;  // INTEGER (0..4095), ask Mikel

    // 6.2.3.24
    // OPTIONAL
    // MeNB UE X2AP ID Extension
    uint16_t *enb_ue_x2ap_id_extension;  // INTEGER (0..4095), ask Mikel

    // 6.2.3.9
    // Mandatory
    // Global eNB ID
    global_enb_id_t global_enb_id;

    // 6.2.3.21
    // gNB-CU UE F1AP ID
    // C-ifCUDUseparated 
    uint32_t *gnb_cu_ue_f1ap_lst;

    // gNB-CU-CP UE E1AP ID List
    // C-ifCPUPseparated 
    size_t gnb_cu_cp_ue_e1ap_lst_len;  // [1, 65535]
    uint32_t *gnb_cu_cp_ue_e1ap_lst;  // 6.2.3.20

    // RAN UE ID
    // Optional
    // 6.2.3.25
    uint64_t *ran_ue_id;

} en_gnb_e2sm_t;

void free_en_gnb_ue_id_e2sm(en_gnb_e2sm_t * src);

bool eq_en_gnb_ue_id_e2sm(en_gnb_e2sm_t const * m0, en_gnb_e2sm_t const * m1);

en_gnb_e2sm_t cp_en_gnb_ue_id_e2sm(const en_gnb_e2sm_t * src);

#ifdef __cplusplus
}
#endif

#endif

// done
