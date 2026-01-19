#ifndef DL_HARQ_STATS_E2SM_LLC_MIR_H
#define DL_HARQ_STATS_E2SM_LLC_MIR_H 

#include "dl_harq_ue_id.h"
#include <stdbool.h>

//8.3.23
typedef struct{
  // DL HARQ UE Ide
  // [1, 65535]
  size_t sz_dl_harq_ue_id;
  dl_harq_ue_id_t* dl_harq_ue_id;
} dl_harq_stats_t;

dl_harq_stats_t cp_dl_harq_stats(dl_harq_stats_t const* src); 

void free_dl_harq_stats(dl_harq_stats_t* src); 

bool eq_dl_harq_stats(dl_harq_stats_t const* m0, dl_harq_stats_t const* m1); 

#endif
