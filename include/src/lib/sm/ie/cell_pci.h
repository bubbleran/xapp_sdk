/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef SERVING_CELL_PCI_SM_H
#define SERVING_CELL_PCI_SM_H  

#include "rat_type.h"
#include <stdbool.h>

// RC SM
// 9.3.39
// E2 SM 
// 6.2.2.14

typedef struct{
  // CHOICE RAT type
  // Mandatory
  rat_type_e type;

  union{
    int nr_pci; // [0,1007]  6.2.3.29 
    int eutra_pci; // [0,503] // 6.2.3.32
  };
} cell_pci_t;

bool eq_cell_pci( cell_pci_t const* m0,  cell_pci_t const* m1);

void free_cell_pci(cell_pci_t* src);

cell_pci_t cp_cell_pci(cell_pci_t const* src);



#endif
