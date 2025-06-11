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

#ifndef MIR_LOCK_GUARD_H
#define MIR_LOCK_GUARD_H 

#include "../../alg/defer.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


// ToDO: Have a look at the implementation on QEMU_LOCK_GUARD


void mir_dummy_lock_guard();
void mir_dummy_lock_guard_const();

// __attribute__((unused)) 

#define CHECK_TYPE_INLINE(val, type) (void)_Generic((val), type: mir_dummy_lock_guard, const type: mir_dummy_lock_guard_const)

#define lock_guard(X) \
  do{ CHECK_TYPE_INLINE(X, pthread_mutex_t*);\
     int rc = pthread_mutex_lock(X);  \
     if (rc != 0){ \
        fprintf(stdout, "Error while locking, possibly the lock is already locked: %s\n", strerror(rc)); \
        fflush(stdout); \
        assert(0 != 0); \
     } \
  } while(0); \
   defer( { int rc = pthread_mutex_unlock(X); \
         if(rc != 0){ \
          fprintf(stdout, "Error while unlocking: %s\n", strerror(rc) ); \
          fflush(stdout); \
          assert(0 != 0); \
         } \
         }); \

//         printf("Defering... \n" ); 

#endif

