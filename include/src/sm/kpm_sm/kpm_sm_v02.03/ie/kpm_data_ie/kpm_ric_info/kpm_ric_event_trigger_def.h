#ifndef RIC_EVENT_TRIGGER_DEFINITION_KPM_V2_H
#define RIC_EVENT_TRIGGER_DEFINITION_KPM_V2_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "kpm_ric_event_trigger_def_frm_1.h"

typedef enum {
    STYLE_1_RIC_EVENT_TRIGGER,

    END_STYLE_RIC_EVENT_TRIGGER

} style_ric_event_trigger_e;

typedef enum {
    FORMAT_1_RIC_EVENT_TRIGGER,

    END_FORMAT_RIC_EVENT_TRIGGER

} format_ric_event_trigger_e;


// 8.2.1.1    RIC EVENT TRIGGER DEFINITION IE

typedef struct {
    format_ric_event_trigger_e type;
    union {
        kpm_ric_event_trigger_format_1_t kpm_ric_event_trigger_format_1;
    };

} kpm_event_trigger_def_t;

void free_kpm_event_trigger_def(kpm_event_trigger_def_t* src);

bool eq_kpm_event_trigger_def( kpm_event_trigger_def_t const* m0,  kpm_event_trigger_def_t const* m1);

kpm_event_trigger_def_t cp_kpm_event_trigger_def(const kpm_event_trigger_def_t * src);

#ifdef __cplusplus
}
#endif

#endif

// done
