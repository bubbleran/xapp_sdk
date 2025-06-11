/*-
 * Copyright (c) 2003-2017 Lev Walkin <vlm@lionet.info>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_ENUMERATED_H_
#define	_ENUMERATED_H_

#include <INTEGER.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef INTEGER_t ENUMERATED_t;		/* Implemented via INTEGER */

extern asn_TYPE_descriptor_t asn_DEF_ENUMERATED_kpm_v2_01;
extern asn_TYPE_operation_t asn_OP_ENUMERATED_kpm_v2_01;

#define ENUMERATED_free ASN__PRIMITIVE_TYPE_free_kpm_v2_01

#if !defined(ASN_DISABLE_PRINT_SUPPORT)
#define ENUMERATED_print INTEGER_print_kpm_v2_01
#endif  /* !defined(ASN_DISABLE_PRINT_SUPPORT) */

#define ENUMERATED_compare INTEGER_compare_kpm_v2_01

#define ENUMERATED_constraint asn_generic_no_constraint_kpm_v2_01

#if !defined(ASN_DISABLE_BER_SUPPORT)
#define ENUMERATED_decode_ber ber_decode_primitive
#define ENUMERATED_encode_der INTEGER_encode_der
#endif  /* !defined(ASN_DISABLE_BER_SUPPORT) */

#if !defined(ASN_DISABLE_XER_SUPPORT)
#define ENUMERATED_decode_xer INTEGER_decode_xer_kpm_v2_01
#define ENUMERATED_encode_xer INTEGER_encode_xer_kpm_v2_01
#endif  /* !defined(ASN_DISABLE_XER_SUPPORT) */

#if !defined(ASN_DISABLE_JER_SUPPORT)
jer_type_decoder_f ENUMERATED_decode_jer;
#define ENUMERATED_encode_jer INTEGER_encode_jer
#endif  /* !defined(ASN_DISABLE_JER_SUPPORT) */

#if !defined(ASN_DISABLE_OER_SUPPORT)
oer_type_decoder_f ENUMERATED_decode_oer;
oer_type_encoder_f ENUMERATED_encode_oer;
#endif  /* !defined(ASN_DISABLE_OER_SUPPORT) */

#if !defined(ASN_DISABLE_UPER_SUPPORT)
per_type_decoder_f ENUMERATED_decode_uper;
per_type_encoder_f ENUMERATED_encode_uper;
#endif  /* !defined(ASN_DISABLE_UPER_SUPPORT) */
#if !defined(ASN_DISABLE_APER_SUPPORT)
per_type_decoder_f ENUMERATED_decode_aper_kpm_v2_01;
per_type_encoder_f ENUMERATED_encode_aper_kpm_v2_01;
#endif  /* !defined(ASN_DISABLE_APER_SUPPORT) */

#if !defined(ASN_DISABLE_RFILL_SUPPORT)
#define ENUMERATED_random_fill INTEGER_random_fill_kpm_v2_01
#endif  /* !defined(ASN_DISABLE_RFILL_SUPPORT) */

#ifdef __cplusplus
}
#endif

#endif	/* _ENUMERATED_H_ */
