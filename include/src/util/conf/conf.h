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
