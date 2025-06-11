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



#ifndef SEQ_DEQUE
#define SEQ_DEQUE

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct seq_deque_chunk
{
  void* current_it;
  void* end_it;
  struct seq_deque_chunk* next;
  
} seq_deque_chunk_t;


typedef struct seq_deque_s
{
  void* start_it;
  void* end_it;
  const uint32_t chunk_size;
  const size_t elt_size;
  size_t size;
} seq_deque_t;

typedef void (*seq_free_func)(void*); 

void seq_deque_init(seq_deque_t*, size_t);

void seq_deque_free(seq_deque_t*, seq_free_func);

void seq_deque_push_back(seq_deque_t* arr, uint8_t* data, size_t len);

void seq_deque_erase(seq_deque_t*, void*);

void seq_deque_swap(seq_deque_t*, void*, void*);

size_t seq_deque_size(seq_deque_t*);

void* seq_deque_front(seq_deque_t*);

void* seq_deque_next(seq_deque_t*, void*);

void* seq_deque_end(seq_deque_t*);

bool seq_deque_equal(void*,void*);

void* seq_deque_value(void*);


#endif
