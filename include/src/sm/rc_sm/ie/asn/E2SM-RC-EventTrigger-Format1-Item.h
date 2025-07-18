/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-RC-IEs"
 * 	found in "e2sm_rc_v1_03_modified.asn"
 * 	`asn1c -no-gen-BER -no-gen-UPER -no-gen-OER -no-gen-XER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps -S ../../../../../../asn1c_oai/skeletons/`
 */

#ifndef	_E2SM_RC_EventTrigger_Format1_Item_H_
#define	_E2SM_RC_EventTrigger_Format1_Item_H_


#include <asn_application.h>

/* Including external dependencies */
#include "RIC-EventTriggerCondition-ID.h"
#include "MessageType-Choice.h"
#include <NativeEnumerated.h>
#include "LogicalOR.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum E2SM_RC_EventTrigger_Format1_Item__messageDirection {
	E2SM_RC_EventTrigger_Format1_Item__messageDirection_incoming	= 0,
	E2SM_RC_EventTrigger_Format1_Item__messageDirection_outgoing	= 1
	/*
	 * Enumeration is extensible
	 */
} e_E2SM_RC_EventTrigger_Format1_Item__messageDirection;

/* Forward declarations */
struct EventTrigger_UE_Info;
struct EventTrigger_UEevent_Info;

/* E2SM-RC-EventTrigger-Format1-Item */
typedef struct E2SM_RC_EventTrigger_Format1_Item {
	RIC_EventTriggerCondition_ID_t	 ric_eventTriggerCondition_ID;
	MessageType_Choice_t	 messageType;
	long	*messageDirection;	/* OPTIONAL */
	struct EventTrigger_UE_Info	*associatedUEInfo;	/* OPTIONAL */
	struct EventTrigger_UEevent_Info	*associatedUEEvent;	/* OPTIONAL */
	LogicalOR_t	*logicalOR;	/* OPTIONAL */
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} E2SM_RC_EventTrigger_Format1_Item_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_messageDirection_4_rc_v1_03;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_E2SM_RC_EventTrigger_rc_v1_03_Format1_Item;
extern asn_SEQUENCE_specifics_t asn_SPC_E2SM_RC_EventTrigger_Format1_Item_specs_1_rc_v1_03;
extern asn_TYPE_member_t asn_MBR_E2SM_RC_EventTrigger_Format1_Item_1_rc_v1_03[6];

#ifdef __cplusplus
}
#endif

#endif	/* _E2SM_RC_EventTrigger_Format1_Item_H_ */
#include <asn_internal.h>
