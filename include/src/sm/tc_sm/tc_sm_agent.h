#ifndef TC_SERVICE_MODEL_AGENT_H
#define TC_SERVICE_MODEL_AGENT_H

#include <stddef.h>
#include <stdint.h>

#include "../sm_agent.h"

__attribute__ ((visibility ("default"))) 
sm_agent_t* make_tc_sm_agent(sm_io_ag_ran_t const* io);

#endif

