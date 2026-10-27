
#include "../include/src/xApp/e42_xapp_api.h"
#include "../include/src/util/alg_ds/alg/defer.h"
#include "../include/src/sm/e2x_sm/e2x_sm_id.h"
#include "../include/src/sm/e2x_sm/ie/e2x_data_ie.h"

#include <assert.h>
#include <stdio.h>
#include <poll.h>
#include <string.h>
#include <unistd.h>

// The same layout needs to be preserved in 
// the E2 Agent 
typedef struct{
  int32_t m0; 
  float m1; 
  double m2; 
} my_data_t;

void cb_period(sm_ag_if_rd_t const* rd, global_e2_node_id_t const* node)
{
  assert(rd->type == INDICATION_MSG_AGENT_IF_ANS_V0);
  assert(rd->ind.type == E2X_STATS_V0_1);
  (void)node;
  
  e2x_ind_data_t const* uni = &rd->ind.e2x;
  e2x_ind_msg_t const* msg = &uni->msg; // needed for flexible array member

  printf("xApp: Decoding data from the read_agent function from the e2x e2 node...\n");

  size_t it = 0;

  int32_t m0 = 0;
  memcpy(&m0, msg->data + it, sizeof(m0));
  it += sizeof(m0);
  //it += decode_val(msg->data+it, m0);

  float m1 = 0.0;
  memcpy(&m1, msg->data + it, sizeof(m1));
  it += sizeof(m1);

  double m2 = 0.0;
  memcpy(&m2, msg->data + it, sizeof(m2));
  it += sizeof(m2);

  char m3[8] = {0};
  memcpy(&m3, msg->data + it, 8*sizeof(char));
  it += 8*sizeof(char);

  uint8_t m4[8] = {0};
  memcpy(&m4, msg->data + it, 8*sizeof(uint8_t));
  it += 8*sizeof(uint8_t);

  my_data_t m5 = {0};
  memcpy(&m5, msg->data + it, sizeof(m5));
  it += sizeof(m5);

  printf("xApp: m0 %d m1 %f m2 %lf m3 %s m4", m0, m1, m2, m3);
  for(size_t i = 0; i < 8; ++i){
    printf(" %x ", m4[i]); 
  }
  printf("xApp: m5.m0 %d m5.m1 %f m5.m2 %lf \n", m5.m0, m5.m1, m5.m2);
}

void cb_aperiod(sm_ag_if_rd_t const* rd, global_e2_node_id_t const* node)
{
  assert(rd->type == INDICATION_MSG_AGENT_IF_ANS_V0);
  assert(rd->ind.type == E2X_STATS_V0_1);
  (void)node;
  
  e2x_ind_data_t const* uni = &rd->ind.e2x;
  e2x_ind_msg_t const* msg = &uni->msg; // needed for flexible array member

  printf("xApp: Decoding data sent using the async function, Len %lu\n", msg->len);

  int64_t tstamp = msg->tstamp;
  printf("xApp: Tstamp received %ld msg values: ", tstamp); 
  printf("xApp: String %s \n", msg->data);
  for(size_t i = 0; i < msg->len; ++i){
    printf(" %d ", msg->data[i]);
  }
  printf("\n");
}

typedef enum{
  OPTION_1,
  OPTION_2
} ctrl_example_e;

typedef struct{
  int16_t m0;
  int16_t m1;
} ctrl_ex_opt1_t;

typedef struct{
  size_t len;
  uint8_t* data;
} ctrl_ex_opt2_t;

typedef struct{
  ctrl_example_e type; 
  union{
   ctrl_ex_opt1_t opt1;  
   ctrl_ex_opt2_t opt2;  
  };
} ctrl_example_t;

static
e2x_ctrl_req_data_t gen_e2x_ctrl_req_data(void)
{
  e2x_ctrl_req_data_t dst = {0}; 

  dst.hdr.dummy = 42;
  dst.msg.len = 1024;
  dst.msg.data = calloc(dst.msg.len, sizeof(uint8_t)); 
  assert(dst.msg.data != NULL && "Memory exhausted");

  ctrl_example_e type = OPTION_2; 
  size_t it = 0;
  memcpy(dst.msg.data + it, &type, sizeof(type));
  it += sizeof(type);

  size_t len = 10;
  memcpy(dst.msg.data + it, &len, sizeof(len));
  it += sizeof(len);

  uint8_t data[] = {9,8,7,6,5,4,3,2,1,0};
  memcpy(dst.msg.data + it, data, len); 
  it += len;

  printf("xApp: Sending %s\n", (char*)dst.msg.data);

  assert(dst.msg.len > it && "Overflow? Augment the msg len");

  return dst;
}

int main(int argc, char *argv[])
{
  assert(argc == 2);
  (void)argc;

  //Init the xApp
  init_xapp_api(argv[1]);
  poll(NULL, 0, 1000);

  e2_node_arr_xapp_t arr = e2_nodes_xapp_api();
  defer{ free_e2_node_arr_xapp(&arr); };
 
  assert(arr.len == 1 && "Demo showing how to fetch data from one E2 Node.");

  e2x_sub_data_t uni_sub_per = {.et.type = PERIODIC_E2X_SM_EVENT};
  uni_sub_per.et.per.periodicity_ms = 100;

  // Monitor periodic events for 5 seconds
  sm_ans_xapp_t hndl = report_sm_xapp_api(&arr.n[0].id, SM_E2X_ID, &uni_sub_per, cb_period);
  sleep(5);
  rm_report_sm_xapp_api(hndl.u.handle);

  e2x_ctrl_req_data_t uni_ctrl = gen_e2x_ctrl_req_data();
  // Send control message
  sm_ans_xapp_t ans = control_sm_xapp_api(&arr.n[0].id, SM_E2X_ID, &uni_ctrl);
  printf("xApp: Ctrl response %d \n", ans.success);
  sleep(1);

  e2x_sub_data_t uni_sub_aper = {.et.type = APERIODIC_E2X_SM_EVENT};
  uni_sub_aper.et.aper.len = 1024;
  uni_sub_aper.et.aper.data = calloc(1024, sizeof(uint8_t));
  assert(uni_sub_aper.et.aper.data != NULL && "Memory exhausted");
  memcpy(uni_sub_aper.et.aper.data, "Sending command", 16);

  // Monitor aperiodic events for 5 seconds
  hndl = report_sm_xapp_api(&arr.n[0].id, SM_E2X_ID, &uni_sub_aper, cb_aperiod);
  sleep(5);
  rm_report_sm_xapp_api(hndl.u.handle);

  // Stop the xApp
  while(try_stop_xapp_api() == false)
    poll(NULL, 0, 1000);


  free_e2x_sub_data(&uni_sub_per); 
  free_e2x_sub_data(&uni_sub_aper); 

  return 0;
}

