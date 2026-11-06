/*

Copyright (C) 2026 BubbleRAN

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see http://www.gnu.org/licenses/.
*/

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
