#ifndef TEST_INFORMATION_LIST_KPM_V2_01_H
#define TEST_INFORMATION_LIST_KPM_V2_01_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>

#include "../../../../../../util/byte_array.h"


typedef enum {
    GBR_TEST_COND_TYPE,
    AMBR_TEST_COND_TYPE,
    IsStat_TEST_COND_TYPE,
    IsCatM_TEST_COND_TYPE,
    DL_RSRP_TEST_COND_TYPE,
    DL_RSRQ_TEST_COND_TYPE,
    UL_RSRP_TEST_COND_TYPE,
    CQI_TEST_COND_TYPE,
    fiveQI_TEST_COND_TYPE,
    QCI_TEST_COND_TYPE,
    S_NSSAI_TEST_COND_TYPE,

    END_TEST_COND_TYPE_KPM_V2_01

} test_cond_type_e;

typedef enum {
    TRUE_TEST_COND_TYPE,

    END_COND_TYPE_KPM_V2_01

} cond_type_e;

typedef enum {
    EQUAL_TEST_COND,
    GREATERTHAN_TEST_COND,
    LESSTHAN_TEST_COND,
    CONTAINS_TEST_COND,
    PRESENT_TEST_COND,

    /* This type is extensible */

    END_TEST_COND

} test_cond_e;

typedef enum {
    INTEGER_TEST_COND_VALUE,
    ENUMERATED_TEST_COND_VALUE,
    BOOLEAN_TEST_COND_VALUE,
    BIT_STRING_TEST_COND_VALUE,
    OCTET_STRING_TEST_COND_VALUE,
    PRINTABLE_STRING_TEST_COND_VALUE,

    END_TEST_COND_VALUE

} test_cond_value_e;

typedef struct{
  test_cond_value_e type;  /* 8.3.23, OPTIONAL */
  union {
    int64_t * int_value;
    int64_t * enum_value;
    bool * bool_value;
    byte_array_t * bit_string_value; // enc/dec of this bit_string to be created
    byte_array_t * octet_string_value;
    byte_array_t * printable_string_value;
  };
} test_cond_value_t;

void free_test_cond_value(test_cond_value_t* src);

bool eq_test_cond_value(const test_cond_value_t* m0, const test_cond_value_t* m1);

test_cond_value_t cp_test_cond_value(const test_cond_value_t* src);


// 8.3.22   Test Condition Information
typedef struct {
    
    test_cond_type_e test_cond_type;
    union {
        cond_type_e GBR;
        cond_type_e AMBR;
        cond_type_e IsStat;
        cond_type_e IsCatM;
        cond_type_e DL_RSRP;
        cond_type_e DL_RSRQ;
        cond_type_e UL_RSRP;
        cond_type_e CQI;
        cond_type_e fiveQI;
        cond_type_e QCI;
        cond_type_e S_NSSAI;
    };
   
    // BUG in the standard. Mandatory ASN optional english
    test_cond_e *test_cond;  /* OPTIONAL */

    test_cond_value_t *test_cond_value;  /* 8.3.23, OPTIONAL */

} test_info_lst_t;

void free_test_info(test_info_lst_t* src);

bool eq_test_info(const test_info_lst_t *m0, const test_info_lst_t *m1);

test_info_lst_t cp_kpm_test_info(const test_info_lst_t * src);

#ifdef __cplusplus
}
#endif

#endif

// done
