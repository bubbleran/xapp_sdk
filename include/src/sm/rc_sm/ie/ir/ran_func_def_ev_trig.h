#ifndef RAN_FUNC_DEF_EV_TRIG_H
#define RAN_FUNC_DEF_EV_TRIG_H

#include <stdbool.h>
#include <stddef.h>
#include "seq_ev_trg_style.h"
#include "seq_ran_param_3.h"
#include "seq_call_proc_type.h"


// 9.2.2.2
typedef struct{
  // Sequence of EVENT TRIGGER styles
  // [1 - 63]
  size_t sz_seq_ev_trg_style;
  seq_ev_trg_style_t* seq_ev_trg_style;

  // Sequence of RAN Parameters for L2 Variables
  // [0 - 65535]  
  size_t sz_seq_ran_param_l2_var;
  seq_ran_param_3_t * seq_ran_param_l2_var;

  //Sequence of Call Process Types
  // [0-65535]
  size_t sz_seq_call_proc_type;
  seq_call_proc_type_t* seq_call_proc_type;

  // Sequence of RAN Parameters for Identifying UEs
  // 0-65535
  size_t sz_seq_ran_param_id_ue;
  seq_ran_param_3_t* seq_ran_param_id_ue;

  // Sequence of RAN Parameters for Identifying Cells
  // 0-65535
  size_t sz_seq_ran_param_id_cell;
  seq_ran_param_3_t* seq_ran_param_id_cell;

} ran_func_def_ev_trig_t;

void free_ran_func_def_ev_trig(ran_func_def_ev_trig_t* src);

bool eq_ran_func_def_ev_trig(ran_func_def_ev_trig_t const* m0, ran_func_def_ev_trig_t const* m1);

ran_func_def_ev_trig_t cp_ran_func_def_ev_trig(ran_func_def_ev_trig_t const* src);


#endif


