#ifndef RIC_ACTION_DEFINITION_MIR_KPM_V3_H
#define RIC_ACTION_DEFINITION_MIR_KPM_V3_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include "kpm_ric_action_def_frm_1.h"
#include "kpm_ric_action_def_frm_2.h"
#include "kpm_ric_action_def_frm_3.h"
#include "kpm_ric_action_def_frm_4.h"
#include "kpm_ric_action_def_frm_5.h"



 // 8.3.3
 // 6.2.2.2 RIC Style Type => here enum values !!!
 // Defined as an INTEGER
typedef enum{
  STYLE_1_RIC_SERVICE_REPORT,
  STYLE_2_RIC_SERVICE_REPORT,
  STYLE_3_RIC_SERVICE_REPORT,
  STYLE_4_RIC_SERVICE_REPORT,
  STYLE_5_RIC_SERVICE_REPORT,

  END_RIC_SERVICE_REPORT,

} ric_service_report_e ;

/*
* RIC Style Type 1:  E2 Node Measurement. Used to carry measurement report from a target E2 Node. More in details, 
*                    it contains measurement types that Near-RT RIC is requesting to subscribe followed by a list 
*                    of subcounters to be measured for each measurement type, and a granularity period
*                    indicating collection interval of those measurements.
* RIC Style Type 2: Used to carry measurement report for a single UE of interest from a target E2 Node
* RIC Style Type 3: Used to carry UE-level measurement report for a group of UEs per
*                   measurement type matching subscribed conditions from a target E2 Node
* RIC Style Type 4: Used to carry measurement report for a group of UEs across a set of
*                   measurement types satisfying common subscribed conditions from a target E2 Node
* RIC Style Type 5: Used to carry measurement report for multiple UE of interest from a target E2 Node
*/

typedef enum {
  FORMAT_1_ACTION_DEFINITION,
  FORMAT_2_ACTION_DEFINITION,
  FORMAT_3_ACTION_DEFINITION,
  FORMAT_4_ACTION_DEFINITION,
  FORMAT_5_ACTION_DEFINITION,

  END_ACTION_DEFINITION

} format_action_def_e;

//  8.2.1.2  RIC ACTION DEFINITION IE

typedef struct{
    format_action_def_e type; 
    union{
        kpm_act_def_format_1_t frm_1;  // 8.2.1.2.1
        kpm_act_def_format_2_t frm_2;  // 8.2.1.2.2
        kpm_act_def_format_3_t frm_3;  // 8.2.1.2.3
        kpm_act_def_format_4_t frm_4;  // 8.2.1.2.4
        kpm_act_def_format_5_t frm_5;  // 8.2.1.2.5
    };

} kpm_act_def_t;

void free_kpm_action_def(kpm_act_def_t * src);

bool eq_kpm_action_def(kpm_act_def_t const * m0, kpm_act_def_t const * m1);

#ifdef __cplusplus
}
#endif

#endif

// done
