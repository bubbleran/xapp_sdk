#ifndef GROUP_UE_E2SM_LLC_MIR_H
#define GROUP_UE_E2SM_LLC_MIR_H 

#include "../../../../lib/sm/ie/cell_global_id.h"
#include "../../../../lib/sm/ie/ue_id.h"

#include <stdbool.h>

// 8.3.13 
typedef struct{
  // 8.3.14
  // Optional
  cell_global_id_t* cell_global_id;

  // 8.3.8
  // [0, 65535]
  size_t sz_ue;
  ue_id_e2sm_t* ue;

} group_ue_t; 

group_ue_t cp_group_ue(group_ue_t const* src);

void free_group_ue(group_ue_t* src); 

bool eq_group_ue(group_ue_t const* m0, group_ue_t const* m1);  

#endif
