#ifndef RAN_FUNCTION_NAME_h
#define RAN_FUNCTION_NAME_h

#ifdef __cplusplus
extern "C" {
#endif

#include "../../../util/byte_array.h"

typedef struct {
    // RAN Function Short Name
    // Mandatory
    // PrintableString [1-150]
    byte_array_t name;

    // RAN Function Service Model OID
    // Mandatory
    // PrintableString [1-1000]
    byte_array_t oid;

    // RAN Function Description
    // Mandatory
    // PrintableString [1- 150]
    byte_array_t description;

    // RAN Function Instance
    // Optional
    // INTEGER
    long* instance;	/* OPTIONAL: it is suggested to be used when E2 Node declares
                                 multiple RAN Function ID supporting the same  E2SM specification   ask Mikel */
} ran_function_name_t;

void free_ran_function_name(ran_function_name_t* src);

bool eq_ran_function_name(ran_function_name_t const * m0, ran_function_name_t const * m1);

ran_function_name_t cp_ran_function_name(ran_function_name_t const* src);


#ifdef __cplusplus
}
#endif

#endif

// done
