/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2AP-IEs"
 * 	found in "e2ap-v01.01.asn1"
 * 	`asn1c -gen-APER -no-gen-OER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps`
 */

#ifndef	_TNLinformation_H_
#define	_TNLinformation_H_


#include <asn_application.h>

/* Including external dependencies */
#include <BIT_STRING.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* TNLinformation */
typedef struct TNLinformation {
	BIT_STRING_t	 tnlAddress;
	BIT_STRING_t	*tnlPort;	/* OPTIONAL */
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} TNLinformation_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_TNLinformation_e2ap_v1_01;
extern asn_SEQUENCE_specifics_t asn_SPC_TNLinformation_specs_1_e2ap_v1_01;
extern asn_TYPE_member_t asn_MBR_TNLinformation_1_e2ap_v1_01[2];

#ifdef __cplusplus
}
#endif

#endif	/* _TNLinformation_H_ */
#include <asn_internal.h>
