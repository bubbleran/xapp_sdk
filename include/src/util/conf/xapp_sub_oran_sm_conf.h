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

#ifndef XAPP_SUB_ORAN_SM_CONF_MIR_H
#define XAPP_SUB_ORAN_SM_CONF_MIR_H 

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>

typedef enum{
  STRING_ACT_NAME_ID_E,
  INT32_ACT_NAME_ID_E,
  END_ACT_NAME_ID_E
} act_name_id_e;

typedef struct {
  act_name_id_e type;
  union{  
    char* name;
    int32_t id;
  };
} act_name_id_t;

void free_act_name_id(act_name_id_t*);

typedef struct{
  char* name;
  size_t periodicity_ms;
  size_t format;
  char* ran_type;
  size_t sz_act;
  act_name_id_t* actions;
} elm_oran_sm_conf_t;

void free_elm_oran_sm_conf(elm_oran_sm_conf_t*);

typedef struct{
  uint32_t runtime_sec;
  elm_oran_sm_conf_t* elm;
  size_t sz_elm;
} sub_oran_sm_conf_t;

sub_oran_sm_conf_t init_sub_oran_sm_conf(const char* file);

sub_oran_sm_conf_t init_no_license_sub_oran_sm_conf(const char* file);

void free_sub_oran_sm_conf(sub_oran_sm_conf_t* conf);

#ifdef __cplusplus
}
#endif

#endif

