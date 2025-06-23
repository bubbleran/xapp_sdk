#ifndef ELEMENT_YAML_MIR_H
#define ELEMENT_YAML_MIR_H 

#include "kv_pair_yaml.h"

typedef struct elm{
  kv_pair_yaml_t kv;  
  int indentation;
} elm_yaml_t;

void free_elm_yaml(elm_yaml_t*);

#endif
