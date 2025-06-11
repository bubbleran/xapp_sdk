/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#ifndef XAPP_SDK_FLEXRIC_MIR_H
#define XAPP_SDK_FLEXRIC_MIR_H 

#ifdef __cplusplus
extern "C" {
#endif

#include "xapp_sdk_data.h"

void init_xapp_sdk(int argc, char** argv);

arr_node_data_t node_data_xapp_sdk(use_case_e uc);

void stop_xapp_sdk();

/////
// Hand Over 
/////
void ho_xapp_sdk(global_e2_node_id_sdk_t const* n, ue_id_e2sm_sdk_t const* ue, int16_t target_pci, size_t target_ssb_nr_arfcn);

/////
// Bandwidth
/////
void bw_xapp_sdk(global_e2_node_id_sdk_t const* n, cell_global_id_sdk_t const* cell, uint32_t band, uint32_t new_bnd);

void bwp_xapp_sdk(global_e2_node_id_sdk_t const* n, cell_global_id_sdk_t const* cell, bwp_context_sdk_e bwp_context, uint32_t start_rb, uint32_t number_rb);

/////
// Monitoring 
/////
float e2_node_mntr_xapp_sdk(global_e2_node_id_sdk_t const* n, mntr_var_e var); 

stop_token_t e2_node_mntr_cb_xapp_sdk(global_e2_node_id_sdk_t const* n, mntr_var_e var, periodicity_e p, void (*fn_cb)(float val,uint32_t ric_req_id)); 

float ue_mntr_xapp_sdk(global_e2_node_id_sdk_t const* n, ue_id_e2sm_sdk_t const* ue, mntr_var_e var);

stop_token_t ue_mntr_cb_xapp_sdk(global_e2_node_id_sdk_t const* n, ue_id_e2sm_sdk_t const* ue, mntr_var_e var, periodicity_e p, void (*fn_cb)(float val,uint32_t ric_req_id)); 

void stop_cb_xapp_sdk(stop_token_t st);

/////
// Slice
/////
void slice_xapp_sdk(global_e2_node_id_sdk_t const* n, char const* sst, char const* sd, int dedicated_prb);

#ifdef __cplusplus
}
#endif

#endif

