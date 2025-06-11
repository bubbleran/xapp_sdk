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


#ifndef MIR_MOVING_AVERAGE_TIME_WINDOW
#define MIR_MOVING_AVERAGE_TIME_WINDOW 

#include "../../seq_container/seq_generic.h"

typedef struct{
  seq_ring_t tstamps; // int64_t
  seq_ring_t val; // uint32_t
  double avg;
  double wnd_ms;
} mv_avg_wnd_t;

void mv_avg_wnd_init(mv_avg_wnd_t*, float wnd_ms);

void mv_avg_wnd_free( mv_avg_wnd_t* );

void mv_avg_wnd_push_back(mv_avg_wnd_t*, int64_t tstamp, uint32_t val);

double mv_avg_wnd_val(mv_avg_wnd_t*);

#endif

