/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef CCC_CAUSE_H
#define CCC_CAUSE_H

typedef enum{
  CAUSE_NOT_SUPPORTED,
  CAUSE_NOT_AVAILABLE,
  CAUSE_INCOMPATIBLE_STATE,
  CAUSE_JSON_ERROR,
  CAUSE_SEMANTIC_ERROR,
  CAUSE_UNSPECIFIED,

  END_CAUSE,
} ccc_cause_e;

#endif