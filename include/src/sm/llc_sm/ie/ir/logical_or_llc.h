#ifndef LOGICAL_OR_E2SM_LLC_MIR_H
#define LOGICAL_OR_E2SM_LLC_MIR_H 

#include <stdbool.h>

// 8.3.11
// If set to “true”,
// logical connection
// to the next
// condition is “or”.
// Otherwise, “and”.
typedef enum{
  TRUE_LOGICAL_OR_LLC_E,
  FALSE_LOGICAL_OR_LLC_E,

  END_LOGICAL_OR_LLC_E
} logical_or_llc_e;

bool eq_logical_or_llc(logical_or_llc_e const* m0, logical_or_llc_e const* m1);

#endif
