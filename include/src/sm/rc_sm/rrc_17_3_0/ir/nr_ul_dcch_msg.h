#ifndef NR_UL_DCCH_MSG_MIR_H
#define NR_UL_DCCH_MSG_MIR_H 

#include "util/byte_array.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

// This file represents the skeleton to perform decode properly
// It was not finished, as we took the shortcut to provide a json
// to the xapp when decoding RRC messages. See   
 // void* nr_ul_dcch_msg_asn_to_json_sm_ric(uint8_t const* buf, size_t len); 
 // in rc_sm_ric.h

typedef enum{
  C1_NR_UL_DCCH_MSG_E,
  C2_NR_UL_DCCH_MSG_E,

  END_NR_UL_DCCH_MSG_E,
} nr_ul_dcch_msg_e;

typedef enum{
	MEASUREMENT_REPORT_NR_UL_DCCH_MSG_C1_E,
	RRC_RECONFIGURATION_COMPLETE_NR_UL_DCCH_MSG_C1_E,
	RRC_SETUP_COMPLETE_NR_UL_DCCH_MSG_C1_E,
	RRC_REESTABLISHMENT_COMPLETE_NR_UL_DCCH_MSG_C1_E,
	RRC_RESUME_COMPLETE_NR_UL_DCCH_MSG_C1_E,
	SECURITY_MODE_COMPLETE_NR_UL_DCCH_MSG_C1_E,
	SECURITY_MODE_FAILURE_NR_UL_DCCH_MSG_C1_E,
	UL_INFORMATION_TRANSFER_NR_UL_DCCH_MSG_C1_E,
	LOCATION_MEASUREMENT_INDICATION_NR_UL_DCCH_MSG_C1_E,
	UE_CAPABILITY_INFORMATION_NR_UL_DCCH_MSG_C1_E,
	COUNTER_CHECK_RESPONSE_NR_UL_DCCH_MSG_C1_E,
	UE_ASSISTANCE_INFORMATION_NR_UL_DCCH_MSG_C1_E,
	FAILURE_INFORMATION_NR_UL_DCCH_MSG_C1_E,
	UL_INFORMATION_TRANSFER_MR_DC_NR_UL_DCCH_MSG_C1_E,
	SCG_FAILURE_INFORMATION_NR_UL_DCCH_MSG_C1_E,
	SCG_FAILURE_INFORMATION_EUTRA_NR_UL_DCCH_MSG_C1_E,

	END_NR_UL_DCCH_MSG_C1_E
} nr_ul_dcch_msg_c1_e; 

//	RSRP_Range_t	*rsrp;	/* OPTIONAL */
//	RSRQ_Range_t	*rsrq;	/* OPTIONAL */
//	SINR_Range_t	*sinr;	/* OPTIONAL */
typedef struct{
	// [0-127]
	uint8_t* rsrp;
	// [0-127]
	uint8_t* rsrq;
	// [0-127]
	uint8_t* sinr;
} meas_quantity_results_t;

// typedef struct MeasQuantityResults cellResults 
typedef struct{
	meas_quantity_results_t* ssb_cell;	
	meas_quantity_results_t* csi_rs_cell;	
} cell_results_t;

// ResultsPerSSB_Index
typedef struct{
	// [0,63]
	uint8_t ssb_idx;
  meas_quantity_results_t* ssb_results;
} result_per_ssb_idx_t;

// ResultsPerCSI_RS_Index
typedef struct{
	// 0..maxNrofCSI-RS-ResourcesRRM-1 -> [0, 95]
	uint8_t csi_rs_idx;
	// Optional
  meas_quantity_results_t* csi_rs_results;
} results_per_csi_rs_idx_t;

// struct MeasResultNR__measResult__rsIndexResults
typedef struct{
	// ResultsPerSSB_Index
	size_t sz_result_per_ssb_idx;
	result_per_ssb_idx_t* result_per_ssb_idx; 

	size_t sz_results_per_csi_rs_idx;
 	results_per_csi_rs_idx_t results_per_csi_rs_idx;
} rs_idx_results_t;

// struct MeasResultNR__measResult 
typedef struct{
	cell_results_t cell_results;
	rs_idx_results_t* rs_idx_results;
} meas_result_t; 

// PLMN_Identity
typedef struct{
	// Optional. Zerp permited
	size_t sz_mcc;
  uint64_t* mcc; 	

	size_t sz_mnc;
  uint64_t* mnc; 	
} plmn_id_t;

typedef enum{
	RESERVED_CELL_RESERVED_FOR_OPERATOR_USE_E,
	UNRESERVED_CELL_RESERVED_FOR_OPERATOR_USE_E,
	END_CELL_RESERVED_FOR_OPERATOR_USE_E
} cell_reserved_for_operator_use_e;

typedef struct{
	// TrackingAreaCode_t
	// Size 24. First 8 bits must be zero
	size_t sz_tracking_area_code;
	uint32_t* tracking_area_code;
	// Optional
	// INTEGER [22..32]
	uint8_t* gNB_ID_Length_r17;
} plmn_id_info_ext2_t;

// PLMN_IdentityInfo
typedef struct{
	size_t sz_plmn_id;
	plmn_id_t* plmn_id;
	// Optional. size 24. The first 8 bits are always zero
	uint32_t* tac; 
	// [0-255]
	uint8_t* ranac; // RAN_AreaCode_t	*ranac;	/* OPTIONAL */
	// CellIdentity_t	 
	// Size 36 bits. First 24 bits are always zero
	uint64_t cell_id;
	cell_reserved_for_operator_use_e cell_reserved_for_operator_use;
	// Optional in ext1
	long	*iab_Support_r16;
	// Optional
 	plmn_id_info_ext2_t* ext2;
} plmn_id_info_t;

