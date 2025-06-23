#ifndef EUTRA_CGI_KPM_V2_H
#define EUTRA_CGI_KPM_V2_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "plmn_identity.h"


//  6.2.3.11  E-UTRA CGI
typedef struct{

  e2sm_plmn_t plmn_id; // 6.2.3.1
  uint32_t eutra_cell_id; // bit string of 28 bits

} eutra_cgi_t ;

void free_eutra_cgi(eutra_cgi_t* src);

bool eq_eutra_cgi(eutra_cgi_t const * m0, eutra_cgi_t const * m1);

eutra_cgi_t cp_eutra_cgi(eutra_cgi_t const* src);

#ifdef __cplusplus
}
#endif

#endif

// done
