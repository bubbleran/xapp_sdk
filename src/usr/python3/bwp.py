import sys
import xapp_usr_sdk as xapp

xapp.init(sys.argv)
nodes = xapp.e2_nodes(xapp.BWP_USE_CASE_e)
assert(len(nodes) > 0 and "Needed at least one E2 node to change bwp")

n = nodes[0].node
cell = nodes[0].cell[0] 
start_rb = 0
number_rb = 10

xapp.bandwidth_part(n, cell,xapp.DL_BWP_CONTEXT_SDK, start_rb, number_rb)

