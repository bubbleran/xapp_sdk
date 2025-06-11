/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef XAPP_SDK_DATA_MIR_H
#define XAPP_SDK_DATA_MIR_H 

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef enum{
  PDCP_SDU_VOLUME_DL,
  PDCP_SDU_VOLUME_UL,
  RLC_SDU_DELAY_DL,
  UE_THP_DL,
  UE_THP_UL,
  PRB_TOT_DL,
  PRB_TOT_UL,
  PDSCH_MCS,

  END_MNTR_VAR_E
} mntr_var_e;

typedef enum {
 PERIODICITY_1_MS,
 PERIODICITY_2_MS,
 PERIODICITY_5_MS,
 PERIODICITY_10_MS,
 PERIODICITY_20_MS,
 PERIODICITY_50_MS,
 PERIODICITY_100_MS,
 PERIODICITY_200_MS,
 PERIODICITY_500_MS,
 PERIODICITY_1000_MS,

 END_PERIODICITY_E,
} periodicity_e ;

typedef enum{
  BWP_USE_CASE_e,
  HAND_OVER_USE_CASE_e,
  MONITOR_USE_CASE_e,
  SLICE_USE_CASE_e,

  END_USE_CASE_e
} use_case_e;

typedef struct{
   uint32_t ric_req_id;
} stop_token_t;

typedef struct{
  uint32_t nb_id;
  uint32_t unused;
} e2ap_gnb_id_sdk_t;

typedef struct {
  uint16_t mcc;
  uint16_t mnc;
  uint8_t mnc_digit_len;
} e2ap_plmn_sdk_t;

typedef enum {
  e2ap_ngran_eNB_SDK       = 0,
  e2ap_ngran_ng_eNB_SDK    = 1,
  e2ap_ngran_gNB_SDK       = 2,
  e2ap_ngran_eNB_CU_SDK    = 3,
  e2ap_ngran_ng_eNB_CU_SDK = 4,
  e2ap_ngran_gNB_CU_SDK    = 5,
  e2ap_ngran_eNB_DU_SDK    = 6,
  e2ap_ngran_gNB_DU_SDK    = 7,
  e2ap_ngran_eNB_MBMS_STA_SDK  = 8,
  e2ap_ngran_gNB_CUCP_SDK  = 9,
  e2ap_ngran_gNB_CUUP_SDK  = 10,

  END_E2AP_NGRAN_NODE_TYPE_SDK
} e2ap_ngran_node_sdk_t;

typedef struct {
  e2ap_ngran_node_sdk_t type;
  e2ap_plmn_sdk_t plmn;
  e2ap_gnb_id_sdk_t nb_id;
  uint64_t *cu_du_id;
} global_e2_node_id_sdk_t;

typedef enum{
  GNB_UE_ID_E2SM_SDK,
	GNB_DU_UE_ID_E2SM_SDK,
	GNB_CU_UP_UE_ID_E2SM_SDK,
	NG_ENB_UE_ID_E2SM_SDK,
	NG_ENB_DU_UE_ID_E2SM_SDK,
	EN_GNB_UE_ID_E2SM_SDK,
  ENB_UE_ID_E2SM_SDK,

  END_UE_ID_E2SM_SDK
} ue_id_e2sm_sdk_e; 

typedef struct {
  uint16_t mcc;
  uint16_t mnc;
  uint8_t mnc_digit_len;
} e2sm_plmn_sdk_t;

typedef struct{
  // Mandatory
  // PLMN Identity 6.2.3.1
  e2sm_plmn_sdk_t plmn_id;

  // Mandatory
  // AMF Region ID BIT STRING (SIZE(8))
  // openair3/NGAP/ngap_gNB_defs.h
  uint8_t amf_region_id;

  // Mandatory
  //  AMF Set ID BIT STRING (SIZE(10))
  uint16_t amf_set_id:10;

  // Mandatory
  // AMF Pointer BIT STRING (SIZE(6))
  uint16_t amf_ptr:6;
} guami_sdk_t;

typedef enum {
    GNB_TYPE_ID_SDK,
    END_TYPE_ID_SDK
} gnb_type_id_sdk_e;

typedef struct {
    e2sm_plmn_sdk_t plmn_id;
    gnb_type_id_sdk_e type;
    //union {
       e2ap_gnb_id_sdk_t gnb_id; 
    //} u;
} global_gnb_id_sdk_t;

typedef enum {
    GNB_GLOBAL_TYPE_ID_SDK,
    NG_ENB_GLOBAL_TYPE_ID_SDK,

    END_GLOBAL_TYPE_ID_SDK
} ng_ran_node_type_id_sdk_e;

// 6.2.3.2 Global NG-RAN Node ID
typedef struct {
    ng_ran_node_type_id_sdk_e type;
    //union {
        global_gnb_id_sdk_t global_gnb_id;  // 6.2.3.3
        //global_ng_enb_id_t global_ng_enb_id;  // 6.2.3.8 
    //};
} global_ng_ran_node_id_sdk_t;