typedef struct{
	// [0,15]
	uint8_t ssb_subcarrier_offset;
	// PDCCH-config-SIB1
	// [0,15]
	uint8_t ctrl_resource_set_zero_pdcch_config_sib1;
	// [0,15]
	uint8_t search_space_zero_pdcch_config_sib1;
} no_sib1_t;

// struct CGI_InfoNR	*cgi_Info;	/* OPTIONAL */
typedef struct{
// struct PLMN_IdentityInfoList	*plmn_IdentityInfoList;	/* OPTIONAL */
	size_t sz_plmn_id_info; 
	plmn_id_info_t* plmn_id_info; 
	// FreqBandIndicatorNR_t
	size_t sz_freq_band_ind_nr;
	// [1,1024] pag. 799 
	uint16_t* freq_band_ind_nr;
	// Optional
	no_sib1_t* no_sib1;

	// Optional ext1
	//struct NPN_IdentityInfoList_r16	*npn_IdentityInfoList_r16;	/* OPTIONAL */
	void* npn_Id_Info_list_r16; // Not implemented
	// Optional ext2
	//*cellReservedForOtherUse_r16;	enumertaed, only TRUE valid/* OPTIONAL */
	bool* cell_reserved_for_other_use_r16; // Not implemented
} cgi_info_t;

// NR_RS_Type_t
typedef enum{
	SSB_NR_RS_TYPE_E,
	CSI_RS_NR_RS_TYPE_E,
	END_NR_RS_TYPE_E
} nr_rs_type_e; 

typedef enum {
	A3_COND_EVENT_COND_TRIGGER_CONFIG_R16_E,
	A5_COND_EVENT_COND_TRIGGER_CONFIG_R16_E,
	A4_COND_EVENT_COND_TRIGGER_CONFIG_R16_E,
	D1_COND_EVENT_COND_TRIGGER_CONFIG_R16_E,
	T1_COND_EVENT_COND_TRIGGER_CONFIG_R16_E,
	END_COND_TRIGGER_CONFIG_R16_E
} cond_trigger_config_r16_e;

typedef enum{
	RSRP_MEAS_TRIGGER_QUAN_OFFSET_E,
	RSRQ_MEAS_TRIGGER_QUAN_OFFSET_E,
	SINR_MEAS_TRIGGER_QUAN_OFFSET_E,
	END_MEAS_TRIGGER_QUAN_OFFSET_E
} meas_trigger_quan_offset_e;

typedef struct{
 meas_trigger_quan_offset_e type;
 union{
	// [-30, 30]
	int8_t rsrp;
	// [-30, 30]
	int8_t rsrq;
	// [-30, 30]
	int8_t sinr;
 };
} meas_trigger_quan_offset_t;

typedef struct{
	// [0, 127]
	uint8_t rsrp;
	// [0, 127]
	uint8_t rsrq;
	// [0, 127]
	uint8_t sinr;
} meas_trigger_quan_t;

typedef enum{
	ms0_time_to_trigger_e = 0,
	ms40_time_to_trigger_e,
	ms64_time_to_trigger_e,
	ms80_time_to_trigger_e,
	ms100_time_to_trigger_e,
	ms128_time_to_trigger_e,
	ms160_time_to_trigger_e,
	ms256_time_to_trigger_e,
	ms320_time_to_trigger_e,
	ms480_time_to_trigger_e,
	ms512_time_to_trigger_e,
	ms640_time_to_trigger_e,
	ms1024_time_to_trigger_e,
	ms1280_time_to_trigger_e,
	ms2560_time_to_trigger_e,
	ms5120_time_to_trigger_e,
	end_time_to_trigger_e
} time_to_trigger_e;

// struct CondTriggerConfig_r16__condEventId__condEventA3 {
typedef struct{
//	MeasTriggerQuantityOffset_t	 a3_Offset;
//	Hysteresis_t	 hysteresis;
//	TimeToTrigger_t	 timeToTrigger;

  meas_trigger_quan_offset_t a3_offset;
	// [0,30]
	uint8_t histeresis;
	time_to_trigger_e time_to_trigger;
} cond_event_a3_t;

typedef struct{
	// MeasTriggerQuantity_t	 
	// MeasTriggerQuantityOffset_t	 
	meas_trigger_quan_t threshold_1; 
	meas_trigger_quan_t threshold_2; 
	// [0,30]
	uint8_t histeresis;
	time_to_trigger_e time_to_trigger;
} cond_event_a5_t;

typedef struct{
	// MeasTriggerQuantity_t	 
	meas_trigger_quan_t threshold_1; 
	// [0,30]
	uint8_t histeresis;
	time_to_trigger_e time_to_trigger;
} cond_event_a4_t;

typedef struct{
	// [0,65525]
	// long	 distanceThreshFromReference1_r17;
	uint16_t dist_thresh_from_ref1_r17; 

	// [0,65525]
	// long	 distanceThreshFromReference2_r17;
	uint16_t dist_thresh_from_ref2_r17;

	// ReferenceLocation_r17_t referenceLocation1_r17;
	size_t sz_ref_loc_1;
	uint8_t* ref_loc_1;

	// ReferenceLocation_r17_t referenceLocation2_r17;
	size_t sz_ref_loc_2;
	uint8_t* ref_loc_2;

	// [0, 32768]
	// HysteresisLocation_r17_t	 hysteresisLocation_r17;
	uint16_t hysteresis_location;

	// TimeToTrigger_t	 timeToTrigger_r17;
	time_to_trigger_e time_to_trigger;
} cond_event_d1_t;

typedef struct{
	//[0,549755813887]
	uint64_t t1_threshold;
	// [1,6000]
	uint32_t duration;
} cond_event_t1_t;

