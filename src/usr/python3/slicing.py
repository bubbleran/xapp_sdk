import sys
import xapp_usr_sdk as xapp

xapp.init(sys.argv)
nodes = xapp.e2_nodes(xapp.SLICE_USE_CASE_e)
assert(len(nodes) > 0 and "Needed at least one E2 node to slice")

node_idx = -1
for i in range(0, len(nodes)):
    if (nodes[i].node.type == xapp.e2ap_ngran_gNB_DU_SDK or nodes[i].node.type == xapp.e2ap_ngran_gNB_SDK):
        node_idx = i

assert(node_idx > -1 and "require node type is gNB or DU")

n = nodes[node_idx].node
sst = "1"
sd = "0"
dedicated_prb = 30
xapp.slice(n, sst, sd, dedicated_prb)

