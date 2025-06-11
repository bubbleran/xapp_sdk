#ifndef MEASUREMENT_DATA_LIST_KPM_V2_01_H
#define MEASUREMENT_DATA_LIST_KPM_V2_01_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "enum_value.h"

/* Intermediate structures for  8.2.1.4  RIC INDICATION MESSAGE IE */

typedef enum {
	INTEGER_MEAS_VALUE,
	REAL_MEAS_VALUE,
	NO_VALUE_MEAS_VALUE,

	END_MEAS_VALUE

} meas_value_e;

typedef struct {
	meas_value_e value;
	union {
		uint32_t   int_val;  // [0..4294967295]
		double	   real_val;
		void*      no_value; 
	};

} meas_record_lst_t;

meas_record_lst_t cp_meas_record_lst(meas_record_lst_t const* src);

typedef struct {
    size_t                    meas_record_len;  // [1, 65535]
	meas_record_lst_t        *meas_record_lst; 
	enum_value_e	         *incomplete_flag;  // OPTIONAL, Indicates that the measurements record is not reliable.

} meas_data_lst_t;

meas_data_lst_t cp_meas_data_lst(meas_data_lst_t const* src);

bool eq_meas_data_lst(meas_data_lst_t const* m0, meas_data_lst_t const* m1);

#ifdef __cplusplus
}
#endif

#endif

// done
