#ifndef VALUE_YAML_MIR_H
#define VALUE_YAML_MIR_H 

#include <stdint.h>

typedef enum{
  INT64_val_e,
  FLOAT64_val_e,
  STRING_val_e,
  LIST_INT64_val_e,
  LIST_FLOAT64_val_e,
  LIST_STRING_val_e,
  NESTED_or_LIST_val_e,
  END_val_e
} val_yaml_e;

typedef struct{
  val_yaml_e type;
  union{
    int64_t i64;
    double f64;
    char* str;
  };
} val_yaml_t;

void free_val_yaml(val_yaml_t*);

#endif
