/*
MIT License

Copyright (c) 2023 Mikel Irazabal

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/////
// Equality macro functions
/////

#include "macros.h"

// Clang has problems with _Generic at compile time, so two defines are needed
#if defined __clang__ 
  #define eq_ptr_assert(x,f) assert((is_primitive_type((*x)) || f != NULL) && "Structs need equality function"); 
#elif defined __GNUC__ 
  #define eq_ptr_assert(x,f) _Static_assert((is_primitive_type((*x)) || f != NULL) , "Structs need equality function"); 
#endif 


#define eq_ptr(x, y, f) ({ \
    assert_is_ptr(x); \
    assert_is_ptr(y); \
    assert_same_type(x,y); \
    eq_ptr_assert(x,f); \
    bool ret = true; \
    if(x == y) \
      ret = true; \
    else if(x == NULL || y == NULL) \
      ret = false; \
    else if(f != NULL) \
      ret = ((bool (*)(void const*, void const*) )f) (x,y); \
    else if(memcmp(x,y, sizeof(__typeof__(*x))) != 0) \
      ret = false; \
    ret;})



