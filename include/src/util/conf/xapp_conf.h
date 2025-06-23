#ifndef XAPP_CONFIGURATION_MIR_H
#define XAPP_CONFIGURATION_MIR_H 

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
  char* ip;
  char* dir;
  char* filename;
  char* usr;
  char* psw;
} db_xapp_conf_t;

void free_db_xapp_conf(db_xapp_conf_t* db);

typedef struct{
  char* ip_ric;
  char* ip_xapp;
  char* sm_dir;
  db_xapp_conf_t* db;
  uint32_t e42_port;
  uint32_t log_level;
} xapp_conf_t;

xapp_conf_t init_xapp_conf(const char* file);

void free_xapp_conf(xapp_conf_t*);

#ifdef __cplusplus
}
#endif


#endif
