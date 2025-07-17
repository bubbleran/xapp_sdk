#ifndef GNB_h
#define GNB_h

#ifdef __cplusplus
extern "C" {
#endif

#include "guami.h"
#include "global_gnb_id.h"
#include "global_ng_ran_node_id.h"
#include <stdint.h>
#include <stdlib.h>

typedef struct{
  // 6.2.3.16
  // Mandatory
  // AMF UE NGAP ID
  // Defined in TS 38.413 [6] (NGAP) clause 9.3.3.1.
  // Defined in TS 38.401 [2].
  // fill with openair3/NGAP/ngap_gNB_ue_context.h:61
  uint64_t amf_ue_ngap_id; // [0, 2^40 ]

  // Mandatory
  // GUAMI 6.2.3.17 
  guami_t guami;

  // gNB-CU UE F1AP ID List
  // C-ifCUDUseparated 
  size_t gnb_cu_ue_f1ap_lst_len;  // [1,4]
  uint32_t *gnb_cu_ue_f1ap_lst;

  //gNB-CU-CP UE E1AP ID List
  //C-ifCPUPseparated 
  size_t gnb_cu_cp_ue_e1ap_lst_len;  // [1, 65535]
  uint32_t *gnb_cu_cp_ue_e1ap_lst;

  // RAN UE ID
  // Optional
  // 6.2.3.25
  // OCTET STRING (SIZE (8))
  // Defined in TS 38.473 (F1AP) 
  // clause 9.2.2.1
  // UE CONTEXT SETUP REQUEST
  uint64_t *ran_ue_id;

  // M-NG-RAN node UE XnAP ID
  // C- ifDCSetup
  // 6.2.3.19
  uint32_t *ng_ran_node_ue_xnap_id;

  // Global gNB ID
  // 6.2.3.3
  // Optional
  // This IE shall not be used. Global NG-RAN Node ID IE shall replace this IE 
  global_gnb_id_t *global_gnb_id;

  // Global NG-RAN Node ID
  // C-ifDCSetup
  // 6.2.3.2
  global_ng_ran_node_id_t *global_ng_ran_node_id;

} gnb_e2sm_t ;

void free_gnb_ue_id_e2sm(gnb_e2sm_t * src);

bool eq_gnb_ue_id_e2sm(gnb_e2sm_t const * m0, gnb_e2sm_t const * m1);

gnb_e2sm_t cp_gnb_ue_id_e2sm(const gnb_e2sm_t * src);

#ifdef __cplusplus
}
#endif

#endif

// done
