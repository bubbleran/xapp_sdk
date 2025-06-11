/*-
 * Copyright (c) 2004-2017 Lev Walkin <vlm@lionet.info>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	ASN_TYPE_REAL_H
#define	ASN_TYPE_REAL_H

#include <asn_application.h>
#include <asn_codecs_prim.h>

#define	_ISOC99_SOURCE		/* For ilogb() and quiet NAN */
#ifndef _BSD_SOURCE
#define	_BSD_SOURCE		/* To reintroduce finite(3) */
#endif
#if	defined(__alpha)
#include <sys/resource.h>	/* For INFINITY */
#endif
#include <math.h>

#if	!(defined(NAN) || defined(INFINITY))
static volatile double real_zero CC_NOTUSED = 0.0;
#endif
#ifndef	NAN
#define	NAN	(0.0/0.0)
#endif
#ifndef	INFINITY
#define	INFINITY	(1.0/0.0)
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef enum specialRealValue_rc_v1_03 {
    SRV__NOT_A_NUMBER,
    SRV__MINUS_INFINITY,
    SRV__PLUS_INFINITY
} specialRealValue_e_rc_v1_03;
extern struct specialRealValue_s_rc_v1_03 {
    char *string;
    size_t length;
    long dv;
} specialRealValue_rc_v1_03[3];

typedef ASN__PRIMITIVE_TYPE_t REAL_t;

extern asn_TYPE_descriptor_t asn_DEF_REAL_rc_v1_03;
extern asn_TYPE_operation_t asn_OP_REAL_rc_v1_03;

#define REAL_free ASN__PRIMITIVE_TYPE_free_rc_v1_03

#if !defined(ASN_DISABLE_PRINT_SUPPORT)
asn_struct_print_f REAL_print_rc_v1_03;
#endif  /* !defined(ASN_DISABLE_PRINT_SUPPORT) */

asn_struct_compare_f REAL_compare_rc_v1_03;

#define REAL_constraint asn_generic_no_constraint_rc_v1_03

#if !defined(ASN_DISABLE_BER_SUPPORT)
#define REAL_decode_ber ber_decode_primitive
#define REAL_encode_der der_encode_primitive
#endif  /* !defined(ASN_DISABLE_BER_SUPPORT) */

#if !defined(ASN_DISABLE_XER_SUPPORT)
xer_type_decoder_f REAL_decode_xer_rc_v1_03;
xer_type_encoder_f REAL_encode_xer_rc_v1_03;
#endif  /* !defined(ASN_DISABLE_XER_SUPPORT) */

#if !defined(ASN_DISABLE_JER_SUPPORT)
jer_type_decoder_f REAL_decode_jer;
jer_type_encoder_f REAL_encode_jer;
#endif  /* !defined(ASN_DISABLE_JER_SUPPORT) */

#if !defined(ASN_DISABLE_OER_SUPPORT)
oer_type_decoder_f REAL_decode_oer;
oer_type_encoder_f REAL_encode_oer;
#endif  /* !defined(ASN_DISABLE_OER_SUPPORT) */

#if !defined(ASN_DISABLE_UPER_SUPPORT)
per_type_decoder_f REAL_decode_uper;
per_type_encoder_f REAL_encode_uper;
#endif  /* !defined(ASN_DISABLE_UPER_SUPPORT) */
#if !defined(ASN_DISABLE_APER_SUPPORT)
per_type_decoder_f REAL_decode_aper_rc_v1_03;
per_type_encoder_f REAL_encode_aper_rc_v1_03;
#endif  /* !defined(ASN_DISABLE_APER_SUPPORT) */

#if !defined(ASN_DISABLE_RFILL_SUPPORT)
asn_random_fill_rc_v1_03_f  REAL_random_fill_rc_v1_03;
#endif  /* !defined(ASN_DISABLE_RFILL_SUPPORT) */

/***********************************
 * Some handy conversion routines. *
 ***********************************/

ssize_t REAL__dump_rc_v1_03(double d, int canonical, asn_app_consume_bytes_f *cb, void *app_key);

/*
 * Convert between native double type and REAL representation (DER).
 * RETURN VALUES:
 *  0: Value converted successfully
 * -1: An error occurred while converting the value: invalid format.
 */
int asn_REAL2double_rc_v1_03(const REAL_t *real_ptr, double *d);
int asn_double2REAL_rc_v1_03(REAL_t *real_ptr, double d);

/*
 * Downcast double to float while checking that no overflow occurs.
 * This allows stricter control of the input data.
 * RETURN VALUES:
 *  0: The conversion was successful (perhaps with a loss of precision)
 * -1: The conversion created overflow into infinities.
 * The (outcome) is ALWAYS set to a value you'd expect from the
 * standard silent float to double conversion behavior.
 */
int asn_double2float_rc_v1_03(double d, float *outcome);

#ifdef __cplusplus
}
#endif

#endif	/* ASN_TYPE_REAL_H */
