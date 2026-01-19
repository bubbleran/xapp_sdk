#ifndef SEQ_CTRL_ACT_LLC_E2SM_MIR_H 
#define SEQ_CTRL_ACT_LLC_E2SM_MIR_H  

#include <stdbool.h>
#include <stdint.h>
#include "../../../../util/byte_array.h"


typedef struct{
  // Control Action ID
  // Mandatory
  // 8.3.6
  // [1-65535]
  uint16_t id; 

  // Control Action Name
  // Mandatory
  // 8.3.7
  // [1-150]
  byte_array_t name;

} seq_ctrl_act_llc_t;

seq_ctrl_act_llc_t cp_seq_ctrl_act_llc(seq_ctrl_act_llc_t const* src);

void free_seq_ctrl_act_llc(seq_ctrl_act_llc_t* src);

bool eq_seq_ctrl_act_llc(seq_ctrl_act_llc_t const* m0, seq_ctrl_act_llc_t const* m1);


#endif
