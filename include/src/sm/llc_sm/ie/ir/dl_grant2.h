#ifndef DL_GRANT2_E2SM_LLC_MIR_H
#define DL_GRANT2_E2SM_LLC_MIR_H 

#include "not_fully_exec.h"
#include <stdbool.h>

typedef enum{
  FULLY_EXECUTED_EXECUTION_LEVEL_E,
  NOT_FULLY_EXECUTED_EXECUTION_LEVEL_E,
  END_FULLY_EXECUTED_EXECUTION_LEVEL_E,
} execution_level_e ;

// From 8.3.27
// List of DL Grants
typedef struct{

  // Grant ID 
  // Mandatory
  uint32_t grant_id;

  execution_level_e execution_level; 

  // Only applies when exec_level NOT_FULLY_EXECUTED_EXECUTION_LEVEL_E !!!!
  union{
    not_fully_exec_t not_fully_exec;
  };

} dl_grant2_t;

dl_grant2_t cp_dl_grant2(dl_grant2_t const* src);

void free_dl_grant2(dl_grant2_t* src); 

bool eq_dl_grant2(dl_grant2_t const* m0, dl_grant2_t const* m1); 

#endif
