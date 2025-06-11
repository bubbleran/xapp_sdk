#/*
#Copyright (C) 2021-2025 BubbleRAN SAS
#External application
#Last Changed: 2025-05-02
#Project: MX-XAPP
#Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
#*/

import time
import xapp_usr_sdk as xapp
import sys

global_node = None
dedicated_prb = 10

class Monitor(xapp.mntr_cb_fn):
    # Inherit C++ mntr_cb_fn class
    def __init__(self):
        xapp.mntr_cb_fn.__init__(self)

    # Override C++ method 
    def cb(self, ue_thp_kbs):
        if ue_thp_kbs > 9999.9 and ue_thp_kbs < 15000.1 :
            return

        global dedicated_prb 
        if ue_thp_kbs < 10000.0:
            dedicated_prb = dedicated_prb + 2; 
        elif ue_thp_kbs > 15000.0: 
            dedicated_prb = dedicated_prb - 2; 

        min_prb = 10;
        max_prb = 100;

        dedicated_prb = max(min_prb, min(max_prb, dedicated_prb)) 

        sst = "0"
        sd = "1"
        xapp.slice(global_node, sst, sd, dedicated_prb)


xapp.init(sys.argv)
#Step 1 
# Retrieve the amount of E2 Nodes in the system

assert(len(nodes) > 0 and "Needed at least one E2 node to monitor")

call_back = Monitor().__disown__()

n = nodes[0].node
global_node = n

ue = nodes[0].ue_ho[0].ue
global_ue = ue

# Step 2
# Correctly call the function mntr_ue_cb 

time.sleep(60)

xapp.stop_mntr(token)