// A_SEQUENCE_OF(struct CondTriggerConfig_r16) list;
typedef struct{
	nr_rs_type_e nr_rs_type;
  cond_trigger_config_r16_e type;
	union{
		cond_event_a3_t a3;
		cond_event_a5_t a5;
		cond_event_a4_t a4;
		cond_event_d1_t d1;
		cond_event_t1_t t1;
	};
} cond_trigger_config_r16_t;

// ENUMERATED {condFirstEvent, condSecondEvent} 
typedef enum{
	COND_FIRST_EVENT_FIRST_TRIGGER_EVENT_E, 
	COND_SECOND_EVENT_FIRST_TRIGGER_EVENT_E,
	END_FIRST_TRIGGER_EVENT_E,
} first_trigger_event_e;

//TimeBetweenEvent_r17_t	*timeBetweenEvents_r17;	/* OPTIONAL */
//long	*firstTriggeredEvent;	/* OPTIONAL */
typedef struct{
	//[0,1023]
	uint16_t* time_between_event;
	// Optional
	first_trigger_event_e* firstTriggeredEvent;
} triggered_Event_r17_t;

typedef struct{
	// ENUMERATED(true)
	bool* choCandidate_r17;	/* OPTIONAL */
	//struct CondTriggerConfig_r16)
	size_t sz_cond_trigger_config_r16;
	cond_trigger_config_r16_t* cond_trigger_config_r16;

	triggered_Event_r17_t* triggered_Event_r17;

} meas_result_nr_ext2_t;

// MeasResultNR	 
typedef struct{
	// Optional
	// [0..1007]
	uint16_t* phy_cell_id; 
	meas_result_t meas_result;
	// ext1. CGI_InfoNR Optional
	cgi_info_t* ext1; //cgi_info;
	// ext2. Optional
 	meas_result_nr_ext2_t* ext2;
} meas_result_nr_t;

typedef struct{
	size_t sz;
	meas_result_nr_t* elm; 
} meas_result_nr_list_t;

// MeasResults__measResultNeighCells_PR 
typedef enum {
	NR_MEAS_RESULT_NEIGH_CELLS_E ,
	EUTRA_MEAS_RESULT_NEIGH_CELLS_E ,
	UTRA_FDD_R16_MEAS_RESULT_NEIGH_CELLS_E ,
	CAND_REALY_R17_MEAS_RESULT_NEIGH_CELLS_E ,

	END_MEAS_RESULT_NEIGH_CELLS_E
} meas_result_neigh_cells_e;

typedef struct{
  meas_result_neigh_cells_e type;
	union{
		 meas_result_nr_list_t nr;
		 void* eutra;
		 void* utra_fdd_r16;
		 byte_array_t meas_result_cand_relay_r17; 
	};
} meas_result_neigh_cells_t;

// MeasResultServMO
typedef struct{
	// [0..maxNrofServingCells-1] -> [0,31]
	uint8_t serv_cell_id;
 	meas_result_nr_t meas_result_serving_cell;
	// Optional
	meas_result_nr_t* meas_result_best_neigh_cell;
} meas_result_serving_mo_t;

typedef struct{
	int dummy;
} meas_result_ext1_t;

typedef struct{
	int dummy;
}	meas_result_ext2_t;

typedef struct{
	int dummy;
}	meas_result_ext3_t;

typedef struct{
	int dummy;
} meas_result_ext4_t;

// measurementReport MeasurementReport -> MeasurementReport_IEs -> MeasResults_t  ,
typedef struct{
	// MeasResults_t 
	// [1 ,maxNrofMeasId] => [1,64] 
	uint8_t meas_id;

	//  MeasResultServMO 
	meas_result_serving_mo_t* meas_result_serv_mo;
	size_t sz_meas_result_serv_mo;

	// measResultNeighCells struct MeasResults__measResultNeighCells 
	meas_result_neigh_cells_t* meas_result_neigh_cells;

	// Not implemented
	meas_result_ext1_t* ext1;
	meas_result_ext2_t* ext2;
	meas_result_ext3_t* ext3;
	meas_result_ext4_t* ext4;

} measurement_report_rrc_t; 

// struct UplinkTxDirectCurrentBWP 
typedef struct{
	// INTEGER (0..maxNrofBWPs -> [0,4]  
	uint8_t bwp_id; 	
	bool shift_7_dot_5_khz;	
	// INTEGER (0..4095)
	uint16_t tx_direct_current_loc;
} uplink_tx_direct_current_bwp_t;

typedef struct{
	size_t sz;
	 uplink_tx_direct_current_bwp_t* elm;
} uplink_tx_direct_current_bwp_list_t;


typedef struct{
	// INTEGER (0..maxNrofServingCells-1) -> [0, 31] 
	uint8_t serv_cell_idx;
	uplink_tx_direct_current_bwp_list_t uplink_tx_direct_current_bwp_list;	

	uplink_tx_direct_current_bwp_list_t* ext1;

} uplink_tx_direct_current_cell_t;

typedef struct{
	size_t sz;
  uplink_tx_direct_current_cell_t* elm;
} uplink_tx_direct_current_list_t;

typedef enum{
	NR_SCG_RESPONSE_E,
	EUTRA_SCG_RESPONSE_E,
	END_SCG_RESPONSE_E ,
} scg_response_e;

typedef struct{
  scg_response_e type;
	union{
		byte_array_t nr;
		byte_array_t eutra;
	};
} scg_response_t;

//struct RRCReconfigurationComplete_v1610_IEs	*nonCriticalExtension;	/* OPTIONAL */
typedef struct{
	int dummy;	
}	rrc_reconfiguration_complete_v1610_ie_t; 

// struct RRCReconfigurationComplete_v1560_IEs	
typedef struct{
 scg_response_t* scg_response;
	//struct RRCReconfigurationComplete_v1610_IEs	*nonCriticalExtension;	/* OPTIONAL */
	rrc_reconfiguration_complete_v1610_ie_t* rrc_reconf; 
} rrc_reconf_complete_v1560_ie_t;

