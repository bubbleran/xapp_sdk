#ifndef XAPP_SUB_ALL_SM_CONF_MIR_H
#define XAPP_SUB_ALL_SM_CONF_MIR_H 

#ifdef __cplusplus
extern "C" {
#endif

#include "xapp_sub_cust_sm_conf.h"
#include "xapp_sub_oran_sm_conf.h"

typedef struct{
  // CUSTOM
  sub_cust_sm_conf_t cust;
  // ORAN
  sub_oran_sm_conf_t oran;
} sub_all_sm_conf_t;

sub_all_sm_conf_t init_sub_all_sm_conf(const char* file);

void free_sub_all_sm_conf(sub_all_sm_conf_t*);

#ifdef __cplusplus
}
#endif

#endif
