#ifndef RRC_MSG_ID_E2SM_H
#define RRC_MSG_ID_E2SM_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

typedef enum{
  LTE_RRC_MESSAGE_ID,
  NR_RRC_MESSAGE_ID,

  END_RRC_MESSAGE_ID,
} rrc_message_id_e;

typedef enum{
  BCCH_BCH_LTE_RRC_CLASS, 
  BCCH_BCH_MBMS_LTE_RRC_CLASS,
  BCCH_DL_SCH_LTE_RRC_CLASS,
  BCCH_DL_SCH_BR_LTE_RRC_CLASS, 
  BCCH_DL_SCH_MBMS_LTE_RRC_CLASS, 
  MCCH_LTE_RRC_CLASS,

  PCCH_LTE_RRC_CLASS,
  DL_CCCH_LTE_RRC_CLASS,
  DL_DCCH_LTE_RRC_CLASS, 
  UL_CCCH_LTE_RRC_CLASS, 
  UL_DCCH_LTE_RRC_CLASS, 
  SC_MCCH_LTE_RRC_CLASS, 

  END_LTE_RRC_CLASS

} lte_rrc_class_e;

typedef enum{
  BCCH_BCH_NR_RRC_CLASS, 
  BCCH_DL_SCH_NR_RRC_CLASS, 
  DL_CCCH_NR_RRC_CLASS, 
  DL_DCCH_NR_RRC_CLASS, 
  PCCH_NR_RRC_CLASS,
  UL_CCCH_NR_RRC_CLASS,
  UL_CCCH1_NR_RRC_CLASS,
  UL_DCCH_NR_RRC_CLASS,

  END_NR_RRC_CLASS

} nr_rrc_class_e; 




// 6.2.2.13 E2 SM
// 9.3.35 E2 RC

typedef struct{
  // Mandatory
  rrc_message_id_e type;
  union{
    lte_rrc_class_e lte;
    nr_rrc_class_e nr;
  };

  // Mandatory
  // Integer
  // Number starts from 0 from the first
  // entry of a given RRC message class
  // defined in TS 36.331 [14] or TS
  // 38.331 [15].
  // My interpretation is that they start
  // from BCCH-BCH-Message, DL-CCCH-Message
  uint64_t rrc_msg_id;

} rrc_msg_id_t;

void free_rrc_msg_id( rrc_msg_id_t* src);

bool eq_rrc_msg_id(rrc_msg_id_t const* m0, rrc_msg_id_t const* m1);

rrc_msg_id_t cp_rrc_msg_id(rrc_msg_id_t const* src);

#endif

