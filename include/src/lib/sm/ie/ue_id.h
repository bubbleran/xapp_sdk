#ifndef UE_ID_E2SM_H
#define UE_ID_E2SM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>

#include "../../3gpp/ie/gnb.h"
#include "../../3gpp/ie/gnb_du.h"
#include "../../3gpp/ie/gnb_cu_up.h"
#include "../../3gpp/ie/ng_enb.h"
#include "../../3gpp/ie/ng_enb_du.h"
#include "../../3gpp/ie/en_gnb.h"
#include "../../3gpp/ie/enb.h"

typedef enum{
  GNB_UE_ID_E2SM,
	GNB_DU_UE_ID_E2SM,
	GNB_CU_UP_UE_ID_E2SM,
	NG_ENB_UE_ID_E2SM,
	NG_ENB_DU_UE_ID_E2SM,
	EN_GNB_UE_ID_E2SM,
  ENB_UE_ID_E2SM,

  END_UE_ID_E2SM

} ue_id_e2sm_e; 

typedef struct {
  ue_id_e2sm_e type;
  union{
    gnb_e2sm_t gnb;
    gnb_du_e2sm_t  gnb_du;
    gnb_cu_up_e2sm_t  gnb_cu_up;
    ng_enb_e2sm_t ng_enb;
    ng_enb_du_e2sm_t  ng_enb_du;
    en_gnb_e2sm_t  en_gnb;
    enb_e2sm_t enb;
  };
} ue_id_e2sm_t;

void free_ue_id_e2sm(ue_id_e2sm_t * src);

bool eq_ue_id_e2sm(ue_id_e2sm_t const * m0, ue_id_e2sm_t const * m1);

ue_id_e2sm_t cp_ue_id_e2sm(const ue_id_e2sm_t * src);

#ifdef __cplusplus
}
#endif

#endif

// done
