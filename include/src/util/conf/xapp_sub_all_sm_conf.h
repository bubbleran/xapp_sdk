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

#ifndef XAPP_SUB_ALL_SM_CONF_MIR_H
#define XAPP_SUB_ALL_SM_CONF_MIR_H 

#ifdef __cplusplus
extern "C" {
#endif

#include "xapp_sub_cust_sm_conf.h"
#include "xapp_sub_oran_sm_conf.h"

typedef struct{
  // CUSTOM
  sub_cust_sm_conf_t cust;
  // ORAN
  sub_oran_sm_conf_t oran;
} sub_all_sm_conf_t;

sub_all_sm_conf_t init_sub_all_sm_conf(const char* file);

void free_sub_all_sm_conf(sub_all_sm_conf_t*);

#ifdef __cplusplus
}
#endif

#endif
