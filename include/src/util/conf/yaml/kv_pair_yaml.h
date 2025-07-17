#ifndef KV_PAIR_YAML_MIR_H
#define KV_PAIR_YAML_MIR_H 

#include "val_yaml.h"
#include <stdlib.h>

typedef struct{
  char* str;
  size_t len;
} str_own_t;

typedef struct{
  str_own_t key;
  val_yaml_t val;
} kv_pair_yaml_t;

void free_kv_pair_yaml(kv_pair_yaml_t*);

#endif
