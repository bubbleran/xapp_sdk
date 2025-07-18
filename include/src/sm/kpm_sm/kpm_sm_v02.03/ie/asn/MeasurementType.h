/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-KPM-IEs"
 * 	found in "e2sm_kpm_v02.03_standard.asn1"
 * 	`asn1c -S /home/mir/workspace/asn1c_mouse/skeletons/ -no-gen-BER -no-gen-UPER -no-gen-OER -no-gen-JER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps`
 */

#ifndef	_MeasurementType_H_
#define	_MeasurementType_H_


#include <asn_application.h>

/* Including external dependencies */
#include "MeasurementTypeName.h"
#include "MeasurementTypeID.h"
#include <constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum MeasurementType_PR {
	MeasurementType_PR_NOTHING,	/* No components present */
	MeasurementType_PR_measName,
	MeasurementType_PR_measID
	/* Extensions may appear below */
	
} MeasurementType_PR;

/* MeasurementType */
typedef struct MeasurementType {
	MeasurementType_PR present;
	union MeasurementType_u {
		MeasurementTypeName_t	 measName;
		MeasurementTypeID_t	 measID;
		/*
		 * This type is extensible,
		 * possible extensions are below.
		 */
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MeasurementType_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MeasurementType_kpm_v2_03;
extern asn_CHOICE_specifics_t asn_SPC_MeasurementType_specs_1_kpm_v2_03;
extern asn_TYPE_member_t asn_MBR_MeasurementType_1_kpm_v2_03[2];
extern asn_per_constraints_t asn_PER_type_MeasurementType_constr_1_kpm_v2_03;

#ifdef __cplusplus
}
#endif

#endif	/* _MeasurementType_H_ */
#include <asn_internal.h>
