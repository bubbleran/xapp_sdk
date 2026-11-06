/*

Copyright (C) 2026 BubbleRAN

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see http://www.gnu.org/licenses/.
*/

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
