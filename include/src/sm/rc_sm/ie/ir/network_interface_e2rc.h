#ifndef NETWORK_INTERFACE_E2RC_H
#define NETWORK_INTERFACE_E2RC_H

#include "../../../../lib/3gpp/ie/network_interface_type.h"
#include "../../../../lib/3gpp/ie/network_interface_id.h"
#include "../../../../lib/3gpp/ie/network_interface_msg_id.h"

typedef struct{

  // NI Type
  // Mandatory
  // 9.3.32
  network_interface_type_e ni_type;

  // NI Identifier
  // Optional
  // 9.3.33
  network_interface_id_t* ni_id;

  // NI Message
  // Optional
  // 9.3.34
  network_interface_msg_id_t* ni_msg_id;

} network_interface_e2rc_t ;

void free_network_interface_e2rc( network_interface_e2rc_t* src);

bool eq_network_interface_e2rc( network_interface_e2rc_t const* m0, network_interface_e2rc_t const* m1);

network_interface_e2rc_t cp_network_interface_e2rc(network_interface_e2rc_t const* src);

#endif

