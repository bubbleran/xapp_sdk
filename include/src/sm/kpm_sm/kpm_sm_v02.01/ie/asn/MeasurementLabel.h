/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-KPM-IEs"
 * 	found in "e2sm_kpm_v02.01_standard.asn1"
 * 	`asn1c -S /home/mir/workspace/asn1c_mouse/skeletons/ -no-gen-BER -no-gen-UPER -no-gen-OER -no-gen-JER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps`
 */

#ifndef	_MeasurementLabel_H_
#define	_MeasurementLabel_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>
#include "PLMNIdentity.h"
#include "FiveQI.h"
#include "QosFlowIdentifier.h"
#include "QCI.h"
#include <NativeInteger.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum MeasurementLabel__noLabel {
	MeasurementLabel__noLabel_true	= 0
	/*
	 * Enumeration is extensible
	 */
} e_MeasurementLabel__noLabel;
typedef enum MeasurementLabel__sUM {
	MeasurementLabel__sUM_true	= 0
	/*
	 * Enumeration is extensible
	 */
} e_MeasurementLabel__sUM;
typedef enum MeasurementLabel__preLabelOverride {
	MeasurementLabel__preLabelOverride_true	= 0
	/*
	 * Enumeration is extensible
	 */
} e_MeasurementLabel__preLabelOverride;
typedef enum MeasurementLabel__startEndInd {
	MeasurementLabel__startEndInd_start	= 0,
	MeasurementLabel__startEndInd_end	= 1
	/*
	 * Enumeration is extensible
	 */
} e_MeasurementLabel__startEndInd;
typedef enum MeasurementLabel__min {
	MeasurementLabel__min_true	= 0
	/*
	 * Enumeration is extensible
	 */
} e_MeasurementLabel__min;
typedef enum MeasurementLabel__max {
	MeasurementLabel__max_true	= 0
	/*
	 * Enumeration is extensible
	 */
} e_MeasurementLabel__max;
typedef enum MeasurementLabel__avg {
	MeasurementLabel__avg_true	= 0
	/*
	 * Enumeration is extensible
	 */
} e_MeasurementLabel__avg;

/* Forward declarations */
struct S_NSSAI;

/* MeasurementLabel */
typedef struct MeasurementLabel {
	long	*noLabel;	/* OPTIONAL */
	PLMNIdentity_t	*plmnID;	/* OPTIONAL */
	struct S_NSSAI	*sliceID;	/* OPTIONAL */
	FiveQI_t	*fiveQI;	/* OPTIONAL */
	QosFlowIdentifier_t	*qFI;	/* OPTIONAL */
	QCI_t	*qCI;	/* OPTIONAL */
	QCI_t	*qCImax;	/* OPTIONAL */
	QCI_t	*qCImin;	/* OPTIONAL */
	long	*aRPmax;	/* OPTIONAL */
	long	*aRPmin;	/* OPTIONAL */
	long	*bitrateRange;	/* OPTIONAL */
	long	*layerMU_MIMO;	/* OPTIONAL */
	long	*sUM;	/* OPTIONAL */
	long	*distBinX;	/* OPTIONAL */
	long	*distBinY;	/* OPTIONAL */
	long	*distBinZ;	/* OPTIONAL */
	long	*preLabelOverride;	/* OPTIONAL */
	long	*startEndInd;	/* OPTIONAL */
	long	*min;	/* OPTIONAL */
	long	*max;	/* OPTIONAL */
	long	*avg;	/* OPTIONAL */
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MeasurementLabel_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_noLabel_2_kpm_v2_01;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_sUM_16_kpm_v2_01;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_preLabelOverride_22_kpm_v2_01;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_startEndInd_25_kpm_v2_01;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_min_29_kpm_v2_01;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_max_32_kpm_v2_01;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_avg_35_kpm_v2_01;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_MeasurementLabel_kpm_v2_01;
extern asn_SEQUENCE_specifics_t asn_SPC_MeasurementLabel_specs_1_kpm_v2_01;
extern asn_TYPE_member_t asn_MBR_MeasurementLabel_1_kpm_v2_01[21];

#ifdef __cplusplus
}
#endif

#endif	/* _MeasurementLabel_H_ */
#include <asn_internal.h>
