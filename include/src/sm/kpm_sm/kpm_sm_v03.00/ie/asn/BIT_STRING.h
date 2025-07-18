/*-
 * Copyright (c) 2003-2017 Lev Walkin <vlm@lionet.info>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_BIT_STRING_H_
#define	_BIT_STRING_H_

#include <OCTET_STRING.h>	/* Some help from OCTET STRING */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BIT_STRING_s {
	uint8_t *buf;	/* BIT STRING body */
	size_t size;	/* Size of the above buffer */

	int bits_unused;/* Unused trailing bits in the last octet (0..7) */

	asn_struct_ctx_t _asn_ctx;	/* Parsing across buffer boundaries */
} BIT_STRING_t;

extern asn_TYPE_descriptor_t asn_DEF_BIT_STRING_kpm_v3_00;
extern asn_TYPE_operation_t asn_OP_BIT_STRING_kpm_v3_00;
extern asn_OCTET_STRING_specifics_t asn_SPC_BIT_STRING_specs_kpm_v3_00;

#define BIT_STRING_free OCTET_STRING_free_kpm_v3_00

#if !defined(ASN_DISABLE_PRINT_SUPPORT)
asn_struct_print_f BIT_STRING_print_kpm_v3_00;  /* Human-readable output */
#endif  /* !defined(ASN_DISABLE_PRINT_SUPPORT) */

asn_struct_compare_f BIT_STRING_compare_kpm_v3_00;
asn_struct_copy_f    BIT_STRING_copy_kpm_v3_00;

asn_constr_check_f BIT_STRING_constraint_kpm_v3_00;

#if !defined(ASN_DISABLE_BER_SUPPORT)
#define BIT_STRING_decode_ber OCTET_STRING_decode_ber
#define BIT_STRING_encode_der OCTET_STRING_encode_der
#endif  /* !defined(ASN_DISABLE_BER_SUPPORT) */

#if !defined(ASN_DISABLE_XER_SUPPORT)
#define BIT_STRING_decode_xer OCTET_STRING_decode_xer_binary
xer_type_encoder_f BIT_STRING_encode_xer;
#endif  /* !defined(ASN_DISABLE_XER_SUPPORT) */

#if !defined(ASN_DISABLE_JER_SUPPORT)
#define BIT_STRING_decode_jer OCTET_STRING_decode_jer_binary
jer_type_encoder_f BIT_STRING_encode_jer_kpm_v3_00;
#endif  /* !defined(ASN_DISABLE_JER_SUPPORT) */

#if !defined(ASN_DISABLE_OER_SUPPORT)
oer_type_decoder_f BIT_STRING_decode_oer;
oer_type_encoder_f BIT_STRING_encode_oer;
#endif  /* !defined(ASN_DISABLE_OER_SUPPORT) */

#if !defined(ASN_DISABLE_UPER_SUPPORT)
per_type_decoder_f BIT_STRING_decode_uper;
per_type_encoder_f BIT_STRING_encode_uper;
#endif  /* !defined(ASN_DISABLE_UPER_SUPPORT) */
#if !defined(ASN_DISABLE_APER_SUPPORT)
#define BIT_STRING_decode_aper OCTET_STRING_decode_aper_kpm_v3_00
#define BIT_STRING_encode_aper OCTET_STRING_encode_aper_kpm_v3_00
#endif  /* !defined(ASN_DISABLE_APER_SUPPORT) */

#if !defined(ASN_DISABLE_RFILL_SUPPORT)
asn_random_fill_kpm_v3_00_f BIT_STRING_random_fill_kpm_v3_00;
#endif  /* !defined(ASN_DISABLE_RFILL_SUPPORT) */

const BIT_STRING_t *BIT_STRING__compactify_kpm_v3_00(const BIT_STRING_t *st, BIT_STRING_t *tmp);

#ifdef __cplusplus
}
#endif

#endif	/* _BIT_STRING_H_ */
