/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef NETWORK_INTERFACE_MESSAGE_ID_E2SM_H
#define NETWORK_INTERFACE_MESSAGE_ID_E2SM_H

#include <stdint.h>

typedef enum{

  INITIATINGMESSAGE_NETWORK_INTERFACE_MSG_ID,
  SUCCESSFULOUTCOME_NETWORK_INTERFACE_MSG_ID,
  UNSUCCESSFULOUTCOME_NETWORK_INTERFACE_MSG_ID,

  END_NETWORK_INTERFACE_MSG_ID

} network_interface_msg_id_e; 

typedef struct{

  // Interface Procedure ID
  // Mandatory
  // INTEGER
  uint64_t interface_proc_id;

  // Message Type
  // Mandatory
  network_interface_msg_id_e msg_type;

} network_interface_msg_id_t;

#endif

