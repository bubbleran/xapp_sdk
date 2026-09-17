#ifndef UNIX_NTP_CONVERSION_MIR_H
#define UNIX_NTP_CONVERSION_MIR_H 

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// https://www.rfc-editor.org/rfc/rfc5905 Section 6
// https://tickelton.gitlab.io/articles/ntp-timestamps/ 
// https://stackoverflow.com/questions/29112071/how-to-convert-ntp-time-to-unix-epoch-time-in-c-language-linux

uint64_t unix_to_ntp(uint64_t us);

uint64_t ntp_to_unix(uint64_t ntp);

#ifdef __cplusplus
}
#endif

#endif
