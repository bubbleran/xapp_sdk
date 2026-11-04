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

#ifndef XAPP_SUB_CUST_SM_CONF_MIR_H
#define XAPP_SUB_CUST_SM_CONF_MIR_H 

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

typedef struct{
  char* name;
  size_t periodicity_ms;
} sub_cust_sm_t;

void free_sub_cust_sm(sub_cust_sm_t*);

typedef struct{
  size_t runtime_sec;
  sub_cust_sm_t* sub_cust_sm;
  size_t sz_sub_cust_sm;
} sub_cust_sm_conf_t;

sub_cust_sm_conf_t init_sub_cust_sm_conf(const char* file);

sub_cust_sm_conf_t init_no_license_sub_cust_sm_conf(const char* file);

void free_sub_cust_sm_conf(sub_cust_sm_conf_t* conf);

#ifdef __cplusplus
}
#endif

#endif
