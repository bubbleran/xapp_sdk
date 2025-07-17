#ifndef GUAMI_H
#define GUAMI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "plmn_identity.h"
#include <stdbool.h>
#include <stdint.h>

// openair3/NGAP/ngap_gNB_defs.h

typedef struct{
  // Mandatory
  // PLMN Identity 6.2.3.1
  e2sm_plmn_t plmn_id;

  // Mandatory
  // AMF Region ID BIT STRING (SIZE(8))
  // openair3/NGAP/ngap_gNB_defs.h
  uint8_t amf_region_id;

  // Mandatory
  //  AMF Set ID BIT STRING (SIZE(10))
  uint16_t amf_set_id:10;

  // Mandatory
  // AMF Pointer BIT STRING (SIZE(6))
  uint16_t amf_ptr:6;
} guami_t;

guami_t cp_guami(guami_t const* src);

bool eq_guami(guami_t const * m0, guami_t const * m1);

#ifdef __cplusplus
}
#endif

#endif

// done
