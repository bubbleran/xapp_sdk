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
