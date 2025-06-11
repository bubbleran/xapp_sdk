/*
 * Copyright (c) 2003-2017 Lev Walkin <vlm@lionet.info>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_CONSTR_CHOICE_H_
#define	_CONSTR_CHOICE_H_

#include <asn_application.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct asn_CHOICE_specifics_s {
	/*
	 * Target structure description.
	 */
	unsigned struct_size;       /* Size of the target structure. */
	unsigned ctx_offset;        /* Offset of the asn_codec_ctx_t member */
	unsigned pres_offset;       /* Identifier of the present member */
	unsigned pres_size;         /* Size of the identifier (enum) */

	/*
	 * Tags to members mapping table.
	 */
	const asn_TYPE_tag2member_t *tag2el;
	unsigned tag2el_count;

	/* Canonical ordering of CHOICE elements, for PER */
	const unsigned *to_canonical_order;
	const unsigned *from_canonical_order;

	/*
	 * Extensions-related stuff.
	 */
	signed ext_start; /* First member of extensions, or -1 */
} asn_CHOICE_specifics_t;

/*
 * A set specialized functions dealing with the CHOICE type.
 */
asn_struct_free_f CHOICE_free_e2ap_v1_01;

#if !defined(ASN_DISABLE_PRINT_SUPPORT)
asn_struct_print_f CHOICE_print_e2ap_v1_01;
#endif  /* !defined(ASN_DISABLE_PRINT_SUPPORT) */

asn_struct_compare_f CHOICE_compare_e2ap_v1_01;

asn_constr_check_f CHOICE_constraint_e2ap_v1_01;

#if !defined(ASN_DISABLE_BER_SUPPORT)
ber_type_decoder_f CHOICE_decode_ber_e2ap_v1_01;
der_type_encoder_f CHOICE_encode_der_e2ap_v1_01;
#endif  /* !defined(ASN_DISABLE_BER_SUPPORT) */

#if !defined(ASN_DISABLE_XER_SUPPORT)
xer_type_decoder_f CHOICE_decode_xer_e2ap_v1_01;
xer_type_encoder_f CHOICE_encode_xer_e2ap_v1_01;
#endif  /* !defined(ASN_DISABLE_XER_SUPPORT) */

#if !defined(ASN_DISABLE_JER_SUPPORT)
jer_type_encoder_f CHOICE_encode_jer;
#endif  /* !defined(ASN_DISABLE_JER_SUPPORT) */

#if !defined(ASN_DISABLE_OER_SUPPORT)
oer_type_decoder_f CHOICE_decode_oer;
oer_type_encoder_f CHOICE_encode_oer;
#endif  /* !defined(ASN_DISABLE_OER_SUPPORT) */

#if !defined(ASN_DISABLE_UPER_SUPPORT)
per_type_decoder_f CHOICE_decode_uper_e2ap_v1_01;
per_type_encoder_f CHOICE_encode_uper_e2ap_v1_01;
#endif  /* !defined(ASN_DISABLE_UPER_SUPPORT) */
#if !defined(ASN_DISABLE_APER_SUPPORT)
per_type_decoder_f CHOICE_decode_aper_e2ap_v1_01;
per_type_encoder_f CHOICE_encode_aper_e2ap_v1_01;
#endif  /* !defined(ASN_DISABLE_APER_SUPPORT) */

#if !defined(ASN_DISABLE_RFILL_SUPPORT)
asn_random_fill_e2ap_v1_01_f CHOICE_random_fill_e2ap_v1_01;
#endif  /* !defined(ASN_DISABLE_RFILL_SUPPORT) */

asn_outmost_tag_f CHOICE_outmost_tag_e2ap_v1_01;

extern asn_TYPE_operation_t asn_OP_CHOICE_e2ap_v1_01;

unsigned _fetch_present_idx_e2ap_v1_01(
        const void *struct_ptr,
        unsigned off,
        unsigned size);

void _set_present_idx_e2ap_v1_01(
        void *sptr,
        unsigned offset,
        unsigned size,
        unsigned present);

/*
 * Return the 1-based choice variant presence index.
 * Returns 0 in case of error.
 */
unsigned CHOICE_variant_get_presence_e2ap_v1_01(const asn_TYPE_descriptor_t *td,
                                     const void *structure_ptr);

/*
 * Sets or resets the 1-based choice variant presence index.
 * In case a previous index is not zero, the currently selected structure
 * member is freed and zeroed-out first.
 * Returns 0 on success and -1 on error.
 */
int CHOICE_variant_set_presence_e2ap_v1_01(const asn_TYPE_descriptor_t *td,
                                void *structure_ptr, unsigned present);

#ifdef __cplusplus
}
#endif

#endif	/* _CONSTR_CHOICE_H_ */
