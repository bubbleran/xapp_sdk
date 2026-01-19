#ifndef VRB_TO_PRB_MAP_LLC_E2SM_MIR_H
#define VRB_TO_PRB_MAP_LLC_E2SM_MIR_H 

#include <stdbool.h>

typedef enum{
  INTERLEAVED_VRB_TO_PRB_MAP,
  END_VRB_TO_PRB_MAP_E
} vrb_to_prb_map_e;

bool eq_vrb_to_prb_map(vrb_to_prb_map_e const* m0, vrb_to_prb_map_e const* m1);

#endif