typedef struct{
	// struct UplinkTxDirectCurrentList	*uplinkTxDirectCurrentList;	/* OPTIONAL */
	uplink_tx_direct_current_list_t* uplink_tx_direct_current_list;	

	// struct RRCReconfigurationComplete_v1560_IEs	
	rrc_reconf_complete_v1560_ie_t* non_crit_ext;  	
} rrc_reconf_complete_v1530_t;

// struct RRCReconfigurationComplete_IEs
typedef struct{
	byte_array_t* late_non_crit_ext;
	rrc_reconf_complete_v1530_t* non_crit_ext;
} rrc_reconfiguation_complete_t;

// struct RRCReconfigurationComplete 
typedef struct{
	// RRC_TransactionIdentifier_t [0,3]	 
	uint8_t rrc_transaction_id;
	rrc_reconfiguation_complete_t* rrc_reconfiguation_complete;
} rrc_reconfiguration_complete_rrc_t; 

// struct RegisteredAMF 
typedef struct{
	// struct PLMN_Identity	
	plmn_id_t* plmn_id;	
	// AMF_Identifier_t	  
	// BIT STRING (SIZE (24)). First 8 must be zero
	uint32_t amf_identifier;
} registered_amf_t;

typedef enum{
	SST_NSSAI_E,
	SST_SD_NSSAI_E,
	END_NSSAI_E,
} nssai_e;
// struct S_NSSAI
typedef struct{
 nssai_e type;
	union{
	//sst BIT STRING (SIZE (8)),
	uint8_t sst;
	//sst-SD BIT STRING (SIZE (32))
	uint32_t sst_sd;
	};
} nssai_t;

typedef struct{
	size_t sz;
	nssai_t* elm;
}	nssai_list_t;

typedef enum{
	TMSI_VALUE_NG_5G_S_TMSI_VALUE_E,
	TMSI_VALUE_PART2_NG_5G_S_TMSI_VALUE_E,
	END_NG_5G_S_TMSI_VALUE_E
} ng_5g_s_tmsi_value_e;

// struct RRCSetupComplete_IEs__ng_5G_S_TMSI_Value 
typedef struct{
 	ng_5g_s_tmsi_value_e type;
	union{
		// BIT STRING (SIZE (48))	
		uint64_t tmsi;	
		// BIT STRING (SIZE (9)) 
		uint16_t part2;	
	};
} ng_5g_s_tmsi_value_t;

//ue-MeasurementsAvailable-r16 UE-MeasurementsAvailable-r16 OPTIONAL,
typedef struct{
//logMeasAvailable-r16 ENUMERATED {true} OPTIONAL,
//logMeasAvailableBT-r16 ENUMERATED {true} OPTIONAL,
//logMeasAvailableWLAN-r16 ENUMERATED {true} OPTIONAL,
//connEstFailInfoAvailable-r16 ENUMERATED {true} OPTIONAL,
//rlf-InfoAvailable-r16 ENUMERATED {true} OPTIONAL
	bool* log_meas_available_r16;	/* OPTIONAL */
	bool* log_meas_available_bt_r16;	/* OPTIONAL */
	bool* log_meas_availble_wlan_r16;	/* OPTIONAL */
	bool* conn_ext_fail_info_available_r16;	/* OPTIONAL */
	bool* rlf_info_available_t16;	/* OPTIONAL */

	//ENUMERATED {true} 
	bool* success_HO_Info_Available_r17;	/* OPTIONAL */
	bool* sig_log_meas_config_available_r17; 

}	ue_measure_available_r16_t;

// struct RRCSetupComplete_v1700_IEs
typedef struct{
	int dummy;
}	rrc_setup_complete_v1700_ie_t;

// struct RRCSetupComplete_v1690_IEs
typedef struct{
	// ENUMERATED {true}
	bool* ul_rrc_segmentation_r16;

	// struct RRCSetupComplete_v1700_IEs	
	rrc_setup_complete_v1700_ie_t* non_crit_ext;
}	rrc_setup_complete_v1690_ie_t;

// struct RRCSetupComplete_v1610_IEs	*
typedef struct{
//iab-NodeIndication-r16 ENUMERATED {true} OPTIONAL,
	bool* iab_node_indication_r16;
//	idleMeasAvailable-r16 ENUMERATED {true} OPTIONAL,
	bool* idle_meas_available_r_16;
	//ue-MeasurementsAvailable-r16 UE-MeasurementsAvailable-r16 OPTIONAL,
	ue_measure_available_r16_t* ue_measure_available_r16;
	//mobilityHistoryAvail-r16 ENUMERATED {true} OPTIONAL,
	bool* mobility_history_avail_r16;

	//mobilityState-r16 ENUMERATED {normal, medium, high, spare} OPTIONAL,
	uint8_t* mobility_state_r16; 

	// struct RRCSetupComplete_v1690_IEs	*
	rrc_setup_complete_v1690_ie_t* non_crit_ext;

} rrc_setup_complete_v1610_t;

// struct RRCSetupComplete_IEs	*rrcSetupComplete;
typedef struct{
	//long selectedPLMN_Identity;
	// selectedPLMN-Identity INTEGER (1..maxPLMN) -> [1,12]	
	uint8_t selected_plmn_identity;
	registered_amf_t* registered_amf;
	// long	*guami_Type;	/* OPTIONAL */
	// guami-Type ENUMERATED {native, mapped}
	uint8_t* guami_type;

	nssai_list_t* nssai_list;

	// DedicatedNAS_Message_t	 
	byte_array_t dedicated_nas_msg;

	ng_5g_s_tmsi_value_t* ng_5g_s_tmsi_value;

	// Optional
	byte_array_t* late_non_critical_ext; 

	//struct RRCSetupComplete_v1610_IEs	*nonCriticalExtension;	/* OPTIONAL */
	rrc_setup_complete_v1610_t* non_crit_ext;	

}	rrc_setup_complete_ie_t ;

