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

#ifndef CONFIGURATION_FLEXRIC_MIR_H
#define CONFIGURATION_FLEXRIC_MIR_H 
#include "yaml/yaml_parser_naive.h"

char* get_sm_dir(yaml_parser_naive_t const* yaml, elm_yaml_t const* elm);

uint32_t get_log(yaml_parser_naive_t const* yaml, elm_yaml_t const* elm);

char* get_ip(yaml_parser_naive_t const* yaml, elm_yaml_t const* elm, char const* ip_str);

uint32_t get_port(yaml_parser_naive_t const* yaml, elm_yaml_t const* elm, const char* port_str);

char* get_conf_str(yaml_parser_naive_t const* yaml, elm_yaml_t const* elm, char const* str);

char* maybe_get_conf_str(yaml_parser_naive_t const* yaml, elm_yaml_t const* elm, char const* str);

int64_t get_conf_i64(yaml_parser_naive_t const* yaml, elm_yaml_t const* elm, char const* str);

elm_yaml_t const* get_conf_nested(yaml_parser_naive_t const* yaml, elm_yaml_t const* elm, char const* str);


#endif
