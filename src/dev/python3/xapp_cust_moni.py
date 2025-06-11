#/*
#Copyright (C) 2021-2025 BubbleRAN SAS

#External application
#Last Changed: 2025-05-02
#Project: MX-XAPP
#Full License: https://bubbleran.com/resources/files/BubbleRAN_Licence-Agreement-1.3.pdf)
#*/

import time
import os
import pdb
import csv
import sys
cur_dir = os.path.dirname(os.path.abspath(__file__))
# print("Current Directory:", cur_dir)
sdk_path = cur_dir + "/../xapp_sdk/"
sys.path.append(sdk_path)

import xapp_sdk as ric

####################
#### MAC INDICATION CALLBACK
####################

# MACCallback class is defined and derived from C++ class mac_cb
class MACCallback(ric.mac_cb):
    # Define Python class 'constructor'
    def __init__(self):
        # Call C++ base class constructor
        ric.mac_cb.__init__(self)
    # Override C++ method: virtual void handle(swig_mac_ind_msg_t a) = 0;
    def handle(self, ind):
        # Print swig_mac_ind_msg_t
        if len(ind.ue_stats) > 0:
            t_now = time.time_ns() / 1000.0
            t_mac = ind.tstamp / 1.0
            t_diff = t_now - t_mac
            print(f"MAC Indication tstamp {t_now} diff {t_diff} E2-node type {ind.id.type} nb_id {ind.id.nb_id.nb_id}")
            # with open(file_name, 'a', newline='', buffering=1024) as f:
            #     writer = csv.writer(f)
            #     writer.writerow([ind.id.nb_id.nb_id, ind.id.type, "MAC", t_diff])
            # print('MAC rnti = ' + str(ind.ue_stats[0].rnti))

####################
#### RLC INDICATION CALLBACK
####################

class RLCCallback(ric.rlc_cb):
    # Define Python class 'constructor'
    def __init__(self):
        # Call C++ base class constructor
        ric.rlc_cb.__init__(self)
    # Override C++ method: virtual void handle(swig_rlc_ind_msg_t a) = 0;
    def handle(self, ind):
        # Print swig_rlc_ind_msg_t
        if len(ind.rb_stats) > 0:
            t_now = time.time_ns() / 1000.0
            t_rlc = ind.tstamp / 1.0
            t_diff= t_now - t_rlc
            print(f"RLC Indication tstamp {t_now} diff {t_diff} E2-node type {ind.id.type} nb_id {ind.id.nb_id.nb_id}")
            # with open(file_name, 'a', newline='', buffering=1024) as f:
            #     writer = csv.writer(f)
            #     writer.writerow([ind.id.nb_id.nb_id, ind.id.type, "RLC", t_diff])
            # print('RLC rnti = '+ str(ind.rb_stats[0].rnti))

####################
#### PDCP INDICATION CALLBACK
####################

class PDCPCallback(ric.pdcp_cb):
    # Define Python class 'constructor'
    def __init__(self):
        # Call C++ base class constructor
        ric.pdcp_cb.__init__(self)
   # Override C++ method: virtual void handle(swig_pdcp_ind_msg_t a) = 0;
    def handle(self, ind):
        # Print swig_pdcp_ind_msg_t
        if len(ind.rb_stats) > 0:
            t_now = time.time_ns() / 1000.0
            t_pdcp = ind.tstamp / 1.0
            t_diff = t_now - t_pdcp
            print(f"PDCP Indication tstamp {t_now} diff {t_diff} E2-node type {ind.id.type} nb_id {ind.id.nb_id.nb_id}")
            # with open(file_name, 'a', newline='', buffering=1024) as f:
            #     writer = csv.writer(f)
            #     writer.writerow([ind.id.nb_id.nb_id, ind.id.type, "PDCP", t_diff])
            # print('PDCP rnti = '+ str(ind.rb_stats[0].rnti))

####################
#### GTP INDICATION CALLBACK
####################

# Create a callback for GTP which derived it from C++ class gtp_cb
class GTPCallback(ric.gtp_cb):
    def __init__(self):
        # Inherit C++ gtp_cb class
        ric.gtp_cb.__init__(self)
    # Create an override C++ method
    def handle(self, ind):
        if len(ind.gtp_stats) > 0:
            t_now = time.time_ns() / 1000.0
            t_gtp = ind.tstamp / 1.0
            t_diff = t_now - t_gtp
            print(f"GTP Indication tstamp {t_now} diff {t_diff} e2 node type {ind.id.type} nb_id {ind.id.nb_id.nb_id}")

####################
#### SLICE INDICATION CALLBACK
####################

