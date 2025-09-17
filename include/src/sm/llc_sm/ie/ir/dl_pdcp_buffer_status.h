#ifndef DL_PDCP_BUFFER_STATUS_E2SM_MIR_H
#define DL_PDCP_BUFFER_STATUS_E2SM_MIR_H 

#include "dl_pdcp_ue_id.h"
#include <stdbool.h>

// From 8.3.22 
typedef struct{
  // [1, 65535]
  size_t sz_dl_pdcp_ue_id;
  dl_pdcp_ue_id_t* dl_pdcp_ue_id;
} dl_pdcp_buffer_status_t;

dl_pdcp_buffer_status_t cp_dl_pdcp_buffer_status(dl_pdcp_buffer_status_t const* src);  

void free_dl_pdcp_buffer_status(dl_pdcp_buffer_status_t* src); 

bool eq_dl_pdcp_buffer_status(dl_pdcp_buffer_status_t const* m0, dl_pdcp_buffer_status_t const* m1); 



#endif
