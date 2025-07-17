import sys
import time
import xapp_usr_sdk as xapp

xapp.init(sys.argv)
nodes = xapp.e2_nodes(xapp.MONITOR_USE_CASE_e)
assert(len(nodes) > 0 and "Needed at least one E2 node to monitor")

t0 = time.time_ns()
v = xapp.mntr(nodes[0].node, xapp.PDCP_SDU_VOLUME_DL)
t1 = time.time_ns()

print("Value " + str(v) + " elapsed time " + str((t1 -t0)/1000000.0) + " milliseconds")