// typedef struct RRCSetupComplete 
typedef struct{
	// RRC_TransactionIdentifier_t [0,3]	 
	uint8_t rrc_transaction_id;
	rrc_setup_complete_ie_t rrc_setup_complete;
} rrc_setup_complete_rrc_t; 

// struct RRCReestablishmentComplete_v1610_IEs	
typedef struct{
	// struct UE_MeasurementsAvailable_r16	
	ue_measure_available_r16_t* ue_measure_available_r16; 
}	rrc_establisment_complete_v1610_ie_t;

// struct RRCReestablishmentComplete_IEs	*
typedef struct{
	// Optional
	byte_array_t* late_non_crit_ext;
	//struct RRCReestablishmentComplete_v1610_IEs	*nonCriticalExtension;	/* OPTIONAL */
	rrc_establisment_complete_v1610_ie_t* non_crit_ext;
}	rrc_reestablisment_complete_ie_t;

// struct RRCReestablishmentComplete
typedef struct{
	// RRC_TransactionIdentifier_t [0,3]	 
	uint8_t rrc_transaction_id;
	//struct RRCReestablishmentComplete_IEs	*rrcReestablishmentComplete;
	rrc_reestablisment_complete_ie_t* rrc_reestablishment_complete;
} rrc_reestablishment_complete_rrc_t; 

// struct MeasResultIdleEUTRA_r16	*
typedef struct{
	int dummy;
} meas_result_idle_eutra_r16_t;

// ResultsPerSSB-IndexIdle-r16
typedef struct{
// INTEGER (0..maxNrofSSBs-1)
// [0, 63]
	//SSB_Index_t	 ssb_Index_r16;
	uint8_t ssb_idx_r16;
	//RSRP_Range_t	*ssb_RSRP_Result_r16;	/* OPTIONAL */
	// [0,127] 
	uint8_t* rsrp; 
	uint8_t* rsrq;
}	result_per_ssb_idx_r16_t ;

typedef struct{
	size_t sz;
	result_per_ssb_idx_r16_t* elm; 
}	result_per_ssb_idx_list_r16_t; 

// struct MeasResultsPerCellIdleNR_r16
typedef struct{
	// PhysCellId_t	 physCellId_r16;
	// [0..1007]
	uint16_t phy_cell_id; 
	
	//RSRP_Range_t	*ssb_RSRP_Result_r16;	/* OPTIONAL */
	// [0,127] 
	uint8_t* rsrp; 
	uint8_t* rsrq;

	// Optional
	result_per_ssb_idx_list_r16_t* results_ssb_idx_r16; 

}  meas_result_per_cell_idle_nr_r16_t;

typedef struct{
	size_t sz;
  meas_result_per_cell_idle_nr_r16_t* elm;
} meas_result_per_cell_list_idle_nr_r16_t;

//typedef struct MeasResultsPerCarrierIdleNR_r16 {
typedef struct{
	// ARFCN-ValueNR ::= INTEGER (0..maxNARFCN)
	// [0, 3279165]
	 uint32_t carrierFreq_r16;
	 meas_result_per_cell_list_idle_nr_r16_t meas_result_per_cell_list_idle_nr_r16;

} meas_result_per_carrier_idle_nr_r16_t;

	// struct MeasResultIdleNR_r16__measResultsPerCarrierListIdleNR_r16
typedef struct{
	size_t sz;
	meas_result_per_carrier_idle_nr_r16_t* elm;
}	meas_result_per_carrier_idle_nr_r16_list_t;

// struct MeasResultIdleNR_r16	
typedef struct{
	// [0-127]
	uint8_t* rsrp;
	// [0-127]
	uint8_t* rsrq;
	// Optional
	// struct ResultsPerSSB_IndexList_r16	*resultsSSB_Indexes_r16;	/* OPTIONAL */
	result_per_ssb_idx_list_r16_t*  result_per_ssb_idx_list; 
	// struct MeasResultIdleNR_r16__measResultsPerCarrierListIdleNR_r16
	meas_result_per_carrier_idle_nr_r16_list_t* meas_result_per_carrier_idle_nr_r16_list;
}	meas_result_idle_nr_r16_t;

typedef enum{
	NR_SCG_RESPONSE_R16_E,
	EUTRA_SCG_RESPONSE_R16_E,
	END_SCG_RESPONSE_R16_E,
}	scg_response_r16_e;

// 	struct RRCResumeComplete_v1610_IEs__scg_Response_r16 {
typedef struct{
	scg_response_r16_e type;
	union{
		byte_array_t nr;
		byte_array_t eutra;
	};
}	scg_response_r16_t;

// struct NeedForGapsInfoNR_r16	*needForGapsInfoNR_r16;	/* OPTIONAL */
typedef struct{
	int dummy;
} need_for_gaps_info_nr_r16_t;

//struct RRCResumeComplete_v1640_IEs	*nonCriticalExtension;	/* OPTIONAL */
typedef struct{
	int dummy;
} rrc_resume_complete_v1640_ie_t;

