/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-COMMON-IEs"
 * 	found in "e2sm_rc_v1_03_modified.asn"
 * 	`asn1c -no-gen-BER -no-gen-UPER -no-gen-OER -no-gen-XER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps -S ../../../../../../asn1c_oai/skeletons/`
 */

#ifndef	_NGENB_DU_ID_H_
#define	_NGENB_DU_ID_H_


#include <asn_application.h>

/* Including external dependencies */
#include <INTEGER.h>

#ifdef __cplusplus
extern "C" {
#endif

/* NGENB-DU-ID */
typedef INTEGER_t	 NGENB_DU_ID_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_NGENB_DU_ID_constr_1_rc_v1_03;
extern asn_TYPE_descriptor_t asn_DEF_NGENB_DU_ID_rc_v1_03;
asn_struct_free_f NGENB_DU_ID_free;
asn_struct_print_f NGENB_DU_ID_print;
asn_constr_check_f NGENB_DU_ID_constraint_rc_v1_03;
jer_type_encoder_f NGENB_DU_ID_encode_jer;
per_type_decoder_f NGENB_DU_ID_decode_aper;
per_type_encoder_f NGENB_DU_ID_encode_aper;

#ifdef __cplusplus
}
#endif

#endif	/* _NGENB_DU_ID_H_ */
#include <asn_internal.h>
