/*-
 * Copyright (c) 2003-2017 Lev Walkin <vlm@lionet.info>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_CONSTR_SEQUENCE_H_
#define	_CONSTR_SEQUENCE_H_

#include <asn_application.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct asn_SEQUENCE_specifics_s {
	/*
	 * Target structure description.
	 */
	unsigned struct_size;	/* Size of the target structure. */
	unsigned ctx_offset;	/* Offset of the asn_struct_ctx_t member */

	/*
	 * Tags to members mapping table (sorted).
	 */
	const asn_TYPE_tag2member_t *tag2el;
	unsigned tag2el_count;

	/*
	 * Optional members of the extensions root (roms) or additions (aoms).
	 * Meaningful for PER.
	 */
	const int *oms;         /* Optional MemberS */
	unsigned roms_count;    /* Root optional members count */
	unsigned aoms_count;    /* Additions optional members count */

	/*
	 * Description of an extensions group.
	 * Root components are clustered at the beginning of the structure,
	 * whereas extensions are clustered at the end. -1 means not extensible.
	 */
	signed first_extension;       /* First extension addition */
} asn_SEQUENCE_specifics_t;


/*
 * A set specialized functions dealing with the SEQUENCE type.
 */
asn_struct_free_f SEQUENCE_free_rc_v1_03;

#if !defined(ASN_DISABLE_PRINT_SUPPORT)
asn_struct_print_f SEQUENCE_print_rc_v1_03;
#endif  /* !defined(ASN_DISABLE_PRINT_SUPPORT) */

asn_struct_compare_f SEQUENCE_compare_rc_v1_03;
asn_struct_copy_f SEQUENCE_copy_rc_v1_03;

asn_constr_check_f SEQUENCE_constraint_rc_v1_03;

#if !defined(ASN_DISABLE_BER_SUPPORT)
ber_type_decoder_f SEQUENCE_decode_ber;
der_type_encoder_f SEQUENCE_encode_der;
#endif  /* !defined(ASN_DISABLE_BER_SUPPORT) */

#if !defined(ASN_DISABLE_XER_SUPPORT)
xer_type_decoder_f SEQUENCE_decode_xer;
xer_type_encoder_f SEQUENCE_encode_xer;
#endif  /* !defined(ASN_DISABLE_XER_SUPPORT) */

#if !defined(ASN_DISABLE_JER_SUPPORT)
jer_type_decoder_f SEQUENCE_decode_jer_rc_v1_03;
jer_type_encoder_f SEQUENCE_encode_jer_rc_v1_03;
#endif  /* !defined(ASN_DISABLE_JER_SUPPORT) */

#if !defined(ASN_DISABLE_OER_SUPPORT)
oer_type_decoder_f SEQUENCE_decode_oer;
oer_type_encoder_f SEQUENCE_encode_oer;
#endif  /* !defined(ASN_DISABLE_OER_SUPPORT) */

#if !defined(ASN_DISABLE_UPER_SUPPORT)
per_type_decoder_f SEQUENCE_decode_uper;
per_type_encoder_f SEQUENCE_encode_uper;
#endif  /* !defined(ASN_DISABLE_UPER_SUPPORT) */
#if !defined(ASN_DISABLE_APER_SUPPORT)
per_type_decoder_f SEQUENCE_decode_aper_rc_v1_03;
per_type_encoder_f SEQUENCE_encode_aper_rc_v1_03;
#endif  /* !defined(ASN_DISABLE_APER_SUPPORT) */

#if !defined(ASN_DISABLE_RFILL_SUPPORT)
asn_random_fill_rc_v1_03_f SEQUENCE_random_fill_rc_v1_03;
#endif  /* !defined(ASN_DISABLE_RFILL_SUPPORT) */

extern asn_TYPE_operation_t asn_OP_SEQUENCE_rc_v1_03;

#ifdef __cplusplus
}
#endif

#endif	/* _CONSTR_SEQUENCE_H_ */
