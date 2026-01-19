#ifndef DL_HARQ_UE_ID_E2SM_LLC_MIR_H
#define DL_HARQ_UE_ID_E2SM_LLC_MIR_H 

#include "../../../../lib/sm/ie/ue_id.h"
#include "harq_codeword.h"

// From 8.3.23
typedef struct{

  // 8.3.8
  // Mandatory
  ue_id_e2sm_t ue_id;

  // DL HARQ Codewords
  // Possible Values {1,2}
  size_t sz_harq_codeword;
  harq_codeword_t* harq_codeword;

} dl_harq_ue_id_t;

dl_harq_ue_id_t cp_dl_harq_ue_id(dl_harq_ue_id_t  const* src) ;

void free_dl_harq_ue_id(dl_harq_ue_id_t* src) ;

bool eq_dl_harq_ue_id(dl_harq_ue_id_t const* m0, dl_harq_ue_id_t const* m1);

#endif
