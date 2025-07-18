/*-
 * Copyright (c) 2003-2017 Lev Walkin <vlm@lionet.info>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	CONSTR_SET_OF_H
#define	CONSTR_SET_OF_H

#include <asn_application.h>
#include <asn_SET_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct asn_SET_OF_specifics_s {
    /*
     * Target structure description.
     */
    unsigned struct_size;       /* Size of the target structure. */
    unsigned ctx_offset;        /* Offset of the asn_struct_ctx_t member */

    /* XER-specific stuff */
    int as_XMLValueList; /* The member type must be encoded like this */
} asn_SET_OF_specifics_t;

/*
 * A set specialized functions dealing with the SET OF type.
 */
asn_struct_free_f SET_OF_free_kpm_v3_00;

#if !defined(ASN_DISABLE_PRINT_SUPPORT)
asn_struct_print_f SET_OF_print_kpm_v3_00;
#endif  /* !defined(ASN_DISABLE_PRINT_SUPPORT) */

asn_struct_compare_f SET_OF_compare_kpm_v3_00;
asn_struct_copy_f    SET_OF_copy_kpm_v3_00;

asn_constr_check_f SET_OF_constraint_kpm_v3_00;

#if !defined(ASN_DISABLE_BER_SUPPORT)
ber_type_decoder_f SET_OF_decode_ber;
der_type_encoder_f SET_OF_encode_der;
#endif  /* !defined(ASN_DISABLE_BER_SUPPORT) */

#if !defined(ASN_DISABLE_XER_SUPPORT)
xer_type_decoder_f SET_OF_decode_xer;
xer_type_encoder_f SET_OF_encode_xer;
#endif  /* !defined(ASN_DISABLE_XER_SUPPORT) */

#if !defined(ASN_DISABLE_JER_SUPPORT)
jer_type_decoder_f SET_OF_decode_jer_kpm_v3_00;
jer_type_encoder_f SET_OF_encode_jer_kpm_v3_00;
#endif  /* !defined(ASN_DISABLE_JER_SUPPORT) */

#if !defined(ASN_DISABLE_OER_SUPPORT)
oer_type_decoder_f SET_OF_decode_oer;
oer_type_encoder_f SET_OF_encode_oer;
#endif  /* !defined(ASN_DISABLE_OER_SUPPORT) */

#if !defined(ASN_DISABLE_UPER_SUPPORT)
per_type_decoder_f SET_OF_decode_uper;
per_type_encoder_f SET_OF_encode_uper;
#endif  /* !defined(ASN_DISABLE_UPER_SUPPORT) */
#if !defined(ASN_DISABLE_APER_SUPPORT)
per_type_decoder_f SET_OF_decode_aper_kpm_v3_00;
per_type_encoder_f SET_OF_encode_aper_kpm_v3_00;
#endif  /* !defined(ASN_DISABLE_APER_SUPPORT) */

#if !defined(ASN_DISABLE_RFILL_SUPPORT)
asn_random_fill_kpm_v3_00_f SET_OF_random_fill_kpm_v3_00;
#endif  /* !defined(ASN_DISABLE_RFILL_SUPPORT) */

extern asn_TYPE_operation_t asn_OP_SET_OF_kpm_v3_00;

/*
 * Internally visible buffer holding a single encoded element.
 */
struct _el_buffer {
    uint8_t *buf;
    size_t length;
    size_t allocated_size;
    unsigned bits_unused;
};

enum SET_OF__encode_method {
    SOES_DER,   /* Distinguished Encoding Rules */
    SOES_CUPER,  /* Canonical Unaligned Packed Encoding Rules */
    SOES_CAPER  /* Canonical Aligned Packed Encoding Rules */
};

struct _el_buffer * SET_OF__encode_sorted_kpm_v3_00(
        const asn_TYPE_member_t *elm,
        const asn_anonymous_set_ *list,
        enum SET_OF__encode_method method);

void SET_OF__encode_sorted_kpm_v3_00_free(
        struct _el_buffer *el_buf,
        size_t count);

#ifdef __cplusplus
}
#endif

#endif	/* CONSTR_SET_OF_H */
