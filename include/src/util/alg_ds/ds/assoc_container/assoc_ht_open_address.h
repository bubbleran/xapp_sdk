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

#ifndef ASSOC_HASH_TABLE_OPEN_ADDRESSING
#define ASSOC_HASH_TABLE_OPEN_ADDRESSING 

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


typedef bool (*key_eq_func_fp)(const void* a, const void* b);
typedef void (*free_func_ht_open_fp)(void* key, void* value);
typedef uint32_t (*hash_func_ht_open_fp)(const void* key);

typedef struct hentry_s hentry_t;

typedef struct {
  hentry_t* arr;
  size_t key_sz;
  uint32_t sz;
  uint32_t cap;
  // # of used entries, even if they are now freed
  uint32_t num_dirty; 
  key_eq_func_fp key_eq;
  free_func_ht_open_fp free_func;
  hash_func_ht_open_fp hash_func;
} assoc_ht_open_t;


void assoc_ht_open_init(assoc_ht_open_t* htab, size_t key_sz, key_eq_func_fp eq, free_func_ht_open_fp free, hash_func_ht_open_fp hash_func);

void assoc_ht_open_free(assoc_ht_open_t* ht);

// Modifiers
// The tree is responsible for freeing the void* key and value memory later
void assoc_ht_open_insert(assoc_ht_open_t* ht, void const* key, size_t key_sz, void* value);

// It returns the void* of value. the void* of the key is freed
void* assoc_ht_open_extract(assoc_ht_open_t* ht, void* key);

// Get the key from an iterator 
void* assoc_ht_open_key(assoc_ht_open_t* ht, void* it);

// Get the value pointer from the key 
void* assoc_ht_open_value(assoc_ht_open_t* htab, const void* key);

// Capacity
size_t assoc_ht_open_size(assoc_ht_open_t* ht);

// Forward Iterator Concept
void* assoc_ht_open_front(assoc_ht_open_t const* ht);

void* assoc_ht_open_next(assoc_ht_open_t const* ht, void* it);

void* assoc_ht_open_end(assoc_ht_open_t const* ht);

#endif