// struct RRCResumeComplete_v1610_IEs
typedef struct{
	//	idleMeasAvailable-r16 ENUMERATED {true} OPTIONAL,
	bool* idle_meas_available_r16;
	// Optional
	meas_result_idle_eutra_r16_t*  meas_result_idle_eutra_r16;
	// Optional struct MeasResultIdleNR_r16	
	meas_result_idle_nr_r16_t* meas_result_idle_nr_r16;
	// Optional
	scg_response_r16_t* scg_response_r16;

	// 	struct UE_MeasurementsAvailable_r16	*ue_MeasurementsAvailable_r16;	/* OPTIONAL */
	ue_measure_available_r16_t* ue_measure_available_r16; 
	// mobilityHistoryAvail-r16 ENUMERATED {true} 
	bool* mobilityHistoryAvail_r16;	/* OPTIONAL */
	// ENUMERATED {normal, medium, high, spare}
	uint8_t* mobilityState_r16;	/* OPTIONAL */

	// Optional
	need_for_gaps_info_nr_r16_t* need_for_gaps_info_nr_r16;

	rrc_resume_complete_v1640_ie_t* non_crit_ext; 

}	rrc_resume_complete_v1610_ie_t;

//typedef struct RRCResumeComplete_IEs {
typedef struct{
	// Optional DedicatedNAS_Message_t	 
	byte_array_t* dedicated_nas_msg;
	//long selectedPLMN_Identity;
	// selectedPLMN-Identity INTEGER (1..maxPLMN) -> [1,12]	
	uint8_t* selected_plmn_identity;
	// struct UplinkTxDirectCurrentList	*uplinkTxDirectCurrentList;	/* OPTIONAL */
	uplink_tx_direct_current_list_t* uplink_tx_direct_current_list;	

	byte_array_t* late_non_crit_ext;

	//struct RRCResumeComplete_v1610_IEs	*nonCriticalExtension;	/* OPTIONAL */
	rrc_resume_complete_v1610_ie_t* non_crit_ext;

}	rrc_resume_complete_ie_t;

// typedef struct RRCResumeComplete 
typedef struct{
	// RRC_TransactionIdentifier_t [0,3]	 
	uint8_t rrc_transaction_id;
	// struct RRCResumeComplete_IEs	*rrcResumeComplete;
	rrc_resume_complete_ie_t* rrc_resume_complete;
} rrc_resume_complete_rrc_t; 

// struct SecurityModeComplete	*securityModeComplete;
typedef struct{
	// RRC_TransactionIdentifier_t [0,3]	 
	uint8_t rrc_transaction_id;
	//typedef struct SecurityModeComplete_IEs {
	// Optional
	byte_array_t* late_non_crit_ext; 
} security_mode_complete_rrc_t ; 

// struct SecurityModeFailure	*securityModeFailure;
typedef struct{
	// RRC_TransactionIdentifier_t [0,3]	 
	uint8_t rrc_transaction_id;
	//typedef struct SecurityModeFailure_IEs {
	// Optional
	byte_array_t* late_non_crit_ext; 
} security_mode_failure_rrc_t; 

typedef struct{
	// RRC_TransactionIdentifier_t [0,3]	 
	uint8_t rrc_transaction_id;
	// typedef struct ULInformationTransfer_IEs {
	// DedicatedNAS_Message_t	*dedicatedNAS_Message;	/* OPTIONAL */
	byte_array_t* dedicated_nas_msg;
	byte_array_t* late_non_crit_ext; 

	//struct ULInformationTransfer_v1700_IEs	*nonCriticalExtension;	/* OPTIONAL */
	// DedicatedInfoF1c_r17_t	*dedicatedInfoF1c_r17;	/* OPTIONAL */
	byte_array_t* dedicated_info_f1c_r17;
} ul_information_transfer_rrc_t ; 

typedef enum{
	RELEASE_SETUP_RELEASE_LOC_MEAS_INFO_E ,
	SETUP_SETUP_RELEASE_LOC_MEAS_INFO_E ,
	END_SETUP_RELEASE_LOC_MEAS_INFO_E 
} setup_release_loc_meas_info_e ;

//struct LocationMeasurementInfo	*setup;
typedef struct{
	int dummy;
} loc_meas_info_t;

// 	SetupRelease_LocationMeasurementInfo_t	 measurementIndication;
typedef struct{
	 setup_release_loc_meas_info_e type;
		union{
			// Release has NULL type
			void* release;
			loc_meas_info_t* setup;
		};
} setup_release_loc_meas_info_t;

// typedef struct LocationMeasurementIndication {
typedef struct{
	setup_release_loc_meas_info_t measurementIndication;
	byte_array_t* late_non_crit_ext;
} location_measurement_indication_rrc_t ; 

// struct UE_CapabilityRAT_Container
typedef struct {
	//RAT_Type_t	 rat_Type;
	// ENUMERATED {nr, eutra-nr, eutra, utra-fdd-v1610,
	uint8_t rat_type;		
	//
	byte_array_t ue_cap_rat_container;
} ue_cap_rat_container_t;

typedef struct{
	size_t sz;
  ue_cap_rat_container_t* elm;
} ue_cap_rat_container_list_t;


// struct UECapabilityInformation__criticalExtensions {
typedef struct{
	// RRC_TransactionIdentifier_t [0,3]	 
	uint8_t rrc_transaction_id;
// typedef struct UECapabilityInformation_IEs {
	// Optional 
//	struct UE_CapabilityRAT_ContainerList	*ue_CapabilityRAT_ContainerList;	/* OPTIONAL */
		ue_cap_rat_container_list_t* ue_cap_rat_container_list;
	// Optional
	byte_array_t* late_non_crit_ext;
} ue_capability_information_rrc_t; 

//typedef struct DRB_CountInfo {
typedef struct{
	// INTEGER (1..32)
	// [1,32]
	uint8_t drb_id;
	// [0,4294967295]
	uint32_t cnt_uplink;
	uint32_t cnt_downlink;

} drb_count_info_t;

//typedef struct CounterCheckResponse {
typedef struct{
	// RRC_TransactionIdentifier_t [0,3]	 
	uint8_t rrc_transaction_id;
// struct CounterCheckResponse_IEs	*counterCheckResponse;

// DRB_CountInfoList_t	 drb_CountInfoList;
//	A_SEQUENCE_OF(struct DRB_CountInfo) list;
	// [0, 29]
	size_t sz_drb_count_info;
	drb_count_info_t* drb_count_info;

	byte_array_t* late_non_crit_ext;
	//OCTET_STRING_t	*lateNonCriticalExtension;	/* OPTIONAL */
} counter_check_response_rrc_t; 

