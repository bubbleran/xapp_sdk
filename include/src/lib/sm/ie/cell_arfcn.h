/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef SERVING_CELL_ARFCN_MIR_H
#define SERVING_CELL_ARFCN_MIR_H 
#include <stdint.h>
#include <stdbool.h>
#include "rat_type.h"

// 9.3.40
// 6.2.2.15
typedef struct{
  // CHOICE RAT type
  // Mandatory
  rat_type_e type;

  union{
    uint32_t nr_arfcn; // [0,3279165]  6.2.3.30  
    uint16_t eutra_arfcn; // [0,65535] 6.2.3.33
  }; 

} cell_arfcn_t;

void free_cell_arfcn(cell_arfcn_t* src);

cell_arfcn_t cp_cell_arfcn(cell_arfcn_t const* src);

bool eq_cell_arfcn(cell_arfcn_t const* m0, cell_arfcn_t const* m1);



#endif
