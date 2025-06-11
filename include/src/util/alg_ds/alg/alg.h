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

#ifndef ALG_MIR_H
#define ALG_MIR_H

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "find.h"
#include "for_each.h"
#include "defer.h"
#include "iter_swap.h"


/*
 * Check at compile time that something is of a particular type.
 * Always evaluates to 1 so you may use it easily in comparisons.
 */
#define typecheck(type, x)                                                     \
  ({           \
    type __dummy;                                                              \
    typeof(x) __dummy2;                                                        \
    (void)(&__dummy == &__dummy2);  \
    1;                                                                         \
  })


#define swap(x,y) do \ { uint8_t swap_temp[sizeof(x) == sizeof(y) ? (signed)sizeof(x) : -1]; \
     memcpy(swap_temp,&y,sizeof(x)); \
     memcpy(&y,&x,       sizeof(x)); \
     memcpy(&x,swap_temp,sizeof(x)); \
    } while(0)


#define find_if(T,U,W,X,Y) _Generic ((T), seq_arr_t*:  find_if_arr, \
                                          seq_list_t*: find_if_list,\
                                          seq_ring_t*: find_if_ring, \
                                          assoc_rb_tree_t*: find_if_rb_tree, \
                                          default: find_if_arr) (T,U,W,X,Y)

#define find_if_r(T,X,Y) _Generic ((T), seq_arr_t*:  find_if_arr_r, \
                                          seq_list_t*: find_if_list_r,\
                                          seq_ring_t*: find_if_ring_r, \
                                          assoc_rb_tree_t*: find_if_rb_tree_r, \
                                          assoc_rb_tree_lck_t*: find_if_rb_tree_lck_r, \
                                          default: find_if_arr_r) (T,X,Y)


#define for_each(T,U,W,X,Y) _Generic((T), seq_arr_t*: for_each_arr, \
                                        default:  for_each_arr)(T,U,W,X,Y)

#define accumulate(T,U,W) _Generic ((T), seq_ring_t*: accumulate_ring, \
                                          default:  accumulate_ring) (T,U,W)


// Should iterator swap come at some point...

#endif