typedef struct {
	int dummy;
} ue_assistance_information_v1540_ie_t;

// typedef struct DelayBudgetReport {
typedef enum{
	MINUS_1280_MS_DELAY_BUGGET_REPORT_E,
	MINUS_640_MS_DELAY_BUGGET_REPORT_E,
	MINUS_320_MS_DELAY_BUGGET_REPORT_E,
	MINUS_160_MS_DELAY_BUGGET_REPORT_E,
	MINUS_80_MS_DELAY_BUGGET_REPORT_E,
	MINUS_60_MS_DELAY_BUGGET_REPORT_E,
	MINUS_40_MS_DELAY_BUGGET_REPORT_E,
	MINUS_20_MS_DELAY_BUGGET_REPORT_E,
	PLUS_0_MS_DELAY_BUGGET_REPORT_E,
	PLUS_20_MS_DELAY_BUGGET_REPORT_E,
	PLUS_40_MS_DELAY_BUGGET_REPORT_E,
	PLUS_60_MS_DELAY_BUGGET_REPORT_E,
	PLUS_80_MS_DELAY_BUGGET_REPORT_E,
	PLUS_160_MS_DELAY_BUGGET_REPORT_E,
	PLUS_320_MS_DELAY_BUGGET_REPORT_E,
	PLUS_640_MS_DELAY_BUGGET_REPORT_E,
	PLUS_1280_MS_DELAY_BUGGET_REPORT_E,
	END_DELAY_BUGGET_REPORT_E
} delay_bugget_report_e;

// typedef struct UEAssistanceInformation {
typedef struct{
// typedef struct UEAssistanceInformation_IEs {
	//Optional
	delay_bugget_report_e* delay_budget_report; 
	// Optional
	byte_array_t* late_non_crit_ext;
	// Optional
	//struct UEAssistanceInformation_v1540_IEs	*nonCriticalExtension;	/* OPTIONAL */
	ue_assistance_information_v1540_ie_t* non_crit_ext;
} ue_assistance_information_rrc_t; 

//	struct FailureInformation_v1610_IEs	*nonCriticalExtension;	/* OPTIONAL */
typedef struct{
	int dummy;
} failure_information_v1610_ie_t;

//typedef enum FailureInfoRLC_Bearer__failureType {
typedef enum{
	SPARE3_FAILURE_TYPE_E,
	SPARE2_FAILURE_TYPE_E,
	SPARE1_FAILURE_TYPE_E,
	END_FAILURE_TYPE_E
} failure_type_e;

//	struct FailureInfoRLC_Bearer	*failureInfoRLC_Bearer;	/* OPTIONAL */
typedef struct{
	//CellGroupId_t	 cellGroupId;
	//INTEGER (0.. maxSecondaryCellGroups) 
	//[0,3]
	uint8_t cell_group_id;
	// INTEGER (1..maxLC-ID)
	//LogicalChannelIdentity_t	 logicalChannelIdentity;
	// [1,32]
	uint8_t logical_channel_id;	
	failure_type_e failure_type;
}	failure_info_rlc_bearer_t; 

// struct FailureInformation_IEs	*failureInformation;
typedef struct{
	// struct FailureInfoRLC_Bearer	*failureInfoRLC_Bearer;	/* OPTIONAL */
	// Optional
	failure_info_rlc_bearer_t* failure_info_rlc_bearer; 

	// Optional
	byte_array_t* late_non_crit_ext; 
	failure_information_v1610_ie_t* non_crit_ext;

} failure_information_rrc_t; 

//typedef enum ULInformationTransferMRDC__criticalExtensions__c1_PR {
typedef enum{
	UL_INFORMATION_TRANSFER_MR_DC_UL_INFORMATION_TRANSFER_MR_DC_RRC_E ,
	SPARE3_UL_INFORMATION_TRANSFER_MR_DC_RRC_E,
	SPARE2_UL_INFORMATION_TRANSFER_MR_DC_RRC_E,
	SPARE1_UL_INFORMATION_TRANSFER_MR_DC_RRC_E,
	END_UL_INFORMATION_TRANSFER_MR_DC_RRC_E
} ul_information_transfer_mr_dc_rrc_e;

// ULInformationTransferMRDC_IEs	
typedef struct{
//	OCTET_STRING_t	*ul_DCCH_MessageNR;	/* OPTIONAL */
//	OCTET_STRING_t	*ul_DCCH_MessageEUTRA;	/* OPTIONAL */
//	OCTET_STRING_t	*lateNonCriticalExtension;	/* OPTIONAL */
	byte_array_t* ul_dcch_msg_nr;
	byte_array_t* ul_dcch_msg_eutra;
	byte_array_t* late_non_crit_ext;
}	ul_information_transfer_mr_dc_ie_t ;

// typedef struct ULInformationTransferMRDC {
typedef struct{
 ul_information_transfer_mr_dc_rrc_e type;
	union{
		ul_information_transfer_mr_dc_ie_t  ul_information_transfer_mr_dc_ie;   
		// NULL type
		void* spare3;
		void* spare2;
		void* spare1;
	};
} ul_information_transfer_mr_dc_rrc_t; 

typedef struct{
	int dummy;
} scg_failure_info_v1590_ie_t;

