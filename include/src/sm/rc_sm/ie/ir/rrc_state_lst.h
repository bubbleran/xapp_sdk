#ifndef RRC_STATE_LIST_E2SM_H
#define RRC_STATE_LIST_E2SM_H 

#include <stdbool.h>
#include <stdlib.h>

#include "rrc_state.h"

typedef struct {

  // 9.3.37
  // [1 - 8]
  size_t sz_rrc_state;
  rrc_state_t* state_chng_to;

} rrc_state_lst_t ;

void free_rrc_state_lst(rrc_state_lst_t* src);

bool eq_rrc_state_lst(rrc_state_lst_t const* m0, rrc_state_lst_t const* m1);

rrc_state_lst_t cp_rrc_state_lst( rrc_state_lst_t const* src);

#endif

