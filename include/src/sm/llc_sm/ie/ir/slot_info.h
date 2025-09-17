#ifndef E2SM_LLC_SLOT_INFO_MIR_H
#define E2SM_LLC_SLOT_INFO_MIR_H 

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum{
  SCS_15_SLOT_IDX_LLC_E,
  SCS_30_SLOT_IDX_LLC_E,
  SCS_60_SLOT_IDX_LLC_E,
  SCS_120_SLOT_IDX_LLC_E,
  END_SLOT_IDX_LLC_E
} slot_idx_llc_e;

// 8.3.17
typedef struct{

  // System Frame Number 
  // Mandatory
  // [0,1023]
  uint32_t frame_num;

  // Mandatory
  slot_idx_llc_e slot_idx;
  union{
    uint32_t scs_15;
    uint32_t scs_30;
    uint32_t scs_60;
    uint32_t scs_120;
  };

} slot_info_t;

slot_info_t cp_slot_info( slot_info_t const* src);

bool eq_slot_info(slot_info_t const* m0, slot_info_t const* m1);

void free_slot_info(slot_info_t* src);

#endif
