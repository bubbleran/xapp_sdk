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
 * Thread Safe Notification Queue. 
 * Inspired by Anthony Williams C++ Concurrency in Action Book, Section 6.2
 */


#ifndef THREAD_SAFE_NOTIFICATION_QUEUE_MIR_H
#define THREAD_SAFE_NOTIFICATION_QUEUE_MIR_H 

#include <stdatomic.h>
#include <stdbool.h>
#include <pthread.h>

#include "../seq_container/seq_generic.h"

typedef struct{
  pthread_mutex_t mtx;
  pthread_cond_t cv;
  seq_ring_t r;
  atomic_bool stop_token;
  atomic_bool stopped;
} tsnq_t;

void init_tsnq(tsnq_t* q, size_t elm_sz);

void free_tsnq(tsnq_t* q, void (*f)(void*) ) ;

void push_tsnq(tsnq_t* q, void* val, size_t size);

void* wait_and_pop_tsnq(tsnq_t* q, void* (*f)(void*) );

void* pop_tsnq_10(tsnq_t* q, void* (*f)(void*) );

void* pop_tsnq_100(tsnq_t* q, void* (*f)(void*) );

size_t size_tsnq(tsnq_t* q);

#endif

