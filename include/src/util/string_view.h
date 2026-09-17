#ifndef STRING_VIEW_MIR_H
#define STRING_VIEW_MIR_H 

#include <stdlib.h>
#include <stdbool.h>

// Non-owning ds. Do not try to free it!
typedef struct{
  // Non-owning iterator
  char* it;
  size_t sz;
} string_view_t;

bool eq_string_view(string_view_t m0, string_view_t m1);

size_t concat_str(char* dst, string_view_t m0, string_view_t m1);

size_t add_str(char* dst, string_view_t m0);

#endif

