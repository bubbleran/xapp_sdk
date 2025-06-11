/*
Copyright (C) 2021-2025 BubbleRAN SAS

External application
Last Changed: 2025-05-02
Project: MX-XAPP
Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
*/

#include "../include/src/xApp/e42_xapp_api.h"
#include "../include/src/util/alg_ds/ds/lock_guard/lock_guard.h"
#include "../include/src/util/alg_ds/ds/latch_cv/latch_cv.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define MAX_LEN_CELL 3

#define SM_CCC_ID 4

static
bwp_context_e BWP_CONTEXT = END_BWP_CONTEXT;

static
uint32_t START_RB = 0;

static
uint32_t NUMBER_OF_RBS = 0;

static
cell_global_id_t* LIST_CELL_ID_LOCAL[MAX_LEN_CELL];

static
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

static
latch_cv_t latch;


//////////////
// CCC MONITOR
//////////////

static
e2sm_ccc_event_trigger_t gen_ev_trig(void)
{
  // Periodic event
  e2sm_ccc_event_trigger_t dst = {.format = FORMAT_3_E2SM_CCC_EV_TRIGGER_FORMAT};
  dst.frmt_3.period = 10;

  return dst;
}

static
e2sm_ccc_action_def_t gen_act_def(void)
{
 e2sm_ccc_action_def_t dst = {.format = FORMAT_2_E2SM_CCC_ACT_DEF};
 size_t sz_act_def_cell_report = 1;
 dst.frmt_2.sz_act_def_cell_report = sz_act_def_cell_report;
 dst.frmt_2.act_def_cell_report = calloc(sz_act_def_cell_report, sizeof(act_def_cell_report_t));
 assert(dst.frmt_2.act_def_cell_report != NULL);

 size_t sz_act_def_ran_conf = 1;
 dst.frmt_2.act_def_cell_report[0].sz_act_def_ran_conf = sz_act_def_ran_conf;
 dst.frmt_2.act_def_cell_report[0].act_def_ran_conf = calloc(sz_act_def_ran_conf, sizeof(act_def_ran_conf_t));
 assert(dst.frmt_2.act_def_cell_report[0].act_def_ran_conf != NULL);

 dst.frmt_2.act_def_cell_report[0].act_def_ran_conf[0].ran_conf_name = cp_str_to_ba("O-NRCellCU");
 dst.frmt_2.act_def_cell_report[0].act_def_ran_conf[0].report_type = REPORT_TYPE_ALL;
 dst.frmt_2.act_def_cell_report[0].act_def_ran_conf[0].sz_attribute = 0;

 return dst;
}

void cb(sm_ag_if_rd_t const *rd, global_e2_node_id_t const *n)
{
  assert(n != NULL);
  (void)n;
  assert(rd != NULL);
  assert(rd->type == INDICATION_MSG_AGENT_IF_ANS_V0);
  assert(rd->ind.type == CCC_STATS_V3_0);

  ccc_ind_data_t const* ind = &rd->ind.ccc.ind;

  // Header
  assert(ind->hdr.format == FORMAT_1_E2SM_CCC_IND_HDR);

  // Message
  assert(ind->msg.format == FORMAT_2_E2SM_CCC_IND_MSG);
  e2sm_ccc_ind_msg_frmt_2_t const* frmt_2 = &ind->msg.frmt_2; // 9.2.1.4.2

  lock_guard(&mtx);

  assert(frmt_2->sz_ind_msg_cell_report <= MAX_LEN_CELL);
  for (size_t i = 0; i < frmt_2->sz_ind_msg_cell_report; i++){
    printf("Cell global id: %ld \n", frmt_2->ind_msg_cell_report[i].cell_global_id.nr_cgi.nr_cell_id);
    if (LIST_CELL_ID_LOCAL[i] == NULL){
      LIST_CELL_ID_LOCAL[i] = calloc(1, sizeof(cell_global_id_t));
      assert(LIST_CELL_ID_LOCAL[i] != NULL);
      *LIST_CELL_ID_LOCAL[i] = frmt_2->ind_msg_cell_report[i].cell_global_id;
    }
  }

  count_down_latch_cv(&latch);
}

//////////////////
// End CCC Monitor
//////////////////

static
e2sm_ccc_o_bwp_t fill_e2sm_ccc_o_bwp()
{
  e2sm_ccc_o_bwp_t dst = {0};

  dst.bwp_context = BWP_CONTEXT;
  dst.start_rb = START_RB;
  dst.number_of_rbs = NUMBER_OF_RBS;

  return dst;
}


// CONTROL Service Style 2: Cell level configuration and control
static
e2sm_ccc_ctrl_hdr_t gen_hdr(void)
{
  e2sm_ccc_ctrl_hdr_t dst = {.format = FORMAT_1_E2SM_CCC_CTRL_HDR}; 
  dst.frmt_1.ric_style_type = 2;

  return dst;
}

static
ctrl_msg_ran_conf_t fill_ctrl_msg_ran_conf()
{
  ctrl_msg_ran_conf_t dst = {0}; 

  dst.ran_conf_name = cp_str_to_ba("O-BWP");
  dst.vals_attributes = calloc(1, sizeof(values_of_attributes_t));
  assert(dst.vals_attributes != NULL);
  dst.vals_attributes->values_of_attributes_type = VALUES_OF_ATTRIBUTES_O_BWP;
  dst.vals_attributes->e2sm_ccc_o_bwp = fill_e2sm_ccc_o_bwp();

  dst.old_vals_attributes = calloc(1, sizeof(values_of_attributes_t));
  assert(dst.old_vals_attributes != NULL);
  dst.old_vals_attributes->values_of_attributes_type = VALUES_OF_ATTRIBUTES_O_BWP;
  dst.old_vals_attributes->e2sm_ccc_o_bwp = fill_e2sm_ccc_o_bwp();
  return dst;
}

