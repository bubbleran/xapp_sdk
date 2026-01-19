#ifndef E2SM_LLC_CTRL_HDR_FORMT_1_MIR_H
#define E2SM_LLC_CTRL_HDR_FORMT_1_MIR_H 

#include <stdbool.h>
#include <stdint.h>

// 8.2.1.6.1
typedef struct{
  //8.3.3
  //RIC Style Type 
  //Mandatory
  uint32_t ric_style_type;

  //8.3.6
  //Control Action ID 
  //Mandatory 
  //[1, 65535]
  uint32_t ctrl_act_id;

} e2sm_llc_ctrl_hdr_frmt_1_t ;

e2sm_llc_ctrl_hdr_frmt_1_t cp_e2sm_llc_ctrl_hdr_frmt_1(e2sm_llc_ctrl_hdr_frmt_1_t const* src);

void free_e2sm_llc_ctrl_hdr_frmt_1(e2sm_llc_ctrl_hdr_frmt_1_t* src);

bool eq_e2sm_llc_ctrl_hdr_frmt_1(e2sm_llc_ctrl_hdr_frmt_1_t const* m0, e2sm_llc_ctrl_hdr_frmt_1_t const* m1);

#endif
