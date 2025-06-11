/*
MIT License

Copyright (c) 2023 Mikel Irazabal

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

#ifndef MACROS_MIR_H
#define MACROS_MIR_H 

/////
// Naive macros for compile time metaprogramming
/////

#define is_same_type(a, b) __builtin_types_compatible_p(__typeof__(a), __typeof__(b))

#define is_compatible(x, T) ({ _Generic((x), T:1, default: 0); })

// Defined at gcc/typeclass.h
#define gcc_pointer_type_class 5  
#define is_ptr_or_array(p)  (__builtin_classify_type(p) == gcc_pointer_type_class)

#define is_primitive_type(x) ({ _Generic((x), \
    _Bool: 1, \
    char: 1, \
    signed char: 1, \
    unsigned char: 1, \
    short int: 1, \
    unsigned short int: 1, \
    int: 1, \
    unsigned int: 1, \
    long int: 1, \
    unsigned long int: 1, \
    long long int: 1, \
    unsigned long long int: 1, \
    float: 1, \
    double: 1, \
    long double: 1, \
    default: 0) \
 ;})



#define decay_ptr(p) (&*__builtin_choose_expr(is_ptr_or_array(p), p, NULL))

/////
// Compile time assertions
/////

#define assert_is_ptr(p) ({ _Static_assert(is_same_type(p, decay_ptr(p)), "Not a pointer!"); })

#define assert_same_type(a, b) ({ _Static_assert(is_same_type(a, b), "Incompatible types"); })


#endif


