#ifndef E2_AGENT_AMARISOFT_CONF_MIR_H
#define E2_AGENT_AMARISOFT_CONF_MIR_H 

#include <stdint.h>

typedef struct {
  char* conf_yaml;
  char* ip_amr;
  uint32_t port_amr;
  uint32_t log_level;
} e2ag_amr_conf_t;

e2ag_amr_conf_t init_e2ag_amr_conf(const char* file_path);

void free_e2ag_amr_conf(e2ag_amr_conf_t*);

#endif