typedef enum{
	T310_EXPIRY_FAILURE_REPORT_SCG_E,
	RANDOM_ACCESS_PROBLEM_FAILURE_REPORT_SCG_E,
	RLC_MAX_NUM_RETX_FAILURE_REPORT_SCG_E,
	SYNCH_RECONFIG_FAILURE_SCG_FAILURE_REPORT_SCG_E,
	SCG_RECONFIG_FAILURE_FAILURE_REPORT_SCG_E,
	SRB3_INTEGRITY_FAILURE_FAILURE_REPORT_SCG_E,
	OTHER_R16_FAILURE_REPORT_SCG_E,
	SPARE1_FAILURE_REPORT_SCG_E,
	END_FAILURE_REPORT_SCG_E,
} failure_report_scg_e;

// typedef struct MeasResult2NR 
typedef struct{
	// ARFCN-ValueNR INTEGER (0..maxNARFCN)
	// [0, 3279165]
	uint32_t* ssb_freq;
	uint32_t* ref_freq_csi_rs;

	//struct MeasResultNR	*measResultServingCell;	/* OPTIONAL */
	meas_result_nr_t* meas_result_serving_cell;

	//struct MeasResultListNR	*measResultNeighCellListNR;	/* OPTIONAL */
	size_t sz_meas_result_neigh_cell_list_nr;
	meas_result_nr_t* meas_result_neigh_cell_list_nr;
} meas_result2_nr_t;

typedef struct{
	size_t sz;
	meas_result2_nr_t* elm;
} meas_result_freq_list_t;

// typedef struct FailureReportSCG {
typedef struct{
 	failure_report_scg_e failure_type;
	// Optional. typedef struct MeasResultFreqList {
	meas_result_freq_list_t* meas_result_freq_list;

	// Optional
	byte_array_t* meas_result_scg_failure;

} failure_report_scg_t;

// typedef struct SCGFailureInformation {
// struct SCGFailureInformation_IEs	*scgFailureInformation;
typedef struct{
	// Optional	
	failure_report_scg_t*	failure_report_scg;
	// Optional
	scg_failure_info_v1590_ie_t* non_crit_ext;
} scg_failure_information_rrc_t; 

typedef struct{
	int dummy;
} scg_failure_information_eutra_v1590_ie_t;

// typedef enum FailureReportSCG_EUTRA__failureType {
typedef enum{
	T313_EXPIRY_FAILURE_REPORT_SCG_EUTRA_E,
	RANDOM_ACCESS_PROBLEM_FAILURE_REPORT_SCG_EUTRA_E, 
	RLC_MAX_NUM_RETX_FAILURE_REPORT_SCG_EUTRA_E, 
	SCG_CHANGE_FAILURE_FAILURE_REPORT_SCG_EUTRA_E, 
	SPARE4_FAILURE_REPORT_SCG_EUTRA_E, 
	SPARE3_FAILURE_REPORT_SCG_EUTRA_E, 
	SPARE2_FAILURE_REPORT_SCG_EUTRA_E, 
	SPARE1_FAILURE_REPORT_SCG_EUTRA_E,
	END_FAILURE_REPORT_SCG_EUTRA_E
} failure_report_scg_eutra_e;

typedef struct{
	int dummy;
} meas_result_freq_list_fail_mr_dc_t;

typedef struct{
 	failure_report_scg_eutra_e failure_type;
	//struct MeasResultFreqListFailMRDC	*measResultFreqListMRDC;	/* OPTIONAL */
	meas_result_freq_list_fail_mr_dc_t* meas_result_freq_list_fail_mr_dc;
	//OCTET_STRING_t	*measResultSCG_FailureMRDC;	/* OPTIONAL */
 	byte_array_t* meas_result_scg_failure_mr_dc;
} failure_report_scg_eutra_t;

//typedef struct SCGFailureInformationEUTRA {
typedef struct{
// struct SCGFailureInformationEUTRA_IEs	*scgFailureInformationEUTRA;
//	struct FailureReportSCG_EUTRA	*failureReportSCG_EUTRA;	/* OPTIONAL */
	failure_report_scg_eutra_t* failure_report_scg_eutra;
	//	struct SCGFailureInformationEUTRA_v1590_IEs	*nonCriticalExtension;	/* OPTIONAL */
	scg_failure_information_eutra_v1590_ie_t* non_crit_ext;	
} scg_failure_information_eutra_rrc_t ; 

// struct UL_DCCH_MessageType__c1 {
typedef struct{
  nr_ul_dcch_msg_c1_e type;
  union{
 	measurement_report_rrc_t meas_report; 
 	rrc_reconfiguration_complete_rrc_t rrc_reconf_compl; 
 	rrc_setup_complete_rrc_t rrc_setup_compl; 
	rrc_reestablishment_complete_rrc_t rrc_reestabl_compl; 
 	rrc_resume_complete_rrc_t rrc_resume_compl; 
	security_mode_complete_rrc_t secur_mode_compl; 
 	security_mode_failure_rrc_t secur_mode_fail; 
	ul_information_transfer_rrc_t ul_info_trans; 
	location_measurement_indication_rrc_t loc_measure_ind; 
  ue_capability_information_rrc_t ue_cap_info; 
 	counter_check_response_rrc_t counter_chck_repon; 
 	ue_assistance_information_rrc_t ue_assis_info; 
 	failure_information_rrc_t fail_info; 
 	ul_information_transfer_mr_dc_rrc_t ul_info_trans_mr_dc; 
 	scg_failure_information_rrc_t scg_fail_info; 
 	scg_failure_information_eutra_rrc_t scg_fail_info_eutra; 
  };
} nr_ul_dcch_msg_c1_t;

typedef struct{
	int dummy;
} nr_ul_dcch_msg_c2_t;

// UL_DCCH_MessageType_t	 message;
typedef struct{
  nr_ul_dcch_msg_e type;
  union {
   nr_ul_dcch_msg_c1_t c1;
   nr_ul_dcch_msg_c2_t c2;
  };
} nr_ul_dcch_msg_t;

#endif
