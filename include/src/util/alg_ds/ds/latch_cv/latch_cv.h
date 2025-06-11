/*
MIT License

Copyright (c) 2024 Mikel Irazabal

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

#ifndef LATCH_CONDITION_VARIABLE_MIR_H
#define LATCH_CONDITION_VARIABLE_MIR_H 

// Interface mimicking c++20 std::latch
// https://en.cppreference.com/w/cpp/thread/latch


#include <stdatomic.h>
#include <pthread.h>

typedef struct {
  pthread_mutex_t mtx; 
  pthread_cond_t cond; 
  atomic_int cnt;
} latch_cv_t;

latch_cv_t init_latch_cv(size_t cnt);

void free_latch_cv(latch_cv_t* l);

void count_down_latch_cv(latch_cv_t* l);

void wait_latch_cv(latch_cv_t* l);

int wait_timeout_latch_cv(latch_cv_t* l, int timeout_sec);

#endif

