#ifndef STRING_DS_MIR_H
#define STRING_DS_MIR_H 

#include <stdlib.h>
#include <stdbool.h>
#include "string_view.h"

typedef struct{
  // Owning iterator
  char* it;
  size_t sz;
} string_t;

void free_string(string_t s);

string_t cp_string(string_t s);

string_t concat_string(string_t m0, string_t m1);

bool eq_string(string_t m0, string_t m1);

bool eq_string_ptr(string_t const* m0, string_t const* m1);

string_t char_to_string(char* src);

string_t string_view_to_string(string_view_t src); 

string_view_t string_to_string_view(string_t src);

#endif