typedef struct{
  // 6.2.3.16
  // Mandatory
  // AMF UE NGAP ID
  // Defined in TS 38.413 [6] (NGAP) clause 9.3.3.1.
  // Defined in TS 38.401 [2].
  // fill with openair3/NGAP/ngap_gNB_ue_context.h:61
  uint64_t amf_ue_ngap_id; // [0, 2^40 ]

  // Mandatory
  // GUAMI 6.2.3.17 
  guami_sdk_t guami;

  // gNB-CU UE F1AP ID List
  // C-ifCUDUseparated 
  size_t gnb_cu_ue_f1ap_lst_len;  // [1,4]
  uint32_t *gnb_cu_ue_f1ap_lst;

  //gNB-CU-CP UE E1AP ID List
  //C-ifCPUPseparated 
  size_t gnb_cu_cp_ue_e1ap_lst_len;  // [1, 65535]
  uint32_t *gnb_cu_cp_ue_e1ap_lst;

  // RAN UE ID
  // Optional
  // 6.2.3.25
  // OCTET STRING (SIZE (8))
  // Defined in TS 38.473 (F1AP) 
  // clause 9.2.2.1
  // UE CONTEXT SETUP REQUEST
  uint64_t *ran_ue_id;

  // M-NG-RAN node UE XnAP ID
  // C- ifDCSetup
  // 6.2.3.19
  uint32_t *ng_ran_node_ue_xnap_id;

  // Global gNB ID
  // 6.2.3.3
  // Optional
  // This IE shall not be used. Global NG-RAN Node ID IE shall replace this IE 
   global_gnb_id_sdk_t *global_gnb_id;

  // Global NG-RAN Node ID
  // C-ifDCSetup
  // 6.2.3.2
  global_ng_ran_node_id_sdk_t *global_ng_ran_node_id;

} gnb_e2sm_sdk_t ;

typedef struct {
  uint32_t gnb_cu_ue_f1ap;  // 6.2.3.21
  uint64_t *ran_ue_id;  // 6.2.3.25, OPTIONAL
} gnb_du_e2sm_sdk_t;

typedef struct {
  uint32_t gnb_cu_cp_ue_e1ap;  // 6.2.3.20
  uint64_t *ran_ue_id;  // 6.2.3.25, OPTIONAL
} gnb_cu_up_e2sm_sdk_t;

typedef union {
    gnb_e2sm_sdk_t gnb;
    gnb_du_e2sm_sdk_t  gnb_du;
    gnb_cu_up_e2sm_sdk_t  gnb_cu_up;
    //ng_enb_e2sm_t ng_enb;
    //ng_enb_du_e2sm_t  ng_enb_du;
    //en_gnb_e2sm_t  en_gnb;
    //enb_e2sm_t enb;
} ue_id_e2sm_sdk_u;


typedef struct {
  ue_id_e2sm_sdk_e type;
  ue_id_e2sm_sdk_u u;
} ue_id_e2sm_sdk_t;

typedef enum {
	NR_RAT_TYPE_SDK,
	EUTRA_RAT_TYPE_SDK,

  END_CGI_RAT_TYPE_SDK
} rat_type_sdk_e; 

//  6.2.3.7  NR CGI
typedef struct{
  e2sm_plmn_sdk_t plmn_id;  // 6.2.3.1
  // Not using nr_cell_id:36 since bit fields are nto addressable, 
  // and thus, memcpy does not work   
  uint64_t nr_cell_id; // bit string of 36 bits
} nr_cgi_sdk_t;

// 6.2.2.5  Cell Global ID
typedef struct{
  // CHOICE RAT type
  // Mandatory
  rat_type_sdk_e type;

  //union{
    nr_cgi_sdk_t nr_cgi; // 6.2.3.7
  //  eutra_cgi_t eutra; // 6.2.3.11
  //};
} cell_global_id_sdk_t;


typedef struct{
  // HO
  uint16_t* target_pci;
  size_t* target_ssb_nr_arfcn;
  size_t sz_nghbr_cell;
} hand_over_info_t;

typedef struct{
  ue_id_e2sm_sdk_t ue;
  hand_over_info_t ho;
} ue_ho_info_t;

typedef struct {
  global_e2_node_id_sdk_t node;

  // UE + HO
  ue_ho_info_t* ue_ho;
  size_t sz_ue;

  // BWP
  cell_global_id_sdk_t* cell;
  size_t sz_cell;
} node_data_t;

void free_node_data(node_data_t* n);

void free_node_data_wrapper(void* v);

node_data_t cp_node_data(node_data_t const* src);


typedef struct{
 node_data_t* n;
 size_t sz;
} arr_node_data_t;

void free_arr_node_data(arr_node_data_t* arr);

void free_arr_node_data_wrapper(void* v);

typedef enum{
  DL_BWP_CONTEXT_SDK,
  UL_BWP_CONTEXT_SDK,
  SUL_BWP_CONTEXT_SDK,
  END_BWP_CONTEXT_SDK,
} bwp_context_sdk_e;

bool eq_global_e2_node_id_sdk(global_e2_node_id_sdk_t const* m0, global_e2_node_id_sdk_t const* m1);

global_e2_node_id_sdk_t cp_global_e2_node_id_sdk(void* src);

cell_global_id_sdk_t cp_cell_global_id_sdk(void* src);

ue_id_e2sm_sdk_t cp_ue_id_e2sm_sdk(void* src);

arr_node_data_t cp_seq_arr_arr_node_sdk(void* src);

int64_t time_now_us_sdk(void);

#ifdef __cplusplus
}
#endif

#endif
