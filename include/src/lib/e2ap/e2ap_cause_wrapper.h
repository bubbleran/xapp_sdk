#ifndef E2AP_CAUSE_WRAPPER_MIR_H
#define E2AP_CAUSE_WRAPPER_MIR_H 

#ifdef E2AP_V1
#include "v1_01/e2ap_types/common/e2ap_cause.h"
#elif E2AP_V2
#include "v2_03/e2ap_types/common/e2ap_cause.h"
#elif E2AP_V3
#include "v3_01/e2ap_types/common/e2ap_cause.h"
#else
static_assert(0!=0, "Unknown E2AP Version");
#endif

#endif
