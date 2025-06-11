/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
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

