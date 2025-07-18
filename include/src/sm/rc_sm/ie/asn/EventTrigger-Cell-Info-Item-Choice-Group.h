/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-RC-IEs"
 * 	found in "e2sm_rc_v1_03_modified.asn"
 * 	`asn1c -no-gen-BER -no-gen-UPER -no-gen-OER -no-gen-XER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps -S ../../../../../../asn1c_oai/skeletons/`
 */

#ifndef	_EventTrigger_Cell_Info_Item_Choice_Group_H_
#define	_EventTrigger_Cell_Info_Item_Choice_Group_H_


#include <asn_application.h>

/* Including external dependencies */
#include "RANParameter-Testing.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* EventTrigger-Cell-Info-Item-Choice-Group */
typedef struct EventTrigger_Cell_Info_Item_Choice_Group {
	RANParameter_Testing_t	 ranParameterTesting;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} EventTrigger_Cell_Info_Item_Choice_Group_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_EventTrigger_Cell_Info_rc_v1_03_Item_Choice_Group;
extern asn_SEQUENCE_specifics_t asn_SPC_EventTrigger_Cell_Info_Item_Choice_Group_specs_1_rc_v1_03;
extern asn_TYPE_member_t asn_MBR_EventTrigger_Cell_Info_Item_Choice_Group_1_rc_v1_03[1];

#ifdef __cplusplus
}
#endif

#endif	/* _EventTrigger_Cell_Info_Item_Choice_Group_H_ */
#include <asn_internal.h>
