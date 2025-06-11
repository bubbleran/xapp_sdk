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


#ifndef ASSOCCIATIVE_CONTAINERS_GENERIC
#define ASSOCCIATIVE_CONTAINERS_GENERIC

#include "assoc_rb_tree.h" 
#include "assoc_rb_tree_lck.h" 
#include "assoc_ht_open_address.h"
#include "assoc_reg.h"

// Initialization
#define assoc_init(T, KS, C, F) _Generic ((T), assoc_rb_tree_t*: assoc_rb_tree_init, \
                                        assoc_rb_tree_lck_t*: assoc_rb_tree_lck_init, \
                                        assoc_ht_open_t*:  assoc_ht_open_init,\
                                        default:  assoc_rb_tree_init) (T, KS, C, F)

#define assoc_free(T) _Generic ((T), assoc_rb_tree_t*:  assoc_rb_tree_free, \
                                       assoc_rb_tree_lck_t*:  assoc_rb_tree_lck_free, \
                                       assoc_ht_open_t*:  assoc_ht_open_free,\
                                       default:   assoc_rb_tree_free)(T)

// Modifiers
#define assoc_insert(T, K, KS, V) _Generic ((T), assoc_rb_tree_t*: assoc_rb_tree_insert, \
                                       assoc_rb_tree_lck_t*: assoc_rb_tree_lck_insert, \
                                       assoc_ht_open_t*:  assoc_ht_open_insert,\
                                       default:   assoc_rb_tree_insert)(T,K,KS,V)


#define assoc_extract(T, K)  _Generic ((T), assoc_rb_tree_t*: assoc_rb_tree_extract, \
                                       assoc_rb_tree_lck_t*: assoc_rb_tree_lck_extract, \
                                       assoc_ht_open_t*:  assoc_ht_open_extract,\
                                       default:   assoc_rb_tree_extract)(T,K)

#define assoc_key(T,U)  _Generic ((T), assoc_rb_tree_t*: assoc_rb_tree_key, \
                                       assoc_rb_tree_lck_t*: assoc_rb_tree_lck_key, \
                                       assoc_ht_open_t*:  assoc_ht_open_key,\
                                       default:   assoc_rb_tree_key)(T,U)

#define assoc_value(T,U)  _Generic ((T), assoc_rb_tree_t*: assoc_rb_tree_value, \
                                       assoc_rb_tree_lck_t*: assoc_rb_tree_lck_value, \
                                       assoc_ht_open_t*:  assoc_ht_open_value,\
                                       default:   assoc_rb_tree_value)(T,U)


// Capacity
#define assoc_size(T) _Generic ((T), assoc_rb_tree_t*:  assoc_rb_tree_size, \
                                     assoc_rb_tree_lck_t*:  assoc_rb_tree_lck_size, \
                                     assoc_ht_open_t*:  assoc_ht_open_size,\
                                       default: assoc_rb_tree_size)(T)

// Forward Iterator Concept
#define assoc_front(T) _Generic ((T), assoc_rb_tree_t*: assoc_rb_tree_front, \
                                      assoc_rb_tree_lck_t*: assoc_rb_tree_lck_front, \
                                      assoc_ht_open_t*: assoc_ht_open_front,\
                                        default: assoc_rb_tree_front)(T)

#define assoc_next(T,U) _Generic((T), assoc_rb_tree_t*: assoc_rb_tree_next, \
                                      assoc_rb_tree_lck_t*: assoc_rb_tree_lck_next, \
                                      assoc_ht_open_t*: assoc_ht_open_next,\
                                        default:  assoc_rb_tree_next)(T,U)

#define assoc_end(T) _Generic((T),  assoc_rb_tree_t*: assoc_rb_tree_end, \
                                    assoc_rb_tree_lck_t*: assoc_rb_tree_lck_end, \
                                    assoc_ht_open_t*: assoc_ht_open_end, \
                                    default: assoc_rb_tree_end)(T)

#endif

