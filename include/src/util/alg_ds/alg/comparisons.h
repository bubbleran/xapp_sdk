/*
MIT License

Copyright (c) 2021 Mikel Irazabal

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

#ifndef ALGO_COMPARISONS
#define ALGO_COMPARISONS 


#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>


static inline
bool eq_uint64_t(const void* a, const void* b)
{
  return *(uint64_t*)a == *(uint64_t*)b;
}

static inline
int cmp_uint64_t(const void* pa, const void* pb)
{
  uint64_t* a = (uint64_t*)pa;
  uint64_t* b = (uint64_t*)pb;

  if(*a < *b) return -1;
  if(*b > *a) return 1;
  return 0;
}

static inline
bool less_int(const void* a, const void* b)
{
  if(a == NULL)
    return false;
  if(b == NULL)
    return true;
 
  return *(int*)a < *(int*)b;
};

static inline
bool less_uint(const void* a, const void* b)
{
  if(a == NULL)
    return false;
  if(b == NULL)
    return true;

  return *(uint64_t*)a < *(uint64_t*)b;
};

static inline
bool greater_int(const void* a, const void* b)
{
  return less_int(b,a); 
};

static inline
bool greater_uint(const void* a, const void* b)
{
  return less_uint(b,a); 
};

#endif

