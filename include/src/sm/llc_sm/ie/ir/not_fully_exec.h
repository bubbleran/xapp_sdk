#ifndef NOT_FULLY_EXEC_E2SM_LLC_MIR_H
#define NOT_FULLY_EXEC_E2SM_LLC_MIR_H 

#include "schd_log_chnl.h"
#include <stdbool.h>
#include <stdlib.h>

// From 8.3.27
// List of DL Grants

typedef struct{

  // List of Scheduled Logical Channels
  // [1,63]
  size_t sz_schd_log_chnl; 
  schd_log_chnl_t* schd_log_chnl;

} not_fully_exec_t;

not_fully_exec_t cp_not_fully_exec(not_fully_exec_t const* src);

void free_not_fully_exec(not_fully_exec_t* src);

bool eq_not_fully_exec(not_fully_exec_t const* m0, not_fully_exec_t const* m1);

#endif
