/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "../../../../util/byte_array.h"

typedef struct {
  // Attribute name
  // Mandatory
  // 9.3.8
  byte_array_t attribute_name;
} attribute_t;

void free_attribute(attribute_t* src);

bool eq_attribute(attribute_t const* m0, attribute_t const* m1);

attribute_t cp_attribute(attribute_t const* src);

#endif

