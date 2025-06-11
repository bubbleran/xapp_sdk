/*-
 * Copyright (c) 2003-2017 Lev Walkin <vlm@lionet.info>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_CONSTR_SEQUENCE_OF_H_
#define	_CONSTR_SEQUENCE_OF_H_

#include <asn_application.h>
#include <constr_SET_OF.h>		/* Implemented using SET OF */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * A set specialized functions dealing with the SEQUENCE OF type.
 * Generally implemented using SET OF.
 */
#define SEQUENCE_OF_free SET_OF_free_e2ap_v3_01

#if !defined(ASN_DISABLE_PRINT_SUPPORT)
#define SEQUENCE_OF_print SET_OF_print_e2ap_v3_01
#endif  /* !defined(ASN_DISABLE_PRINT_SUPPORT) */

asn_struct_compare_f SEQUENCE_OF_compare_e2ap_v3_01;

#define SEQUENCE_OF_constraint SET_OF_constraint_e2ap_v3_01

#if !defined(ASN_DISABLE_BER_SUPPORT)
#define SEQUENCE_OF_decode_ber SET_OF_decode_ber_e2ap_v3_01
der_type_encoder_f SEQUENCE_OF_encode_der_e2ap_v3_01;
#endif  /* !defined(ASN_DISABLE_BER_SUPPORT) */

#if !defined(ASN_DISABLE_XER_SUPPORT)
#define SEQUENCE_OF_decode_xer SET_OF_decode_xer_e2ap_v3_01
xer_type_encoder_f SEQUENCE_OF_encode_xer_e2ap_v3_01;
#endif  /* !defined(ASN_DISABLE_XER_SUPPORT) */

#if !defined(ASN_DISABLE_JER_SUPPORT)
jer_type_encoder_f SEQUENCE_OF_encode_jer_e2ap_v3_01;
#endif  /* !defined(ASN_DISABLE_JER_SUPPORT) */

#if !defined(ASN_DISABLE_OER_SUPPORT)
#define SEQUENCE_OF_decode_oer SET_OF_decode_oer
#define SEQUENCE_OF_encode_oer SET_OF_encode_oer
#endif  /* !defined(ASN_DISABLE_OER_SUPPORT) */

#if !defined(ASN_DISABLE_UPER_SUPPORT)
#define SEQUENCE_OF_decode_uper SET_OF_decode_uper_e2ap_v3_01
per_type_encoder_f SEQUENCE_OF_encode_uper_e2ap_v3_01;
#endif  /* !defined(ASN_DISABLE_UPER_SUPPORT) */
#if !defined(ASN_DISABLE_APER_SUPPORT)
#define SEQUENCE_OF_decode_aper SET_OF_decode_aper_e2ap_v3_01
per_type_encoder_f SEQUENCE_OF_encode_aper_e2ap_v3_01;
#endif  /* !defined(ASN_DISABLE_APER_SUPPORT) */

#if !defined(ASN_DISABLE_RFILL_SUPPORT)
#define SEQUENCE_OF_random_fill SET_OF_random_fill_e2ap_v3_01
#endif  /* !defined(ASN_DISABLE_RFILL_SUPPORT) */

extern asn_TYPE_operation_t asn_OP_SEQUENCE_e2ap_v3_01_OF;

#ifdef __cplusplus
}
#endif

#endif	/* _CONSTR_SET_OF_H_ */
