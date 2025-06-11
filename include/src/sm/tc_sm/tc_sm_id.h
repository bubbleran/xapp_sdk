#ifndef TC_SERVICE_MODEL_ID_H
#define TC_SERVICE_MODEL_ID_H 


/*
 * Service Model ID needed for the agent as well as for the ric to ensure that they match. 
 */

#include <stdint.h>

static
const uint16_t SM_TC_ID = 146; 

__attribute__((unused)) static
const char* SM_TC_STR = "TC_STATS_V0"; 

static
const uint16_t SM_TC_REV = 1; 

__attribute__((unused)) static
const char SM_TC_SHORT_NAME[] = "E2SM-TC";

//iso(0) identified-organization(0)
//dod(0) internet(0) private(0)
//enterprise(0) 53148 e2(0)
// version1 (1) e2sm(145) e2sm-RC-
// IEs (0)

__attribute__((unused)) static
const char SM_TC_OID[] = "0.0.0.0.0.0.0.0.1.146.0"; 

__attribute__((unused)) static
const char SM_TC_DESCRIPTION[] = "TC Service Model";

#endif

