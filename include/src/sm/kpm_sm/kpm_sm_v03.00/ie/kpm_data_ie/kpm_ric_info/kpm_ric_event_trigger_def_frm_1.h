#ifndef RIC_EVENT_TRIGGER_DEFINITION_FORMAT_1_KPM_V3_H
#define RIC_EVENT_TRIGGER_DEFINITION_FORMAT_1_KPM_V3_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// 8.2.1.1.1  E2SM-KPM Event Trigger Definition Format 1

typedef struct {

    uint32_t report_period_ms; // [1, 4294967295] reporting period in milliseconds

} kpm_ric_event_trigger_format_1_t;

#ifdef __cplusplus
}
#endif

#endif

// done
