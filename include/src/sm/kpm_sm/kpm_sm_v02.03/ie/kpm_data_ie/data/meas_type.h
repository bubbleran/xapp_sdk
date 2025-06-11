#ifndef MEASUREMENT_TYPE_KPM_V2_H
#define MEASUREMENT_TYPE_KPM_V2_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include "../../../../../../util/byte_array.h"

typedef struct {
    enum {NAME_MEAS_TYPE, ID_MEAS_TYPE, END_MEAS_TYPE} type;
    union {
        byte_array_t name; // 8.3.9
        uint16_t id; // 8.3.10
    };

} meas_type_t;

bool eq_meas_type(meas_type_t const * m0, meas_type_t const * m1);

meas_type_t cp_meas_type(meas_type_t const* src);

#ifdef __cplusplus
}
#endif

#endif

