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

#ifndef E2_AGENT_CONF_MIR_H
#define E2_AGENT_CONF_MIR_H 

#include <stdint.h>

typedef struct{
  char* ip_ric;
  uint32_t e2_port;
  char* ip_ag;
  char* sm_dir;
  uint32_t log_level;
#ifdef LICENSE_AGENT
  //char* license_path;
  char* license_br_path;
  char* sign_path;
#endif
} e2_agent_conf_t;

e2_agent_conf_t init_e2_agent_conf(const char* file);

void free_e2_agent_conf(e2_agent_conf_t*);

#endif
