import sys
import xapp_usr_sdk as xapp

xapp.init(sys.argv)
nodes = xapp.e2_nodes(xapp.MONITOR_USE_CASE_e)
assert(len(nodes) > 0 and "Needed at least one E2 node to monitor")
assert(len(nodes[0].ue_ho) > 0 and "Needed at least one UE to monitor")
n = nodes[0].node
ue = nodes[0].ue_ho[0].ue
v = xapp.mntr_ue(n, ue, xapp.PDCP_SDU_VOLUME_DL)

print("Value " + str(v))
