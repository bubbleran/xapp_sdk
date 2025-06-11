#/*
#Copyright (C) 2021-2025 BubbleRAN SAS
#External application
#Last Changed: 2025-05-02
#Project: MX-XAPP
#Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
#*/

import xapp_usr_sdk as xapp
import sys

xapp.init(sys.argv)
nodes = xapp.e2_nodes(xapp.SLICE_USE_CASE_e)
assert(len(nodes) > 0 and "Needed at least one E2 node to slice")

n = nodes[0].node
sst = "0"
sd = "1"
dedicated_prb = 30
xapp.slice(n, sst, sd, dedicated_prb)

