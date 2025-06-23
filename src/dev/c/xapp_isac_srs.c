#include "../include/src/xApp/e42_xapp_api.h"
#include "../include/src/util/alg_ds/alg/defer.h"
#include "../include/src/util/time_now_us.h"
#include "../include/src/sm/isac_sm/isac_sm_id.h"
#include <poll.h>
#include <stdio.h>

void cb(sm_ag_if_rd_t const *rd, global_e2_node_id_t const *n) 
{
  assert(n != NULL);
  assert(rd != NULL);
  assert(rd->type == INDICATION_MSG_AGENT_IF_ANS_V0);
  assert(rd->ind.type == ISAC_STATS_V0);

  isac_ind_data_t const* ind = &rd->ind.isac;
  isac_ind_msg_t const* msg = ind->msg; // needed for flexible array member
  printf("Timestamp %ld latency %ld \n", msg->tstamp, time_now_us() - msg->tstamp);
  printf("len_srs_iq %lu \n", msg->len_srs_iq);

//  int16_t const* srs_iq = msg->srs_iq;
  for(size_t i = 0; i < msg->len_srs_iq; ++i){
//    printf("re %d im %d noise_re %d noise_im %d \n",srs_iq[4*i], srs_iq[4*i+1], srs_iq[4*i+2], srs_iq[4*i+3]); 
  }
}

static
isac_sub_data_t gen_isac_sub_data(void)
{
  isac_sub_data_t dst = {0}; 
  dst.et.type = APERIODIC_ISAC_EVENT;
  dst.et.aper = SRS_ISAC_EVENT_TRIGGER_APER;

  return dst;
}

int main(int argc, char *argv[])
{
  assert(argc == 2);

  //Init the xApp
  init_xapp_api(argv[1]);
  poll(NULL, 0, 1000);

  e2_node_arr_xapp_t arr = e2_nodes_xapp_api();
  defer({ free_e2_node_arr_xapp(&arr); });
 
  assert(arr.len > 0);
  sm_ans_xapp_t* hndl = calloc(arr.len, sizeof(sm_ans_xapp_t)); 
  defer({ free(hndl); });

  // Generate RAN CONTROL Subscription
  isac_sub_data_t isac_sub = gen_isac_sub_data();  
  defer({ free_isac_sub_data(&isac_sub); });

  // Retrieve information about the E2 Nodes in the callback func (cb)
  for(size_t i = 0; i < arr.len; ++i){
    hndl[i] = report_sm_xapp_api(&arr.n[i].id, SM_ISAC_ID, &isac_sub, cb);
    assert(hndl[i].success == true);
  }

  poll(NULL, 0, 2000);

  for(size_t i = 0; i < arr.len; ++i){
    rm_report_sm_xapp_api(hndl[i].u.handle);
  }

  // stop the xApp
  while(try_stop_xapp_api() == false)
    poll(NULL, 0, 1000);

  return 0;
}

