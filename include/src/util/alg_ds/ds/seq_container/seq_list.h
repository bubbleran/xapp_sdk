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



#ifndef SEQ_CONTAINER_LIST
#define SEQ_CONTAINER_LIST

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct lst_node_s{
  struct lst_node_s* next;
  void* data;
} lst_node_t;

typedef struct seq_list_s{
   lst_node_t* root;
   size_t size;
} seq_list_t;

typedef void (*seq_free_func)(void*); 

void seq_list_init(seq_list_t*);

void seq_list_free(seq_list_t*, seq_free_func);

void seq_list_push_back(seq_list_t*, void*);

void seq_list_erase(seq_list_t*, void*);

void* seq_list_front(seq_list_t*);

void* seq_list_front_const(const seq_list_t*);
 
void* seq_list_next(seq_list_t*, void*);

void* seq_list_next_const(const seq_list_t*, void*);

void* seq_list_end(seq_list_t*);

void* seq_list_end_const(const seq_list_t*);

void* seq_list_at(seq_list_t*, uint32_t);

int32_t seq_list_dist(seq_list_t* ,void*, void*);

bool seq_list_equal(void* a, void* b);

void* seq_list_value(void* a);

size_t seq_list_size(seq_list_t*);

/* 
 * This function removes the first element of the sequence list LST. If there are no elements in the sequence, it does nothing. 
 * If sequence is NULL, you get an assert.
 */
void seq_list_pop_front(seq_list_t* lst);

#endif

