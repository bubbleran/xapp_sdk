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

#ifndef E2X_SERVICE_MODEL_ID_H
#define E2X_SERVICE_MODEL_ID_H 

/*
 * Service Model ID needed for the agent as well as for the ric to ensure that they match. 
 */

#include <stdint.h>

static
const uint16_t SM_E2X_ID = 242; // needs to be less than 256 

__attribute__((unused)) static
const char* SM_E2X_STR = "E2X_STATS_V0"; 

static
const uint16_t SM_E2X_REV = 1; 

__attribute__((unused)) static
const char SM_E2X_SHORT_NAME[] = "E2SM-E2X";

//iso(0) identified-organization(0)
//dod(0) internet(0) private(0)
//enterprise(0) 53148 e2(0)
// version1 (1) e2sm(147) e2sm-RC-
// IEs (0)

__attribute__((unused)) static
const char SM_E2X_OID[] = "0.0.0.0.0.0.0.0.1.1042.0"; 

__attribute__((unused)) static
const char SM_E2X_DESCRIPTION[] = "E2X Service Model";

#endif

