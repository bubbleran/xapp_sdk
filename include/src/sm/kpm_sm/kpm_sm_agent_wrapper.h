/*

Copyright (C) 2026 BubbleRAN

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see http://www.gnu.org/licenses/.
*/

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
