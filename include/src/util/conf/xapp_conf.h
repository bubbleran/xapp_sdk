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

#ifndef XAPP_CONFIGURATION_MIR_H
#define XAPP_CONFIGURATION_MIR_H 

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
  char* ip;
  char* dir;
  char* filename;
  char* usr;
  char* psw;
  uint32_t port;
} db_xapp_conf_t;

void free_db_xapp_conf(db_xapp_conf_t* db);

typedef struct{
  char* ip_ric;
  char* ip_xapp;
  char* sm_dir;
  db_xapp_conf_t* db;
  uint32_t e42_port;
  uint32_t log_level;
} xapp_conf_t;

xapp_conf_t init_xapp_conf(const char* file);

void free_xapp_conf(xapp_conf_t*);

#ifdef __cplusplus
}
#endif


#endif
