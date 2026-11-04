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

#ifndef RIC_CONFIGURATION_MIR_H
#define RIC_CONFIGURATION_MIR_H 

#include <stdint.h>

typedef struct{
  char* ip;
  char* sm_dir;
  uint32_t e2_port;
  uint32_t e42_port;
  uint32_t log_level;
#ifdef LICENSE_RIC
  char* license_path;
  char* signature_path;
#endif
} ric_conf_t;

ric_conf_t init_ric_conf(const char* file);

void free_ric_conf(ric_conf_t*);

#endif
