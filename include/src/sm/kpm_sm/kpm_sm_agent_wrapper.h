#ifndef KPM_SM_AGENT_WRAPPER_MIR_H
#define KPM_SM_AGENT_WRAPPER_MIR_H 

#ifdef KPM_V2_01
#include "kpm_sm_v02.01/kpm_sm_agent.h"
#elif defined(KPM_V2_03)
#include "kpm_sm_v02.03/kpm_sm_agent.h"
#elif defined(KPM_V3_00)
#include "kpm_sm_v03.00/kpm_sm_agent.h"
#else
_Static_assert(0!=0, "Unknown KPM version");
#endif




#endif
