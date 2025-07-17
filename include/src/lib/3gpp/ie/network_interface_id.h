#ifndef NETWORK_INTERFACE_IDENTIFIER_H
#define NETWORK_INTERFACE_IDENTIFIER_H 

#include "e1_e2sm.h"
#include "network_interface_type.h"
#include "f1_e2sm.h"
#include "guami.h"
#include "global_ng_ran_node_id.h"
#include "e2sm_gummei.h"
#include "w1_e2sm.h"
#include "x2_e2sm.h"

typedef struct{

  network_interface_type_e type;
  union{
    //6.2.3.17
    guami_t ng;

    // 6.2.3.2 
    global_ng_ran_node_id_t xn; 

    // f1
    f1_e2sm_t f1;

    // e1
    e1_e2sm_t e1;

    // s1
    e2sm_gummei_t s1;

    // X2
    x2_e2sm_t x2;

    // W1
    w1_e2sm_t w1; 
  };


} network_interface_id_t;


#endif

