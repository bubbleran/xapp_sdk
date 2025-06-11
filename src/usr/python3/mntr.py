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

xapp.init(sys.argv)
nodes = xapp.e2_nodes(xapp.MONITOR_USE_CASE_e)
assert(len(nodes) > 0 and "Needed at least one E2 node to monitor")

t0 = time.time_ns()
v = xapp.mntr(nodes[0].node, xapp.PDCP_SDU_VOLUME_DL)
t1 = time.time_ns()

print("Value " + str(v) + " elapsed time " + str((t1 -t0)/1000000.0) + " milliseconds")

