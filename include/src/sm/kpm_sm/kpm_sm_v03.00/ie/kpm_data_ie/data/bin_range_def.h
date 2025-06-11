#ifndef BIN_RANGE_DEFINITION_KPM_V3_H
#define BIN_RANGE_DEFINITION_KPM_V3_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

// 8.3.27  Bin Range Value
typedef struct {
  enum {INTEGER_BIN_RANGE, REAL_BIN_RANGE, END_BIN_RANGE} value;
  union {
    unsigned long int_value;
    double real_value;
  };
  
  
} bin_range_value_t;


typedef struct {
  uint16_t bin_index;

  bin_range_value_t start_value;
  bin_range_value_t end_value;

} bin_distr_t;


// 8.3.26   Bin Range Definition
typedef struct {
  size_t bin_x_lst_len;  // [1, 65535]
  bin_distr_t *bin_x_lst;

  size_t bin_y_lst_len;  // [0, 65535]
  bin_distr_t *bin_y_lst;

  size_t bin_z_lst_len;  // [0, 65535]
  bin_distr_t *bin_z_lst;

} bin_range_def_t;

void free_kpm_bin_range_def(bin_range_def_t* src);

bool eq_kpm_bin_range_def(bin_range_def_t const * m0, bin_range_def_t const * m1);

bool eq_kpm_bin_range_def_wrapper(void const * m0, void const * m1);

#ifdef __cplusplus
}
#endif

#endif

// done
