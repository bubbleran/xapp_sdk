#ifndef E2_NODE_INFO_CHANGE_H
#define E2_NODE_INFO_CHANGE_H

#include "ev_trigger_cell_info.h"
#include "logical_or.h"

#include <stdbool.h>
#include <stdint.h>

typedef struct{

  //Event Trigger Condition ID
  //Mandatory
  //9.3.21
  // INTEGER (1..65535, …)
  uint16_t ev_trigger_cond_id;

  // E2 Node Information Change ID
  // Mandatory
  // INTEGER (1..512, ...)
  uint16_t e2_node_info_chng_id;

  // Associated Cell Info
  // Optional
  // 9.3.27
  ev_trigger_cell_info_t* ev_trigger_cell_info;

  // Logical OR
  // Optional
  // 9.3.25
  logical_or_e* log_or; 

} e2_node_info_chng_t;

void free_e2_node_info_chng(e2_node_info_chng_t* src);

bool eq_e2_node_info_chng(e2_node_info_chng_t const* m0, e2_node_info_chng_t const* m1);

e2_node_info_chng_t cp_e2_node_info_chng( e2_node_info_chng_t const* src);

#endif

