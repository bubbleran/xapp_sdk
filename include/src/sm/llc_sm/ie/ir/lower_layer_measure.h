#ifndef E2SM_LLC_LOWER_LAYER_MEASUREMENT_TYPE_MIR_H
#define E2SM_LLC_LOWER_LAYER_MEASUREMENT_TYPE_MIR_H 

// 8.3.16
typedef enum {
  DL_RLC_BUFFER_STATUS_LLM_E,
  DL_PDCP_Buffer_Status_LLM_E,
  DL_HARQ_Statistics_LLM_E,
  SLOT_TIME_STAMP_LLM_E,
  END_LLM_E,
} lower_layer_measure_e;

#endif
