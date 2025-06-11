/*
 * Copyright (c) 2004-2017 Lev Walkin <vlm@lionet.info>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
/*
 * This type differs from the standard ENUMERATED in that it is modelled using
 * the fixed machine type (long, int, short), so it can hold only values of
 * limited length. There is no type (i.e., NativeEnumerated_t, any integer type
 * will do).
 * This type may be used when integer range is limited by subtype constraints.
 */
#ifndef	_NativeEnumerated_H_
#define	_NativeEnumerated_H_

#include <NativeInteger.h>

#ifdef __cplusplus
extern "C" {
#endif

extern asn_TYPE_descriptor_t asn_DEF_NativeEnumerated_e2ap_v3_01;
extern asn_TYPE_operation_t asn_OP_NativeEnumerated_e2ap_v3_01;

#define NativeEnumerated_free NativeInteger_free_e2ap_v3_01

#if !defined(ASN_DISABLE_PRINT_SUPPORT)
#define NativeEnumerated_print NativeInteger_print_e2ap_v3_01
#endif  /* !defined(ASN_DISABLE_PRINT_SUPPORT) */

#define NativeEnumerated_compare NativeInteger_compare_e2ap_v3_01

#define NativeEnumerated_constraint asn_generic_no_constraint_e2ap_v3_01

#if !defined(ASN_DISABLE_BER_SUPPORT)
#define NativeEnumerated_decode_ber NativeInteger_decode_ber_e2ap_v3_01
#define NativeEnumerated_encode_der NativeInteger_encode_der_e2ap_v3_01
#endif  /* !defined(ASN_DISABLE_BER_SUPPORT) */

#if !defined(ASN_DISABLE_XER_SUPPORT)
#define NativeEnumerated_decode_xer NativeInteger_decode_xer_e2ap_v3_01
xer_type_encoder_f NativeEnumerated_encode_xer_e2ap_v3_01;
#endif  /* !defined(ASN_DISABLE_XER_SUPPORT) */

#if !defined(ASN_DISABLE_JER_SUPPORT)
jer_type_encoder_f NativeEnumerated_encode_jer_e2ap_v3_01;
#endif  /* !defined(ASN_DISABLE_JER_SUPPORT) */

#if !defined(ASN_DISABLE_OER_SUPPORT)
oer_type_decoder_f NativeEnumerated_decode_oer;
oer_type_encoder_f NativeEnumerated_encode_oer;
#endif  /* !defined(ASN_DISABLE_OER_SUPPORT) */

#if !defined(ASN_DISABLE_UPER_SUPPORT)
per_type_decoder_f NativeEnumerated_decode_uper_e2ap_v3_01;
per_type_encoder_f NativeEnumerated_encode_uper_e2ap_v3_01;
#endif  /* !defined(ASN_DISABLE_UPER_SUPPORT) */
#if !defined(ASN_DISABLE_APER_SUPPORT)
per_type_decoder_f NativeEnumerated_decode_aper_e2ap_v3_01;
per_type_encoder_f NativeEnumerated_encode_aper_e2ap_v3_01;
#endif  /* !defined(ASN_DISABLE_APER_SUPPORT) */

#if !defined(ASN_DISABLE_RFILL_SUPPORT)
#define NativeEnumerated_random_fill NativeInteger_random_fill_e2ap_v3_01
#endif  /* !defined(ASN_DISABLE_RFILL_SUPPORT) */

#if !defined(ASN_DISABLE_UPER_SUPPORT) || !defined(ASN_DISABLE_APER_SUPPORT)
int NativeEnumerated__compar_value2enum_e2ap_v3_01(
        const void *ap,
        const void *bp);
#endif  /* !defined(ASN_DISABLE_UPER_SUPPORT) || !defined(ASN_DISABLE_APER_SUPPORT) */

#ifdef __cplusplus
}
#endif

#endif	/* _NativeEnumerated_H_ */
