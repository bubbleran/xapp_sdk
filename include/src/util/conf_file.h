#ifndef FLEXRIC_CONFIGURATION_FILE_H
#define FLEXRIC_CONFIGURATION_FILE_H 

#include <stdint.h>
#include <stdbool.h>

#define FR_CONF_FILE_LEN 128
#define MAX_NUM_CUST_SM 6
#define MAX_NUM_ORAN_SM 8 // consider diff ran type

typedef struct {
    char* name;
    char* time;
} sub_cust_sm_t;

typedef struct {
// TODO: add enum for type name and id
    char* name;
    int32_t id;
} act_name_id_t;

typedef struct {
    char* name;
    int32_t time;
    int32_t format;
    char* ran_type;
    int32_t act_len;
    act_name_id_t* actions;
} sub_oran_sm_t;

typedef struct{
    bool enable;
    char* ip;
    char* dir;
    char* filename;
    char* user;
    char* pass;
} db_params_t;

typedef struct {
  char* ric;
  char* e2ag;
  char* xapp;
} ip_addr_t;

typedef struct {
  char conf_file[FR_CONF_FILE_LEN];
  char* libs_dir;

  ip_addr_t ip;
  int32_t e2_port;
  int32_t e42_port;

  int32_t sub_cust_sm_len;
  sub_cust_sm_t sub_cust_sm[MAX_NUM_CUST_SM];
  int32_t sub_oran_sm_len;
  sub_oran_sm_t sub_oran_sm[MAX_NUM_ORAN_SM];

  db_params_t db_params;
  
  // 0-trace; 1-debug; 2-info
  // 3-warn; 4-error; 5-fatal
  int32_t log_level;
} fr_args_t;

fr_args_t init_fr_args(int argc, char* argv[]);

void free_fr_args(fr_args_t* args);

typedef struct{
  char conf_file[FR_CONF_FILE_LEN];
  char* libs_dir;

  char* ric_ip;
  int32_t e2_port;
  char* ip;
  int32_t port;

  // 0-trace; 1-debug; 2-info
  // 3-warn; 4-error; 5-fatal
  int32_t log_level;
} args_proxy_ag_t; // Adapt this one

args_proxy_ag_t init_args_proxy_ag(int argc, char* argv[]);

void free_args_proxy_ag(args_proxy_ag_t* src);

#endif

