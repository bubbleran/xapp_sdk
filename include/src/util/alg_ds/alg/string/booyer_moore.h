
/*
 * A Naive C implementation from the following article 
 *
 * author = {Boyer, Robert S. and Moore, J. Strother},
 * title = {A Fast String Searching Algorithm},
 * year = {1977},
 * issue_date = {Oct. 1977},
 * publisher = {Association for Computing Machinery},
 * address = {New York, NY, USA},
*/
  
#ifndef BOOYER_MOORE_ALG_H
#define BOOYER_MOORE_ALG_H 

#include <stddef.h>


char* search_booyer_moore(size_t len_needle, char needle[len_needle], size_t len_haystack, char haystack[len_haystack]);

#endif


