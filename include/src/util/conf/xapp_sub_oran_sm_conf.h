#ifndef XAPP_SUB_ORAN_SM_CONF_MIR_H
#define XAPP_SUB_ORAN_SM_CONF_MIR_H 

#include <stdlib.h>
#include <stdint.h>

typedef enum{
  STRING_ACT_NAME_ID_E,
  INT32_ACT_NAME_ID_E,
  END_ACT_NAME_ID_E
} act_name_id_e;

typedef struct {
  act_name_id_e type;
  union{  
    char* name;
    int32_t id;
  };
} act_name_id_t;

void free_act_name_id(act_name_id_t*);

typedef struct{
  char* name;
  size_t periodicity_ms;
  size_t format;
  char* ran_type;
  size_t sz_act;
  act_name_id_t* actions;
} elm_oran_sm_conf_t;

void free_elm_oran_sm_conf(elm_oran_sm_conf_t*);

typedef struct{
  uint32_t runtime_sec;
  elm_oran_sm_conf_t* elm;
  size_t sz_elm;
} sub_oran_sm_conf_t;

sub_oran_sm_conf_t init_sub_oran_sm_conf(const char* file);

sub_oran_sm_conf_t init_no_license_sub_oran_sm_conf(const char* file);

void free_sub_oran_sm_conf(sub_oran_sm_conf_t* conf);

#endif


