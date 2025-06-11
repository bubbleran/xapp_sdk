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

#ifndef FIND_ALGORITHM
#define FIND_ALGORITHM 

#include <stdbool.h>
#include <stddef.h>
#include "../ds/seq_container/seq_generic.h"
#include "../ds/assoc_container/assoc_generic.h"
#include "../ds/assoc_container/bimap.h"


//void* find(void* start_it,void* end_it, void* value, bool (*f)(const void*, const void*));

// Sequencial containers

void* find_if_list(const seq_list_t* l, void* start_it, void* end_it, void* value, bool (*f)(const void*, const void*));


void* find_if_arr(seq_arr_t* arr, void* start_it, void* end_it, void* value , bool(*f)(const void*, const void*));


void* find_if_deque(const seq_deque_t* arr, void* start_it, void* end_it, void* value , bool(*f)(const void*, const void*));

void* find_if_ring(seq_ring_t* arr, void* start_it, void* end_it, void* value , bool(*f)(const void*, const void*));



// Ranges
void* find_if_list_r(const seq_list_t* l, void* value, bool (*f)(const void*, const void*));

void* find_if_arr_r(seq_arr_t* arr, void* value , bool(*f)(const void*, const void*));

void* find_if_deque_r(const seq_deque_t* arr, void* value , bool(*f)(const void*, const void*));

void* find_if_ring_r(seq_ring_t* arr, void* value , bool(*f)(const void*, const void*));


// Associative containers

void* find_if_rb_tree(assoc_rb_tree_t* tree, void* start_it, void* end_it, void const* value, bool(*f)(const void*, const void*)); 

void* find_if_rb_tree_lck(assoc_rb_tree_lck_t* tree, void* start_it, void* end_it, void const* value, bool(*f)(const void*, const void*));

void* find_reg(assoc_reg_t* reg, void* start_it, void* end_it, uint32_t key);

bml_iter_t find_if_bi_map_left(bi_map_t* map, bml_iter_t start_it, bml_iter_t end_it, void const* value, bool(*f)(const void*, const void*)); 

bmr_iter_t find_if_bi_map_right(bi_map_t* map, bmr_iter_t start_it, bmr_iter_t end_it, void const* value, bool(*f)(const void*, const void*)); 



// Ranges
void* find_if_rb_tree_r(assoc_rb_tree_t* tree, void const* value, bool(*f)(const void*, const void*)); 

void* find_if_rb_tree_lck_r(assoc_rb_tree_lck_t* tree, void const* value, bool(*f)(const void*, const void*)); 

void* find_reg_r(assoc_reg_t* reg, uint32_t key);

bml_iter_t find_if_bi_map_left_r(bi_map_t* map, void const* value, bool(*f)(const void*, const void*)); 

bmr_iter_t find_if_bi_map_right_r(bi_map_t* map, void const* value, bool(*f)(const void*, const void*)); 


#endif

