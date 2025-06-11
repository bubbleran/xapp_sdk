/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef CCC_SERVICE_MODEL_SERVER_H
#define CCC_SERVICE_MODEL_SERVER_H

#include <stdint.h>
#include "../../sm/sm_ric.h"

__attribute__ ((visibility ("default"))) 
sm_ric_t* make_ccc_sm_ric(void);

uint16_t id_ccc_sm_ric(sm_ric_t const* ); 

#endif

