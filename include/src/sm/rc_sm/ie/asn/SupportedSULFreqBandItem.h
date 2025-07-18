/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-COMMON-IEs"
 * 	found in "e2sm_rc_v1_03_modified.asn"
 * 	`asn1c -no-gen-BER -no-gen-UPER -no-gen-OER -no-gen-XER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps -S ../../../../../../asn1c_oai/skeletons/`
 */

#ifndef	_SupportedSULFreqBandItem_H_
#define	_SupportedSULFreqBandItem_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* SupportedSULFreqBandItem */
typedef struct SupportedSULFreqBandItem {
	long	 freqBandIndicatorNr;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SupportedSULFreqBandItem_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SupportedSULFreqBandItem_rc_v1_03;
extern asn_SEQUENCE_specifics_t asn_SPC_SupportedSULFreqBandItem_specs_1_rc_v1_03;
extern asn_TYPE_member_t asn_MBR_SupportedSULFreqBandItem_1_rc_v1_03[1];

#ifdef __cplusplus
}
#endif

#endif	/* _SupportedSULFreqBandItem_H_ */
#include <asn_internal.h>
