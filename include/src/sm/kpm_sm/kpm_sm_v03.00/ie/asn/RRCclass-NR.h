/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-COMMON-IEs"
 * 	found in "e2sm_kpm_v03.00_modified.asn1"
 * 	`asn1c -no-gen-BER -no-gen-UPER -no-gen-OER -no-gen-XER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps -S ../../../../../../../asn1c_oai/skeletons/`
 */

#ifndef	_RRCclass_NR_H_
#define	_RRCclass_NR_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum RRCclass_NR {
	RRCclass_NR_bCCH_BCH	= 0,
	RRCclass_NR_bCCH_DL_SCH	= 1,
	RRCclass_NR_dL_CCCH	= 2,
	RRCclass_NR_dL_DCCH	= 3,
	RRCclass_NR_pCCH	= 4,
	RRCclass_NR_uL_CCCH	= 5,
	RRCclass_NR_uL_CCCH1	= 6,
	RRCclass_NR_uL_DCCH	= 7
	/*
	 * Enumeration is extensible
	 */
} e_RRCclass_NR;

/* RRCclass-NR */
typedef long	 RRCclass_NR_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_RRCclass_NR_constr_1_kpm_v3_00;
extern asn_TYPE_descriptor_t asn_DEF_RRCclass_NR_kpm_v3_00;
extern const asn_INTEGER_specifics_t asn_SPC_RRCclass_NR_specs_1_kpm_v3_00;
asn_struct_free_f RRCclass_NR_free;
asn_struct_print_f RRCclass_NR_print;
asn_constr_check_f RRCclass_NR_constraint;
jer_type_encoder_f RRCclass_NR_encode_jer;
per_type_decoder_f RRCclass_NR_decode_aper;
per_type_encoder_f RRCclass_NR_encode_aper;

#ifdef __cplusplus
}
#endif

#endif	/* _RRCclass_NR_H_ */
#include <asn_internal.h>
