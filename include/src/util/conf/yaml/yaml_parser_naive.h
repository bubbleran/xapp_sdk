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

#ifndef YAML_PARSER_NAIVE_MIR_H
#define YAML_PARSER_NAIVE_MIR_H 

#include "../../alg_ds/ds/seq_container/seq_arr.h"
#include "elm_yaml.h"

typedef struct{
  // elm_t
  seq_arr_t arr;
} yaml_parser_naive_t;

typedef struct{
  elm_yaml_t const* elm;
  bool found;
} opt_elm_t;

typedef struct{
  char const* str;
  size_t len;
} str_view_t;

yaml_parser_naive_t init_yaml_parser_naive(char const* file_path);
yaml_parser_naive_t init_yaml_parser_naive_buffer(uint8_t const* buffer, size_t sz);

void free_yaml_parser_naive(yaml_parser_naive_t*);

opt_elm_t find_elm_yaml_parser_naive(yaml_parser_naive_t const* yaml, str_view_t key);

opt_elm_t find_subtree_yaml_parser_naive(yaml_parser_naive_t const* yaml, str_view_t key, elm_yaml_t const* src);

seq_arr_t subtree_yaml_parser_naive(yaml_parser_naive_t const* yaml, elm_yaml_t const* src);

elm_yaml_t* next_elm_yaml_parser_naive(yaml_parser_naive_t const* yaml, elm_yaml_t const* elm);
 
#endif

