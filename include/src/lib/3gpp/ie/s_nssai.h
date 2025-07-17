#ifndef S_NSSAI_E2SM_H
#define S_NSSAI_E2SM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "../../../util/byte_array.h"

// 6.2.3.12   S-NSSAI

typedef struct {
  uint8_t	  sST;
	uint32_t  *sD;	/* OPTIONAL, 24 bits are occupied */
} s_nssai_e2sm_t;

bool eq_s_nssai_e2sm(const s_nssai_e2sm_t* m0, const s_nssai_e2sm_t* m1);

void free_s_nssai_e2sm( s_nssai_e2sm_t* src);

s_nssai_e2sm_t cp_s_nssai_e2sm(const s_nssai_e2sm_t* src);

#ifdef __cplusplus
}
#endif


#endif

// done