static
ctrl_msg_cell_t fill_ctrl_msg_cell(cell_global_id_t* const cell_local_id)
{
  assert(cell_local_id != NULL);
  ctrl_msg_cell_t dst = {0};

  dst.cell_global_id = *cell_local_id;
  dst.sz_ctrl_msg_ran_conf = 1;
  dst.ctrl_msg_ran_conf = calloc(dst.sz_ctrl_msg_ran_conf, sizeof(ctrl_msg_ran_conf_t));
  assert(dst.ctrl_msg_ran_conf!= NULL && "Memory exhausted");
  dst.ctrl_msg_ran_conf[0] = fill_ctrl_msg_ran_conf();

  return dst;
}

static
e2sm_ccc_ctrl_msg_t gen_msg(cell_global_id_t* const cell_local_id)
{
  assert(cell_local_id != NULL);
  e2sm_ccc_ctrl_msg_t dst = {0}; 

  // Cell Level
  dst.format = FORMAT_2_E2SM_CCC_CTRL_MSG;
  dst.frmt_2.sz_ctrl_msg_cell = 1;
  dst.frmt_2.ctrl_msg_cell = calloc(dst.frmt_2.sz_ctrl_msg_cell, sizeof(ctrl_msg_cell_t));
  assert(dst.frmt_2.ctrl_msg_cell != NULL);
  dst.frmt_2.ctrl_msg_cell[0] = fill_ctrl_msg_cell(cell_local_id);

  return dst;
}


int main(int argc, char *argv[])
{
  assert(argc > 3 && "Require bwp_context(1 = dl, 2 = ul), rb start and number of rbs");
  fr_args_t args = init_fr_args(argc, argv);
  defer({ free_fr_args(&args); });
  for (int i = argc - 1; i > 0; i--){
    if(i == argc - 1)
      NUMBER_OF_RBS = atoi(argv[i]);
    if(i == argc - 2)
      START_RB = atoi(argv[i]);
    if(i == argc - 3){
      int opt = atoi(argv[i]);
      if (opt == 1){
        BWP_CONTEXT = DL_BWP_CONTEXT;
      } else if (opt == 2) {
        BWP_CONTEXT = UL_BWP_CONTEXT;
      } else {
        assert("Unknown bwp context");
      }
    }
    if(i < argc - 3)
      break;
  }

  //Init the xApp
  init_xapp_api(&args);
  sleep(1);

  e2_node_arr_xapp_t nodes = e2_nodes_xapp_api();
  defer({ free_e2_node_arr_xapp(&nodes); });
  assert(nodes.len > 0);
  printf("Connected E2 nodes = %d\n", nodes.len);

  ////////////
  // START CCC
  ////////////

  /// CCC Monitor
  // Report Service style 2
  // Indication header format 2 - return upon subscription
  // Indication message format 2 - return cell ID and their changes
  // O-NRCellCU
  // CellLocalID
  latch = init_latch_cv(nodes.len);
  defer({free_latch_cv(&latch); });

  sm_ans_xapp_t* hndl = calloc(nodes.len, sizeof(sm_ans_xapp_t));
  defer({ free(hndl); });

  ccc_sub_data_t ccc_sub = {0};
  defer({free_ccc_sub_data(&ccc_sub);});
  ccc_sub.et = gen_ev_trig();
  ccc_sub.sz_ad = 1;
  ccc_sub.ad = calloc(ccc_sub.sz_ad, sizeof(e2sm_ccc_action_def_t));
  assert(ccc_sub.ad != NULL);
  ccc_sub.ad[0] = gen_act_def();

  for (size_t i = 0; i < nodes.len; ++i) {
    hndl[i] = report_sm_xapp_api(&nodes.n[i].id, SM_CCC_ID, &ccc_sub, cb);
    assert(hndl[i].success == true);
  }

  wait_latch_cv(&latch);

  for(int i = 0; i < nodes.len; ++i) {
    rm_report_sm_xapp_api(hndl[i].u.handle);
  }

  // CCC Control
  // CONTROL Service Style 2: Cell level configuration and control
  // E2SM-CCC Control Header Format 1
  // E2SM-CCC Control Message Format 2

  // Send control message for each cell
  for (size_t i = 0; i < MAX_LEN_CELL; ++i) {
    if (LIST_CELL_ID_LOCAL[i] == NULL){
      continue;
    }

    ccc_ctrl_req_data_t ccc_ctrl = {0};
    ccc_ctrl.hdr = gen_hdr();
    ccc_ctrl.msg = gen_msg(LIST_CELL_ID_LOCAL[i]);


    int64_t const t0 = time_now_us_xapp_api();
    for (size_t j = 0; j < nodes.len; ++j) {
      control_sm_xapp_api(&nodes.n[j].id, SM_CCC_ID, &ccc_ctrl);
    }

    printf("[xApp]: Control Loop Latency: %ld us\n", time_now_us_xapp_api() - t0);
    free_ccc_ctrl_req_data(&ccc_ctrl);
  }

  ////////////
  // END CCC
  ////////////

  //Stop the xApp
  while(try_stop_xapp_api() == false)
    usleep(1000);

  for (int i = 0; i < MAX_LEN_CELL; ++i) {
    if (LIST_CELL_ID_LOCAL[i] != NULL){
      free_cell_global_id(LIST_CELL_ID_LOCAL[i]);
    }
    free(LIST_CELL_ID_LOCAL[i]);
  }

  printf("Test xApp run SUCCESSFULLY\n");
}
