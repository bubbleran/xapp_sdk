#ifndef E2SM_LLC_SLOT_TSTAMP_MIR_H
#define E2SM_LLC_SLOT_TSTAMP_MIR_H 

#include "slot_info.h"
#include <stdbool.h>

// 8.3.18
typedef struct{
  // 8.3.17
  // Mandatory
  slot_info_t slot_info;

  // Mandatory
  // Carries UTC time encoded as the
  // 64-bit timestamp format as defined
  // in Clause 6 of IETF RFC 5905
  // [7] containing both seconds
  // and fraction parts. Represents the
  // start time of the slot
  uint8_t slot_start_time[8];

} slot_tstamp_t ;

slot_tstamp_t cp_slot_tstamp(slot_tstamp_t const* src);

bool eq_slot_tstamp( slot_tstamp_t const* m0, slot_tstamp_t const* m1);

void free_slot_tstamp(slot_tstamp_t* src);

#endif
