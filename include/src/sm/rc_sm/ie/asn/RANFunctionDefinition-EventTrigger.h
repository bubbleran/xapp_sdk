/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-RC-IEs"
 * 	found in "e2sm_rc_v1_03_modified.asn"
 * 	`asn1c -no-gen-BER -no-gen-UPER -no-gen-OER -no-gen-XER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps -S ../../../../../../asn1c_oai/skeletons/`
 */

#ifndef	_RANFunctionDefinition_EventTrigger_H_
#define	_RANFunctionDefinition_EventTrigger_H_


#include <asn_application.h>

/* Including external dependencies */
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct RANFunctionDefinition_EventTrigger_Style_Item;
struct L2Parameters_RANParameter_Item;
struct RANFunctionDefinition_EventTrigger_CallProcess_Item;
struct UEIdentification_RANParameter_Item;
struct CellIdentification_RANParameter_Item;

/* RANFunctionDefinition-EventTrigger */
typedef struct RANFunctionDefinition_EventTrigger {
	struct RANFunctionDefinition_EventTrigger__ric_EventTriggerStyle_List {
		A_SEQUENCE_OF(struct RANFunctionDefinition_EventTrigger_Style_Item) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} ric_EventTriggerStyle_List;
	struct RANFunctionDefinition_EventTrigger__ran_L2Parameters_List {
		A_SEQUENCE_OF(struct L2Parameters_RANParameter_Item) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *ran_L2Parameters_List;
	struct RANFunctionDefinition_EventTrigger__ran_CallProcessTypes_List {
		A_SEQUENCE_OF(struct RANFunctionDefinition_EventTrigger_CallProcess_Item) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *ran_CallProcessTypes_List;
	struct RANFunctionDefinition_EventTrigger__ran_UEIdentificationParameters_List {
		A_SEQUENCE_OF(struct UEIdentification_RANParameter_Item) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *ran_UEIdentificationParameters_List;
	struct RANFunctionDefinition_EventTrigger__ran_CellIdentificationParameters_List {
		A_SEQUENCE_OF(struct CellIdentification_RANParameter_Item) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *ran_CellIdentificationParameters_List;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RANFunctionDefinition_EventTrigger_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RANFunctionDefinition_EventTrigger_rc_v1_03;
extern asn_SEQUENCE_specifics_t asn_SPC_RANFunctionDefinition_EventTrigger_specs_1_rc_v1_03;
extern asn_TYPE_member_t asn_MBR_RANFunctionDefinition_EventTrigger_1_rc_v1_03[5];

#ifdef __cplusplus
}
#endif

#endif	/* _RANFunctionDefinition_EventTrigger_H_ */
#include <asn_internal.h>
