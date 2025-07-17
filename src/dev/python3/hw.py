import time
import os
import pdb
import signal
import sys
from tabulate import tabulate
cur_dir = os.path.dirname(os.path.abspath(__file__))
# print("Current Directory:", cur_dir)
sdk_path = cur_dir + "/../xapp_sdk/"
sys.path.append(sdk_path)

import xapp_sdk as ric

####################
####  GENERAL
####################

ric.init(sys.argv)
conn = ric.conn_e2_nodes()

if not (len(conn) > 0):
    print("No E2-Node connected.")

e2nodes_col_names = ["idx", "nb_id", "mcc", "mnc", "ran_type"]
e2nodes_data = []
for i in range(0, len(conn)):
    # NodeB ID
    nb_id = conn[i].id.nb_id.nb_id
    # PLMN
    mcc = conn[i].id.plmn.mcc
    mnc = conn[i].id.plmn.mnc
    # RAN type
    if conn[i].id.type == 0:
        ran_type = "ngran_eNB"
    elif conn[i].id.type == 2:
        ran_type = "ngran_gNB"
    elif conn[i].id.type == 5:
        ran_type = "ngran_gNB_CU"
    elif conn[i].id.type == 7:
        ran_type = "ngran_gNB_DU"
    else:
        ran_type = "Unknown"
    info = [i,
            nb_id,
            mcc,
            mnc,
            ran_type]
    # print(info)
    e2nodes_data.append(info)
print(tabulate(e2nodes_data, headers=e2nodes_col_names, tablefmt="grid"))


####################
####  End
####################
# Avoid deadlock. ToDo revise architecture
while ric.try_stop == 0:
    time.sleep(1)

print("Test xApp run SUCCESSFULLY")