#ifndef LIST_LLI_EVENT_TRIGGER_MIR_H
#define LIST_LLI_EVENT_TRIGGER_MIR_H 

#include "assoc_ue_info_llc.h"
#include "ev_trg_ue_info.h"
#include "logical_or_llc.h"
#include "lower_layer_info.h"

typedef struct{
  // 8.3.9
  // Event Trigger Condition ID
  // Mandatory
  // (1..65535, …)
  uint32_t ev_trg_cond_id;  

  // 8.3.15
  // Lower Layers Information Type
  // Mandatory 
  lower_layer_info_e lower_layer_info;

  // 8.3.12
  // Associated UE Info  
  // Optional
  ev_trg_ue_info_t* assoc_ue_info;

  // 8.3.11
  // Logical OR 
  // Optional
  logical_or_llc_e* logical_or;

} lst_lli_ev_trg_t;

lst_lli_ev_trg_t cp_lst_lli_ev_trg(lst_lli_ev_trg_t const* src);

void free_lst_lli_ev_trg(lst_lli_ev_trg_t* src);

bool eq_lst_lli_ev_trg(lst_lli_ev_trg_t const* m0, lst_lli_ev_trg_t const* m1);

#endif
