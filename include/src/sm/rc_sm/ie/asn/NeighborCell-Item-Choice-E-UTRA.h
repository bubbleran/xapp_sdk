/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-RC-IEs"
 * 	found in "e2sm_rc_v1_03_modified.asn"
 * 	`asn1c -no-gen-BER -no-gen-UPER -no-gen-OER -no-gen-XER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps -S ../../../../../../asn1c_oai/skeletons/`
 */

#ifndef	_NeighborCell_Item_Choice_E_UTRA_H_
#define	_NeighborCell_Item_Choice_E_UTRA_H_


#include <asn_application.h>

/* Including external dependencies */
#include "EUTRA-CGI.h"
#include "E-UTRA-PCI.h"
#include "E-UTRA-ARFCN.h"
#include "E-UTRA-TAC.h"
#include <NativeEnumerated.h>
#include <NativeInteger.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum NeighborCell_Item_Choice_E_UTRA__x2_Xn_established {
	NeighborCell_Item_Choice_E_UTRA__x2_Xn_established_true	= 0,
	NeighborCell_Item_Choice_E_UTRA__x2_Xn_established_false	= 1
	/*
	 * Enumeration is extensible
	 */
} e_NeighborCell_Item_Choice_E_UTRA__x2_Xn_established;
typedef enum NeighborCell_Item_Choice_E_UTRA__hO_validated {
	NeighborCell_Item_Choice_E_UTRA__hO_validated_true	= 0,
	NeighborCell_Item_Choice_E_UTRA__hO_validated_false	= 1
	/*
	 * Enumeration is extensible
	 */
} e_NeighborCell_Item_Choice_E_UTRA__hO_validated;

/* NeighborCell-Item-Choice-E-UTRA */
typedef struct NeighborCell_Item_Choice_E_UTRA {
	EUTRA_CGI_t	 eUTRA_CGI;
	E_UTRA_PCI_t	 eUTRA_PCI;
	E_UTRA_ARFCN_t	 eUTRA_ARFCN;
	E_UTRA_TAC_t	 eUTRA_TAC;
	long	 x2_Xn_established;
	long	 hO_validated;
	long	 version;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} NeighborCell_Item_Choice_E_UTRA_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_x2_Xn_established_6_rc_v1_03;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_hO_validated_10_rc_v1_03;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_NeighborCell_Item_rc_v1_03_Choice_E_UTRA;
extern asn_SEQUENCE_specifics_t asn_SPC_NeighborCell_Item_Choice_E_UTRA_specs_1_rc_v1_03;
extern asn_TYPE_member_t asn_MBR_NeighborCell_Item_Choice_E_UTRA_1_rc_v1_03[7];

#ifdef __cplusplus
}
#endif

#endif	/* _NeighborCell_Item_Choice_E_UTRA_H_ */
#include <asn_internal.h>
