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

extern asn_TYPE_descriptor_t asn_DEF_NativeReal_rc_v1_03;
extern asn_TYPE_operation_t asn_OP_NativeReal_rc_v1_03;

size_t NativeReal__float_size_rc_v1_03(const asn_TYPE_descriptor_t *td);
double NativeReal__get_double_rc_v1_03(const asn_TYPE_descriptor_t *td,
                              const void *ptr);
ssize_t NativeReal__set_rc_v1_03(const asn_TYPE_descriptor_t *td, void **sptr,
                        double d);

asn_struct_free_f  NativeReal_free_rc_v1_03;

#if !defined(ASN_DISABLE_PRINT_SUPPORT)
asn_struct_print_f NativeReal_print_rc_v1_03;
#endif  /* !defined(ASN_DISABLE_PRINT_SUPPORT) */

asn_struct_compare_f NativeReal_compare_rc_v1_03;
asn_struct_copy_f    NativeReal_copy_rc_v1_03;

#define NativeReal_constraint asn_generic_no_constraint_rc_v1_03

#if !defined(ASN_DISABLE_BER_SUPPORT)
ber_type_decoder_f NativeReal_decode_ber;
der_type_encoder_f NativeReal_encode_der;
#endif  /* !defined(ASN_DISABLE_BER_SUPPORT) */

#if !defined(ASN_DISABLE_XER_SUPPORT)
xer_type_decoder_f NativeReal_decode_xer;
xer_type_encoder_f NativeReal_encode_xer;
#endif  /* !defined(ASN_DISABLE_XER_SUPPORT) */

#if !defined(ASN_DISABLE_JER_SUPPORT)
jer_type_decoder_f NativeReal_decode_jer_rc_v1_03;
jer_type_encoder_f NativeReal_encode_jer_rc_v1_03;
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
per_type_decoder_f NativeReal_decode_aper_rc_v1_03;
per_type_encoder_f NativeReal_encode_aper_rc_v1_03;
#endif  /* !defined(ASN_DISABLE_APER_SUPPORT) */

#if !defined(ASN_DISABLE_RFILL_SUPPORT)
asn_random_fill_rc_v1_03_f  NativeReal_random_fill_rc_v1_03;
#endif  /* !defined(ASN_DISABLE_RFILL_SUPPORT) */

#ifdef __cplusplus
}
#endif

#endif	/* ASN_TYPE_NativeReal_H */
