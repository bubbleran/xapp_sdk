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

#ifndef BIDIRECTIONAL_HASH_MAP
#define BIDIRECTIONAL_HASH_MAP

/*
 *  Naive bidirectional map. K1->K2 and K2->K1 
 */


#include "assoc_rb_tree.h"

typedef int (*bi_map_cmp)(void const*, void const*);

typedef void (*free_func_t)(void* key, void* value);
typedef void (*free_fp_key)(void* key);

typedef struct
{
  assoc_rb_tree_t left;
  assoc_rb_tree_t right;
} bi_map_t;

typedef struct{
  void* it;
} bml_iter_t;

typedef struct{
  void* it;
} bmr_iter_t;

void bi_map_init(bi_map_t* map, size_t key_sz_1, size_t key_sz_2, bi_map_cmp cmp1, bi_map_cmp cmp2, free_func_t free1, free_func_t free2);

void bi_map_free(bi_map_t* map);

// Modifiers
void bi_map_insert(bi_map_t* map, void const* key1, size_t key_sz1, void const* key2, size_t key_sz2);

// It returns the void* of key2. f is called and the void* of the key1 is freed 
void* bi_map_extract_left(bi_map_t* map, void* key1, size_t key1_sz, free_fp_key f);

// It returns the void* of key1. f is called and the void* of the key2 is freed 
void* bi_map_extract_right(bi_map_t* map, void* key2, size_t key1_sz, free_fp_key f);

// returns a pointer to the value
void* bi_map_value_left(bi_map_t* map, bml_iter_t it);

// returns a pointer to the value
void* bi_map_value_right(bi_map_t* map, bml_iter_t it);

// Capacity
size_t bi_map_size(bi_map_t* map);



// Forward Iterator Concept

bml_iter_t bi_map_front_left(bi_map_t* map);

bml_iter_t bi_map_next_left(bi_map_t* map, bml_iter_t);

bml_iter_t bi_map_end_left(bi_map_t* map);

bmr_iter_t bi_map_front_right(bi_map_t* map);

bmr_iter_t bi_map_next_right(bi_map_t* map, bmr_iter_t);

bmr_iter_t bi_map_end_right(bi_map_t* map);



#endif

