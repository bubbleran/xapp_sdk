/*-
 * Copyright (c) 2003-2017 Lev Walkin <vlm@lionet.info>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	ASN_TYPE_NULL_H
#define	ASN_TYPE_NULL_H

#include <asn_application.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The value of the NULL type is meaningless.
 * Use the BOOLEAN type if you need to carry true/false semantics.
 */
typedef int NULL_t;

extern asn_TYPE_descriptor_t asn_DEF_NULL_kpm_v3_00;
extern asn_TYPE_operation_t asn_OP_NULL_kpm_v3_00;

asn_struct_free_f NULL_free_kpm_v3_00;

#if !defined(ASN_DISABLE_PRINT_SUPPORT)
asn_struct_print_f NULL_print_kpm_v3_00;
#endif  /* !defined(ASN_DISABLE_PRINT_SUPPORT) */

asn_struct_compare_f NULL_compare_kpm_v3_00;
asn_struct_copy_f    NULL_copy_kpm_v3_00;

#define NULL_constraint asn_generic_no_constraint_kpm_v3_00

#if !defined(ASN_DISABLE_BER_SUPPORT)
ber_type_decoder_f NULL_decode_ber;
der_type_encoder_f NULL_encode_der;
#endif  /* !defined(ASN_DISABLE_BER_SUPPORT) */

#if !defined(ASN_DISABLE_XER_SUPPORT)
xer_type_decoder_f NULL_decode_xer;
xer_type_encoder_f NULL_encode_xer;
#endif  /* !defined(ASN_DISABLE_XER_SUPPORT) */

#if !defined(ASN_DISABLE_JER_SUPPORT)
jer_type_decoder_f NULL_decode_jer_kpm_v3_00;
jer_type_encoder_f NULL_encode_jer_kpm_v3_00;
#endif  /* !defined(ASN_DISABLE_JER_SUPPORT) */

#if !defined(ASN_DISABLE_OER_SUPPORT)
oer_type_decoder_f NULL_decode_oer;
oer_type_encoder_f NULL_encode_oer;
#endif  /* !defined(ASN_DISABLE_OER_SUPPORT) */

#if !defined(ASN_DISABLE_UPER_SUPPORT)
per_type_decoder_f NULL_decode_uper;
per_type_encoder_f NULL_encode_uper;
#endif  /* !defined(ASN_DISABLE_UPER_SUPPORT) */
#if !defined(ASN_DISABLE_APER_SUPPORT)
per_type_decoder_f NULL_decode_aper_kpm_v3_00;
per_type_encoder_f NULL_encode_aper_kpm_v3_00;
#endif  /* !defined(ASN_DISABLE_APER_SUPPORT) */

#if !defined(ASN_DISABLE_RFILL_SUPPORT)
asn_random_fill_kpm_v3_00_f  NULL_random_fill_kpm_v3_00;
#endif  /* !defined(ASN_DISABLE_RFILL_SUPPORT) */

#ifdef __cplusplus
}
#endif

#endif	/* NULL_H */
