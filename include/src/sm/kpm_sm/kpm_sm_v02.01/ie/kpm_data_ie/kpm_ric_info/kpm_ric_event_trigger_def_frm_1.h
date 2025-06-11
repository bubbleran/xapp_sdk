#ifndef RIC_EVENT_TRIGGER_DEFINITION_FORMAT_1_KPM_V2_01_H
#define RIC_EVENT_TRIGGER_DEFINITION_FORMAT_1_KPM_V2_01_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

// 8.2.1.1.1  E2SM-KPM Event Trigger Definition Format 1

typedef struct {

    uint32_t report_period_ms; // [1, 4294967295] reporting period in milliseconds

} kpm_ric_event_trigger_format_1_t;

bool eq_kpm_event_trigger_def_frm_1(kpm_ric_event_trigger_format_1_t const* m0,  kpm_ric_event_trigger_format_1_t const* m1);

kpm_ric_event_trigger_format_1_t cp_kpm_event_trigger_def_frm_1(const kpm_ric_event_trigger_format_1_t * src);


#ifdef __cplusplus
}
#endif

#endif

// done
