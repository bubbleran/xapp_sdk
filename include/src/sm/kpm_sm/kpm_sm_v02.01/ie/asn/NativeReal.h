/*-
 * Copyright (c) 2004-2017 Lev Walkin <vlm@lionet.info>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
/*
 * This type differs from the standard REAL in that it is modelled using
 * the fixed machine type (double), so it can hold only values of
 * limited precision. There is no explicit type (i.e., NativeReal_t).
 * Use of this type is normally enabled by -fnative-types.
 */
#ifndef	ASN_TYPE_NativeReal_H
#define	ASN_TYPE_NativeReal_H

#include <asn_application.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct asn_NativeReal_specifics_s {
    unsigned float_size; /* sizeof(float) or sizeof(double) */
} asn_NativeReal_specifics_t;

extern asn_TYPE_descriptor_t asn_DEF_NativeReal_kpm_v2_01;
extern asn_TYPE_operation_t asn_OP_NativeReal_kpm_v2_01;

size_t NativeReal__float_size_kpm_v2_01(const asn_TYPE_descriptor_t *td);
double NativeReal__get_double_kpm_v2_01(const asn_TYPE_descriptor_t *td,
                              const void *ptr);
ssize_t NativeReal__set_kpm_v2_01(const asn_TYPE_descriptor_t *td, void **sptr,
                        double d);

asn_struct_free_f  NativeReal_free_kpm_v2_01;

#if !defined(ASN_DISABLE_PRINT_SUPPORT)
asn_struct_print_f NativeReal_print_kpm_v2_01;
#endif  /* !defined(ASN_DISABLE_PRINT_SUPPORT) */

asn_struct_compare_f NativeReal_compare_kpm_v2_01;

#define NativeReal_constraint asn_generic_no_constraint_kpm_v2_01

#if !defined(ASN_DISABLE_BER_SUPPORT)
ber_type_decoder_f NativeReal_decode_ber;
der_type_encoder_f NativeReal_encode_der;
#endif  /* !defined(ASN_DISABLE_BER_SUPPORT) */

#if !defined(ASN_DISABLE_XER_SUPPORT)
xer_type_decoder_f NativeReal_decode_xer_kpm_v2_01;
xer_type_encoder_f NativeReal_encode_xer_kpm_v2_01;
#endif  /* !defined(ASN_DISABLE_XER_SUPPORT) */

#if !defined(ASN_DISABLE_JER_SUPPORT)
jer_type_decoder_f NativeReal_decode_jer;
jer_type_encoder_f NativeReal_encode_jer;
#endif  /* !defined(ASN_DISABLE_JER_SUPPORT) */

#if !defined(ASN_DISABLE_OER_SUPPORT)
oer_type_decoder_f NativeReal_decode_oer;
oer_type_encoder_f NativeReal_encode_oer;
#endif  /* !defined(ASN_DISABLE_OER_SUPPORT) */

#if !defined(ASN_DISABLE_UPER_SUPPORT)
per_type_decoder_f NativeReal_decode_uper;
per_type_encoder_f NativeReal_encode_uper;
#endif  /* !defined(ASN_DISABLE_UPER_SUPPORT) */
#if !defined(ASN_DISABLE_APER_SUPPORT)
per_type_decoder_f NativeReal_decode_aper_kpm_v2_01;
per_type_encoder_f NativeReal_encode_aper_kpm_v2_01;
#endif  /* !defined(ASN_DISABLE_APER_SUPPORT) */

#if !defined(ASN_DISABLE_RFILL_SUPPORT)
asn_random_fill_kpm_v2_01_f  NativeReal_random_fill_kpm_v2_01;
#endif  /* !defined(ASN_DISABLE_RFILL_SUPPORT) */

#ifdef __cplusplus
}
#endif

#endif	/* ASN_TYPE_NativeReal_H */
