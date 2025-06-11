/*
MIT License

Copyright (c) 2022 Mikel Irazabal

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

/*
 * Thread Safe Queue. 
 * Inspired by Anthony Williams C++ Concurrency in Action Book, Section 6.2
 */

#ifndef THREAD_SAFE_QUEUE_MIR_H
#define THREAD_SAFE_QUEUE_MIR_H 

#include <stdatomic.h>
#include <stdbool.h>
#include <pthread.h>

#include "../seq_container/seq_generic.h"

typedef struct{
  pthread_mutex_t mtx;
  seq_ring_t r;
} tsq_t;

void init_tsq(tsq_t* q, size_t elm_sz);

void free_tsq(tsq_t* q, void (*f)(void*));

void push_tsq(tsq_t* q, void* val, size_t size);

void pop_tsq(tsq_t* q, void* val, size_t sz);

size_t size_tsq(tsq_t* q);

#endif

