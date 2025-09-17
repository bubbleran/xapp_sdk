#ifndef LIST_LOGICAL_CHANNEL_UE_ID_LLC_E2SM_MIR_H
#define LIST_LOGICAL_CHANNEL_UE_ID_LLC_E2SM_MIR_H 

#include "logical_channel_ue_id.h"
#include <stdbool.h>

typedef struct{
  //[0, 65535]
  size_t sz_logical_channel_ue_id;
  logical_channel_ue_id_t* logical_channel_ue_id; 
} lst_logical_channel_ue_id_t;

lst_logical_channel_ue_id_t cp_lst_logical_channel_ue_id(lst_logical_channel_ue_id_t const* src);

void free_lst_logical_channel_ue_id(lst_logical_channel_ue_id_t* src);

bool eq_lst_logical_channel_ue_id(lst_logical_channel_ue_id_t const* m0, lst_logical_channel_ue_id_t const* m1);

#endif
