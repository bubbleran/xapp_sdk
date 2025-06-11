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

class Monitor(xapp.mntr_cb_fn):
    # Inherit C++ mntr_cb_fn class
    def __init__(self):
        xapp.mntr_cb_fn.__init__(self)

    # Override C++ method 
    def cb(self,v):
        print("Value " + str(v))

xapp.init(sys.argv)
nodes = xapp.e2_nodes(xapp.MONITOR_USE_CASE_e)
assert(len(nodes) > 0 and "Needed at least one E2 node to monitor")

call_back = Monitor().__disown__()

n = nodes[0].node
ue = nodes[0].ue_ho[0].ue
token = xapp.mntr_ue_cb(n, ue, xapp.UE_THP_DL, xapp.PERIODICITY_10_MS, call_back)

time.sleep(10)

xapp.stop_mntr(token)

print("Test xApp run SUCCESSFULLY")
