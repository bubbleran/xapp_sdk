#ifndef XAPP_SUB_CUST_SM_CONF_MIR_H
#define XAPP_SUB_CUST_SM_CONF_MIR_H 

#include <stdlib.h>

typedef struct{
  char* name;
  size_t periodicity_ms;
} sub_cust_sm_t;

void free_sub_cust_sm(sub_cust_sm_t*);

typedef struct{
  size_t runtime_sec;
  sub_cust_sm_t* sub_cust_sm;
  size_t sz_sub_cust_sm;
} sub_cust_sm_conf_t;

sub_cust_sm_conf_t init_sub_cust_sm_conf(const char* file);

sub_cust_sm_conf_t init_no_license_sub_cust_sm_conf(const char* file);

void free_sub_cust_sm_conf(sub_cust_sm_conf_t* conf);

#endif
