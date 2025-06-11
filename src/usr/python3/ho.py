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
nodes = xapp.e2_nodes(xapp.HAND_OVER_USE_CASE_e)
assert(len(nodes) > 0 and len(nodes) < 3 and "Needed at least 1 or 2 E2 nodes to handover")

sum_ue = 0
for idx in range(len(nodes)):
    sum_ue += len(nodes[idx].ue_ho)
assert(sum_ue > 0 and "At least one UE needed")

idx = 0 if len(nodes[0].ue_ho) > 0 else 1
n  = nodes[idx].node
ue = nodes[idx].ue_ho[0].ue
ho_pci = nodes[idx].ue_ho[0].nghbr_cell[0].target_pci
ho_ssb = nodes[idx].ue_ho[0].nghbr_cell[0].target_ssb_nr_arfcn 

xapp.hand_over(n, ue, ho_pci, ho_ssb)

