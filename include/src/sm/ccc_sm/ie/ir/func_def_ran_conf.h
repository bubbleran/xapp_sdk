/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef FUNC_DEF_RAN_CONF_H
#define FUNC_DEF_RAN_CONF_H

#include "attribute.h"
#include "../../../../util/byte_array.h"
#include "report_type.h"
#include "supported_services.h"

typedef struct {
  // Attribute name
  // Mandatory
  // 9.3.8
  byte_array_t attribute_name;

  // Supported Services
  // Mandatory
  // 9.2.2.2
  supported_services_t supported_services;

} lst_sp_attributes_t;

typedef struct {
  // RAN configuration structure name
  // Mandatory
  // 9.3.7
  byte_array_t ran_conf_str_name;

  // List of supported attributes
  // [0..65535]
  size_t sz_lst_sp_attributes;
  lst_sp_attributes_t* lst_sp_attributes;

} func_def_ran_conf_t;

void free_func_def_ran_conf(func_def_ran_conf_t* src);

bool eq_func_def_ran_conf(func_def_ran_conf_t const* m0, func_def_ran_conf_t const* m1);

func_def_ran_conf_t cp_func_def_ran_conf(func_def_ran_conf_t const* src);

#endif

