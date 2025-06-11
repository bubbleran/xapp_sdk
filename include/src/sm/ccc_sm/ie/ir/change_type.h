/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef CHANGE_TYPE_H
#define  CHANGE_TYPE_H

typedef enum {
  CHANGE_TYPE_NONE,
  CHANGE_TYPE_MODIFICATION,
  CHANGE_TYPE_ADDITION,
  CHANGE_TYPE_DELETION,

  END_CHANGE_TYPE
} change_type_e;


#endif
