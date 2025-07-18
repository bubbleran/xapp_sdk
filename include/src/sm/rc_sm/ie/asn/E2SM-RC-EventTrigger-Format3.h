/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-RC-IEs"
 * 	found in "e2sm_rc_v1_03_modified.asn"
 * 	`asn1c -no-gen-BER -no-gen-UPER -no-gen-OER -no-gen-XER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps -S ../../../../../../asn1c_oai/skeletons/`
 */

#ifndef	_E2SM_RC_EventTrigger_Format3_H_
#define	_E2SM_RC_EventTrigger_Format3_H_


#include <asn_application.h>

/* Including external dependencies */
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct E2SM_RC_EventTrigger_Format3_Item;

/* E2SM-RC-EventTrigger-Format3 */
typedef struct E2SM_RC_EventTrigger_Format3 {
	struct E2SM_RC_EventTrigger_Format3__e2NodeInfoChange_List {
		A_SEQUENCE_OF(struct E2SM_RC_EventTrigger_Format3_Item) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} e2NodeInfoChange_List;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} E2SM_RC_EventTrigger_Format3_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_E2SM_RC_EventTrigger_rc_v1_03_Format3;
extern asn_SEQUENCE_specifics_t asn_SPC_E2SM_RC_EventTrigger_Format3_specs_1_rc_v1_03;
extern asn_TYPE_member_t asn_MBR_E2SM_RC_EventTrigger_Format3_1_rc_v1_03[1];

#ifdef __cplusplus
}
#endif

#endif	/* _E2SM_RC_EventTrigger_Format3_H_ */
#include <asn_internal.h>
