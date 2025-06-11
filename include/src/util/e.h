#ifndef ERROR_MACROS_MIR_H
#define ERROR_MACROS_MIR_H 

#include <assert.h>

/////
// For those functions where errors mean assertions 
/////

#define ecalloc(nelm, szelem) ({ \
              void* mem = calloc(nelm, szelem);  \
              assert(mem != NULL && "Memory exhausted");\
              mem;  } )

#define emalloc(sz) ({ \
              void* mem = malloc(sz);  \
              assert(mem != NULL && "Memory exhausted");\
              mem;  } )



#endif
