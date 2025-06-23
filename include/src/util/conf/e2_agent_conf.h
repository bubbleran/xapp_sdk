#ifndef E2_AGENT_CONF_MIR_H
#define E2_AGENT_CONF_MIR_H 

#include <stdint.h>

typedef struct{
  char* ip_ric;
  uint32_t e2_port;
  char* ip_ag;
  char* sm_dir;
  uint32_t log_level;
} e2_agent_conf_t;

e2_agent_conf_t init_e2_agent_conf(const char* file);

void free_e2_agent_conf(e2_agent_conf_t*);

#endif
