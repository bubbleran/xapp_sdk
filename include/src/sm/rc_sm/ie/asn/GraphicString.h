/*-
 * Copyright (c) 2003-2017 Lev Walkin <vlm@lionet.info>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_GraphicString_H_
#define	_GraphicString_H_

#include <OCTET_STRING.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef OCTET_STRING_t GraphicString_t;	/* Implemented via OCTET STRING */

extern asn_TYPE_descriptor_t asn_DEF_GraphicString_rc_v1_03;
extern asn_TYPE_operation_t asn_OP_GraphicString_rc_v1_03;

#define GraphicString_free OCTET_STRING_free_rc_v1_03

#if !defined(ASN_DISABLE_PRINT_SUPPORT)
#define GraphicString_print OCTET_STRING_print_rc_v1_03
#endif  /* !defined(ASN_DISABLE_PRINT_SUPPORT) */

#define GraphicString_compare OCTET_STRING_compare_rc_v1_03
#define GraphicString_copy    OCTET_STRING_copy_rc_v1_03

#define GraphicString_constraint asn_generic_unknown_constraint_rc_v1_03

#if !defined(ASN_DISABLE_BER_SUPPORT)
#define GraphicString_decode_ber OCTET_STRING_decode_ber
#define GraphicString_encode_der OCTET_STRING_encode_der
#endif  /* !defined(ASN_DISABLE_BER_SUPPORT) */

#if !defined(ASN_DISABLE_XER_SUPPORT)
#define GraphicString_decode_xer OCTET_STRING_decode_xer_hex
#define GraphicString_encode_xer OCTET_STRING_encode_xer
#endif  /* !defined(ASN_DISABLE_XER_SUPPORT) */

#if !defined(ASN_DISABLE_JER_SUPPORT)
#define GraphicString_decode_jer OCTET_STRING_decode_jer
#define GraphicString_encode_jer OCTET_STRING_encode_jer_rc_v1_03
#endif  /* !defined(ASN_DISABLE_JER_SUPPORT) */

#if !defined(ASN_DISABLE_UPER_SUPPORT)
#define GraphicString_decode_uper OCTET_STRING_decode_uper
#define GraphicString_encode_uper OCTET_STRING_encode_uper
#endif  /* !defined(ASN_DISABLE_UPER_SUPPORT) */
#if !defined(ASN_DISABLE_APER_SUPPORT)
#define GraphicString_decode_aper OCTET_STRING_decode_aper_rc_v1_03
#define GraphicString_encode_aper OCTET_STRING_encode_aper_rc_v1_03
#endif  /* !defined(ASN_DISABLE_APER_SUPPORT) */

#ifdef __cplusplus
}
#endif

#endif	/* _GraphicString_H_ */
