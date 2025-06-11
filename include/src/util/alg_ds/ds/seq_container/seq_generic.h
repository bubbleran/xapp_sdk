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



#ifndef SEQUENCE_CONTAINERS_GENERIC
#define SEQUENCE_CONTAINERS_GENERIC

#include "seq_arr.h"
#include "seq_list.h"
#include "seq_deque.h"
#include "seq_ring.h"

/*
 *Generic sequence container file. Nomenclature from the C++ sequence containers
 */


// Initialization
#define seq_init(T,U) _Generic ((T), seq_arr_t*: seq_arr_init, \
                                       seq_list_t*: seq_list_init,\
                                       seq_deque_t*: seq_deque_init,\
                                       seq_ring_t*: seq_ring_init,\
                                       default: seq_arr_init) (T,U)


#define seq_free(T,U) _Generic ((T), seq_arr_t*: seq_arr_free, \
                                       seq_list_t*: seq_list_free, \
                                       seq_deque_t*: seq_deque_free,\
                                       seq_ring_t*: seq_ring_free,\
                                       default: seq_arr_free)(T,U)


// Modifiers
#define seq_push_back(T,U,W) _Generic ((T), seq_arr_t*:   seq_arr_push_back,  \
                                            seq_list_t*:  seq_list_push_back, \
                                            seq_deque_t*: seq_deque_push_back,\
                                            seq_ring_t*:  seq_ring_push_back,\
                                            default:      seq_arr_push_back)(T,U,W)

#define seq_erase(T,U,W) _Generic ((T), seq_arr_t*: seq_arr_erase, \
                                          seq_list_t*: seq_list_erase, \
                                          seq_deque_t*: seq_deque_erase,\
                                          seq_ring_t*: seq_ring_erase,\
                                          default: seq_arr_erase)(T,U,W)

#define seq_erase_free(T, U, W, X)                                             \
  _Generic((T), seq_arr_t *                                                    \
           : seq_arr_erase_free, default                                       \
           : seq_arr_erase_free)(T, U, W, X)

// Capacity
#define seq_size(T) _Generic ((T), seq_arr_t*: seq_arr_size, \
                                       seq_list_t*: seq_list_size,\
                                       seq_deque_t*: seq_deque_size,\
                                       seq_ring_t*: seq_ring_size,\
                                       default: seq_arr_size)(T)


// Forward Iterator Concept
#define seq_front(T) _Generic ((T), seq_arr_t*: seq_arr_front, \
                                        seq_list_t*: seq_list_front, \
                                        const seq_list_t*: seq_list_front_const, \
                                        seq_deque_t*: seq_deque_front,\
                                        seq_ring_t*: seq_ring_front,\
                                        default: seq_arr_front)(T)

#define seq_next(T,U) _Generic((T), seq_arr_t*: seq_arr_next, \
                                        seq_list_t*: seq_list_next, \
                                        const seq_list_t*: seq_list_next_const, \
                                        seq_deque_t*: seq_deque_next,\
                                        seq_ring_t*: seq_ring_next,\
                                        default: seq_arr_next)(T,U)

#define seq_end(T) _Generic((T), seq_arr_t*: seq_arr_end, \
                                       seq_list_t*: seq_list_end, \
                                       const seq_list_t*: seq_list_end_const, \
                                        seq_deque_t*: seq_deque_end,\
                                        seq_ring_t*: seq_ring_end,\
                                        default: seq_arr_end)(T)

// at position starting from zero
#define seq_at(T,U) _Generic((T), seq_arr_t*: seq_arr_at, \
                                       seq_list_t*: seq_list_at, \
                                        seq_ring_t*: seq_ring_at,\
                                        default: seq_arr_at)(T,U)

//
#define seq_distance(T,U,V) _Generic((T), seq_arr_t*: seq_arr_dist,\
                                          seq_list_t*: seq_list_dist,\
                                          seq_ring_t*: seq_ring_dist,\
                                          default: seq_arr_dist)(T,U,V)

// Equality

#define seq_equal(T,U,V) _Generic((T), seq_arr_t*: seq_arr_equal, \
                                       seq_list_t*: seq_list_equal, \
                                       const seq_list_t*: seq_list_equal, \
                                        seq_deque_t*: seq_deque_equal,\
                                        default: seq_arr_equal)(U,V)


#define seq_value(T,U) _Generic((T), seq_arr_t*: seq_arr_value, \
                                       seq_list_t*: seq_list_value, \
                                       const seq_list_t*: seq_list_value, \
                                        seq_deque_t*: seq_deque_value,\
                                        default: seq_arr_value)(U)


#endif
