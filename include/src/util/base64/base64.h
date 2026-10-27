#ifndef BASE64_MIR_H
#define BASE64_MIR_H 

#include "../src/util/string_mir.h"

char* encode_file_base64(const char* filepath);

string_t decode_file_base64(const char* file_path);

#endif
