#ifndef LABEL_INFORMATION_LIST_KPM_V2_01_H
#define LABEL_INFORMATION_LIST_KPM_V2_01_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../../../../../../util/byte_array.h"
#include "../../../../../../lib/3gpp/ie/plmn_identity.h"
#include "../../../../../../lib/3gpp/ie/s_nssai.h"
#include "enum_value.h"

typedef enum {
	START_IND,
	END_IND,

	END_START_END_IND

} start_end_ind_e;


//  8.3.11   Measurement Label
typedef struct{
  enum_value_e  	    *noLabel;			/* OPTIONAL */
  e2sm_plmn_t         *plmn_id;   		/* OPTIONAL */
  s_nssai_e2sm_t       *sliceID;			/* OPTIONAL */
  uint8_t            	  *fiveQI;			/* OPTIONAL */
  uint8_t               *qFI;				/* OPTIONAL, INTEGER (0..63, …) */
  uint8_t        	      *qCI;	    		/* OPTIONAL */
  uint8_t        	      *qCImax;			/* OPTIONAL */
  uint8_t        	      *qCImin;			/* OPTIONAL */
  uint8_t	              *aRPmax;			/* OPTIONAL, INTEGER (1.. 15, …) */
  uint8_t	              *aRPmin;			/* OPTIONAL, INTEGER (1.. 15, …) */
  uint16_t	          *bitrateRange;	/* OPTIONAL */
  uint16_t	          *layerMU_MIMO;	/* OPTIONAL */
  enum_value_e  	      *sUM;	    		/* OPTIONAL */
  uint16_t              *distBinX;		/* OPTIONAL */
  uint16_t	          *distBinY;		/* OPTIONAL */
  uint16_t	          *distBinZ;		/* OPTIONAL */
  enum_value_e  	      *preLabelOverride;	/* OPTIONAL */
  start_end_ind_e	      *startEndInd;		/* OPTIONAL */
  enum_value_e  	      *min;	    		/* OPTIONAL */
  enum_value_e  	      *max;	    		/* OPTIONAL */
  enum_value_e          *avg;	    		/* OPTIONAL */
  uint16_t  			  *ssbIndex;		/* OPTIONAL */
  uint16_t  			  *nonGoB_beamformModeIndex;  /* OPTIONAL */
  uint8_t   			  *mimoModeIndex;    /* OPTIONAL, 1 = SU-MIMO, 2 = MU-MIMO  ask Mikel */
} label_info_lst_t;

//void cp_label_info(label_info_lst_t *dst, label_info_lst_t const *src);
label_info_lst_t cp_label_info(label_info_lst_t const *src);

bool eq_label_info(const label_info_lst_t *l1, const label_info_lst_t *l2);

void free_label_info(label_info_lst_t *l);

#ifdef __cplusplus
}
#endif

#endif

// done
