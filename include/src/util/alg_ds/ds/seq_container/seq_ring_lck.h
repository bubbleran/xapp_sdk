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




#ifndef SEQ_CIRCULAR_BUFFER_LCK_H
#define SEQ_CIRCULAR_BUFFER_LCK_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <pthread.h>

typedef struct
{
  const size_t elt_size;
  uint8_t* array;
  pthread_mutex_t mtx;

  size_t cap;
  uint32_t head;
  uint32_t tail;
} seq_ring_lck_t;


typedef void (*seq_free_func)(void*); 

void seq_ring_lck_init(seq_ring_lck_t*, size_t);

void seq_ring_lck_free(seq_ring_lck_t*, seq_free_func);

void seq_ring_lck_push_back(seq_ring_lck_t* arr, uint8_t* data, size_t len);

void seq_ring_lck_erase(seq_ring_lck_t*, void*, void*);

void seq_ring_lck_swap(seq_ring_lck_t*, void*, void*);

size_t seq_ring_lck_size(seq_ring_lck_t*);

void* seq_ring_lck_front(seq_ring_lck_t*);

void* seq_ring_lck_next(seq_ring_lck_t*, void*);

void* seq_ring_lck_end(seq_ring_lck_t*);

void* seq_ring_lck_at(seq_ring_lck_t* , uint32_t );

int32_t seq_ring_lck_dist(seq_ring_lck_t*, void*, void*);

bool seq_ring_lck_equal(void*,void*);

#endif

