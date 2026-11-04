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

#ifndef E2X_SERVICE_MODEL_AGENT_H
#define E2X_SERVICE_MODEL_AGENT_H

#include <stddef.h>
#include <stdint.h>

#include "../sm_agent.h"

__attribute__ ((visibility ("default"))) 
sm_agent_t* make_e2x_sm_agent(sm_io_ag_ran_t const* io);

#endif