# Create a callback for SLICE which derived it from C++ class slice_cb
class SLICECallback(ric.slice_cb):
    def __init__(self):
        # Inherit C++ gtp_cb class
        ric.slice_cb.__init__(self)
    # Create an override C++ method
    def handle(self, ind):
        t_now = time.time_ns() / 1000.0
        t_slice = ind.tstamp / 1.0
        t_diff = t_now - t_slice
        print(f"SLICE Indication tstamp {t_now} diff {t_diff} e2 node type {ind.id.type} nb_id {ind.id.nb_id.nb_id}")


def get_cust_tti(tti):
    if tti == "1_ms":
        return ric.Interval_ms_1
    elif tti == "2_ms":
        return ric.Interval_ms_2
    elif tti == "5_ms":
        return ric.Interval_ms_5
    elif tti == "10_ms":
        return ric.Interval_ms_10
    elif tti == "100_ms":
        return ric.Interval_ms_100
    elif tti == "1000_ms":
        return ric.Interval_ms_1000
    else:
        print(f"Unknown tti {tti}")
        exit()

mac_hndlr = []
rlc_hndlr = []
pdcp_hndlr = []
gtp_hndlr = []
slice_hndlr = []
####################
####  GENERAL 
####################
if __name__ == '__main__':

    # file_name = "ind_output.csv"
    # file_col = ['e2node-nb-id', 'e2node-ran-type', 'SM', 'latency']
    # if file already exists, remove it
    # if os.path.exists(file_name):
    #     os.remove(file_name)
    # # create new csv file and write headers
    # with open(file_name, 'w', newline='') as f:
    #     writer = csv.writer(f)
    #     writer.writerow(file_col)

    # Start
    ric.init(sys.argv)
    cust_sm = ric.get_cust_sm_conf()

    conn = ric.conn_e2_nodes()
    assert(len(conn) > 0)
    for i in range(0, len(conn)):
        print("Global E2 Node [" + str(i) + "]: PLMN MCC = " + str(conn[i].id.plmn.mcc))
        print("Global E2 Node [" + str(i) + "]: PLMN MNC = " + str(conn[i].id.plmn.mnc))


    for sm_info in cust_sm:
        sm_name = sm_info.name
        sm_time = sm_info.time
        tti = get_cust_tti(sm_time)

        if sm_name == "MAC":
            for i in range(0, len(conn)):
                # MAC
                mac_cb = MACCallback()
                hndlr = ric.report_mac_sm(conn[i].id, tti, mac_cb)
                mac_hndlr.append(hndlr)
                time.sleep(1)
        elif sm_name == "RLC":
            for i in range(0, len(conn)):
                # RLC
                rlc_cb = RLCCallback()
                hndlr = ric.report_rlc_sm(conn[i].id, tti, rlc_cb)
                rlc_hndlr.append(hndlr)
                time.sleep(1)
        elif sm_name == "PDCP":
            for i in range(0, len(conn)):
                # PDCP
                pdcp_cb = PDCPCallback()
                hndlr = ric.report_pdcp_sm(conn[i].id, tti, pdcp_cb)
                pdcp_hndlr.append(hndlr)
                time.sleep(1)
        elif sm_name == "GTP":
            for i in range(0, len(conn)):
                # GTP
                gtp_cb = GTPCallback()
                hndlr = ric.report_gtp_sm(conn[i].id, tti, gtp_cb)
                gtp_hndlr.append(hndlr)
                time.sleep(1)
        elif sm_name == "SLICE":
            for i in range(0, len(conn)):
                # SLICE
                slice_cb = SLICECallback()
                hndlr = ric.report_slice_sm(conn[i].id, tti, slice_cb)
                slice_hndlr.append(hndlr)
                time.sleep(1)
        else:
            print(f"not yet implemented function to send subscription for {sm_name}")

    time.sleep(10)

    ### End
    for i in range(0, len(mac_hndlr)):
        ric.rm_report_mac_sm(mac_hndlr[i])

    for i in range(0, len(rlc_hndlr)):
        ric.rm_report_rlc_sm(rlc_hndlr[i])

    for i in range(0, len(pdcp_hndlr)):
        ric.rm_report_pdcp_sm(pdcp_hndlr[i])

    for i in range(0, len(gtp_hndlr)):
        ric.rm_report_gtp_sm(gtp_hndlr[i])

    for i in range(0, len(slice_hndlr)):
        ric.rm_report_slice_sm(slice_hndlr[i])

    # Avoid deadlock. ToDo revise architecture
    while ric.try_stop == 0:
        time.sleep(1)

    print("Test finished")
