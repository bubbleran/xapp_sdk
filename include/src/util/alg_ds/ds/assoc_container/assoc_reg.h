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

#ifndef ASSOCCIATIVE_CONTAINERS_GENERIC_REGISTRY_H
#define ASSOCCIATIVE_CONTAINERS_GENERIC_REGISTRY_H

// Data structure based on Sean Parent's presentation Better Code: Relationships
// https://sean-parent.stlab.cc/papers-and-presentations/#better-code-relationships
// It associates an ID with some data that is stored and can be latter accessed. 
// It replaces the std::map data structure. 
// It is implemented as an ordered array (key_id is a monotonically increasing 
// value) so that searches are always O(logN) and memory is always contiguous,
// contrary to the std::map that is a node based data structure
// It shrinks, compacts and expands as necessary

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "../../ds/seq_container/seq_generic.h"

typedef struct{
  uint32_t key;
  bool has_value;
  // Do NOT change the order in which the variables are declared in the struct
  // as val is an incomplete array type
  uint8_t val[];
} registry_bucket_t ;

typedef struct registry_s{
  void* arr;  
  size_t sz;
  size_t cap;
  size_t occ_bucket;
  size_t elm_sz;
  // monotonic increasing key id 
  size_t key_id;
} assoc_reg_t;


void assoc_reg_init(assoc_reg_t* reg, size_t elm_sz);

void assoc_reg_free(assoc_reg_t* reg);

// Get a reference to the value type. 
//void* find_registry(registry_t* reg, uint32_t key);

//void delete_registry(registry_t* reg, uint32_t key);

// Value semantic. i.e., the void* value will be copied into the registry. Shallow copy 
uint32_t assoc_reg_push_back(assoc_reg_t* reg, void* value, size_t elm_sz); 

// Get the key from an iterator 
void* assoc_reg_key(assoc_reg_t* reg, void* it);

// Get the value pointer from an iterator
void* assoc_reg_value(assoc_reg_t* reg, void* it);

// Erase the elements in the range
void assoc_reg_erase(assoc_reg_t* reg, void* start_it, void* end_it, void(free_func)(void*));

//Capacity
size_t assoc_reg_size(assoc_reg_t* reg);

// Iterators
void* assoc_reg_front(assoc_reg_t* reg);

void* assoc_reg_next(assoc_reg_t* reg, void*);

void* assoc_reg_end(assoc_reg_t* reg);

seq_arr_t remove_if_range_reg(assoc_reg_t* reg, bool (*f)(void* data));


// Just for test purposes
void test_invariants_registry_hold(assoc_reg_t* reg);
 
#endif

