#ifndef RIC_CONFIGURATION_MIR_H
#define RIC_CONFIGURATION_MIR_H 

#include <stdint.h>

typedef struct{
  char* ip;
  char* sm_dir;
  uint32_t e2_port;
  uint32_t e42_port;
  uint32_t log_level;
} ric_conf_t;

ric_conf_t init_ric_conf(const char* file);

void free_ric_conf(ric_conf_t*);

#endif
