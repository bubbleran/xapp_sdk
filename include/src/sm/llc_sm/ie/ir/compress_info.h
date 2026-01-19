#ifndef COMPRESS_INFO_LLC_E2SM_MIR_H
#define COMPRESS_INFO_LLC_E2SM_MIR_H 

#include "../../../../util/byte_array.h"
#include <stdbool.h>


typedef struct{
  // Precoder Compression Header
  // Mandatory
  byte_array_t hdr;

  // Precoder Compression Parameters
  // Mandatory
  byte_array_t params; 

} compress_info_t;

compress_info_t cp_compress_info(compress_info_t const* src);

void free_compress_info(compress_info_t* src);

bool eq_compress_info(compress_info_t const* m0, compress_info_t const* m1);

#endif
