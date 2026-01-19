#ifndef LIST_DL_SCHE_CTRL_LLC_E2SM_MIR_H
#define LIST_DL_SCHE_CTRL_LLC_E2SM_MIR_H 

#include "dl_sched_ctrl.h"
#include <stdbool.h>

typedef struct{
  //[1,63]
  size_t sz_dl_sched_ctrl; 
  dl_sched_ctrl_t* dl_sched_ctrl;
} lst_dl_sched_ctrl_t;

lst_dl_sched_ctrl_t cp_lst_dl_sched_ctrl(lst_dl_sched_ctrl_t const* src);

void free_lst_dl_sched_ctrl(lst_dl_sched_ctrl_t* src);

bool eq_lst_dl_sched_ctrl(lst_dl_sched_ctrl_t const* m0, lst_dl_sched_ctrl_t const* m1);

#endif
