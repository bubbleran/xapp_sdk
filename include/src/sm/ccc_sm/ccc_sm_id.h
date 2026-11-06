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

#ifndef CCC_SERVICE_MODEL_ID_H
#define CCC_SERVICE_MODEL_ID_H


/*
 * Service Model ID needed for the agent as well as for the ric to ensure that they match. 
 */

#include <stdint.h>

static
const uint16_t SM_CCC_ID = 4;


static
const uint16_t SM_CCC_REV = 1;

#define SM_CCC_SHORT_NAME "ORAN-E2SM-CCC"
//iso(1) identified-organization(3)
//dod(6) internet(1) private(4)
//enterprise(1) 53148 e2(1)
// version1 (1) e2sm(2) e2sm-CCC-IEs (4)

#define SM_CCC_OID "1.3.6.1.4.1.53148.1.1.2.4"

#define SM_CCC_DESCRIPTION "Cell Configuration and Control"

#endif

