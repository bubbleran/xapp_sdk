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
import time
import signal
import sys
cur_dir = os.path.dirname(os.path.abspath(__file__))
# print("Current Directory:", cur_dir)
sdk_path = cur_dir + "/../xapp_sdk/"
sys.path.append(sdk_path)

import xapp_sdk as ric

####################
#### KPM INDICATION CALLBACK
####################

# Create a callback for KPM which derived it from C++ class kpm_cb
class KPMCallback(ric.kpm_cb):
    def __init__(self):
        # Inherit C++ kpm_cb class
        ric.kpm_cb.__init__(self)
    # Create an override C++ method 
    def handle(self, ind):
        if ind.hdr:
            t_now = time.time_ns() / 1000.0
            t_kpm = ind.hdr.kpm_ric_ind_hdr_format_1.collectStartTime / 1.0
            t_diff = t_now - t_kpm
            print(f"KPM Indication tstamp {t_now} diff {t_diff} E2-node type {ind.id.type} nb_id {ind.id.nb_id.nb_id}")
            # if ind.hdr.kpm_ric_ind_hdr_format_1.fileformat_version:
            #     print(f"fileformat_version {ind.hdr.kpm_ric_ind_hdr_format_1.fileformat_version}")
            # if ind.hdr.kpm_ric_ind_hdr_format_1.sender_name:
            #     print(f"sender_name {ind.hdr.kpm_ric_ind_hdr_format_1.sender_name}")
            # if ind.hdr.kpm_ric_ind_hdr_format_1.sender_type:
            #     print(f"sender_type {ind.hdr.kpm_ric_ind_hdr_format_1.sender_type}")
            # if ind.hdr.kpm_ric_ind_hdr_format_1.vendor_name:
            #     print(f"vendor_name {ind.hdr.kpm_ric_ind_hdr_format_1.vendor_name}")
        if ind.msg.type == ric.FORMAT_1_INDICATION_MESSAGE:
            ind_frm1 = ind.msg.frm_1
            print(f"ind_frm1.meas_data_lst_len {ind_frm1.meas_data_lst_len}")
            for index, meas_data in enumerate(ind_frm1.meas_data_lst):
                print(f"meas data idx {index}")
                if meas_data.incomplete_flag == ric.TRUE_ENUM_VALUE:
                    print(f"<<< Measurement Record not reliable >>> ")
                if meas_data.meas_record_len == ind_frm1.meas_info_lst_len:
                    # print(f"meas_data.meas_record_len {meas_data.meas_record_len}, ind_frm1.meas_info_lst_len {ind_frm1.meas_info_lst_len}")
                    for meas_record, meas_info in zip(meas_data.meas_record_lst, ind_frm1.meas_info_lst):
                        # print(f"value: {meas_record.value}")
                        # print(f"type: {meas_info.meas_type.type}")
                        print_value = 0
                        if meas_record.value == ric.INTEGER_MEAS_VALUE:
                            print_value = meas_record.int_val
                        elif meas_record.value == ric.REAL_MEAS_VALUE:
                            print_value = meas_record.real_val
                        elif meas_record.value == ric.NO_VALUE_MEAS_VALUE:
                            print_value = meas_record.no_value
                        else:
                            print(f"unknown meas_record")

                        print_name_id = 0
                        if meas_info.meas_type.type == ric.NAME_MEAS_TYPE:
                            print_name_id = meas_info.meas_type.name
                        elif meas_info.meas_type.type == ric.ID_MEAS_TYPE:
                            print_name_id = meas_info.meas_type.id
                        else:
                            print(f"unknown meas info type")
                        print(f"Measurement name/id:value {print_name_id}:{print_value}")
                else:
                    print(f"meas_data.meas_record_len {meas_data.meas_record_len} != ind_frm1.meas_info_lst_len {ind_frm1.meas_info_lst_len}, cannot map value to name")

            print(f"ind_frm1.gran_period_ms {ind_frm1.gran_period_ms}")
        elif ind.msg.type == ric.FORMAT_3_INDICATION_MESSAGE:
            # print(f"ind.msg.type {ind.msg.type}")
            # print(f"ind.msg.frm_3.ue_meas_report_lst_len {ind.msg.frm_3.ue_meas_report_lst_len}")
            for ue_meas in ind.msg.frm_3.meas_report_per_ue: # swig_meas_report_per_ue_t
                # swig_ue_id_e2sm_t
                print(f"ue_meas.type {ue_meas.ue_meas_report_lst.type}")
                ue = ue_meas.ue_meas_report_lst
                if ue.type == ric.GNB_UE_ID_E2SM:
                    print(f"ue.gnb.amf_ue_ngap_id {ue.gnb.amf_ue_ngap_id},"
                          f"ue.gnb.guami.plmn_id.mcc {ue.gnb.guami.plmn_id.mcc},"
                          f"ue.gnb.guami.plmn_id.mnc {ue.gnb.guami.plmn_id.mnc},"
                          f"ue.gnb.guami.plmn_id.mnc_digit_len {ue.gnb.guami.plmn_id.mnc_digit_len}")
                elif ue.type == ric.GNB_DU_UE_ID_E2SM:
                    print(f"ue.gnb_du.gnb_cu_ue_f1ap {ue.gnb_du.gnb_cu_ue_f1ap}")
                elif ue.type == ric.GNB_CU_UP_UE_ID_E2SM:
                    print(f"ue.gnb_cu_up.gnb_cu_cp_ue_e1ap {ue.gnb_cu_up.gnb_cu_cp_ue_e1ap}")
                else:
                    print("python3: not support ue_id_e2sm type")
                # swig_kpm_ind_msg_format_1_t
                ind_frm1 = ue_meas.ind_msg_format_1
                print(f"ind_frm1.meas_data_lst_len {ind_frm1.meas_data_lst_len}")
                for meas_data in ind_frm1.meas_data_lst:
                    # print(f"meas_data.meas_record_len {meas_data.meas_record_len}")
                    # for meas_record in meas_data.meas_record_lst:
                    #     # print(f"meas_record.value {meas_record.value}")
                    #     if meas_record.value == ric.INTEGER_MEAS_VALUE:
                    #         print(f"meas_record.int_val {meas_record.int_val}")
                    #     elif meas_record.value == ric.REAL_MEAS_VALUE:
                    #         print(f"meas_record.real_val {meas_record.real_val}")
                    #     elif meas_record.value == ric.NO_VALUE_MEAS_VALUE:
                    #         print(f"meas_record.no_value {meas_record.no_value}")
                    #     else:
                    #         print(f"unknown meas_record")
                    if meas_data.incomplete_flag == ric.TRUE_ENUM_VALUE:
                        print(f"<<< Measurement Record not reliable >>> ")

                    if meas_data.meas_record_len == ind_frm1.meas_info_lst_len:
                        # print(f"meas_data.meas_record_len {meas_data.meas_record_len}, ind_frm1.meas_info_lst_len {ind_frm1.meas_info_lst_len}")
                        for meas_record, meas_info in zip(meas_data.meas_record_lst, ind_frm1.meas_info_lst):
                            # print(f"value: {meas_record.value}")
                            # print(f"type: {meas_info.meas_type.type}")
                            print_value = 0
                            if meas_record.value == ric.INTEGER_MEAS_VALUE:
                                print_value = meas_record.int_val
                            elif meas_record.value == ric.REAL_MEAS_VALUE:
                                print_value = meas_record.real_val
                            elif meas_record.value == ric.NO_VALUE_MEAS_VALUE:
                                print_value = meas_record.no_value
                            else:
                                print(f"unknown meas_record")

                            print_name_id = 0
                            if meas_info.meas_type.type == ric.NAME_MEAS_TYPE:
                                print_name_id = meas_info.meas_type.name
                            elif meas_info.meas_type.type == ric.ID_MEAS_TYPE:
                                print_name_id = meas_info.meas_type.id
                            else:
                                print(f"unknown meas info type")
                            print(f"Measurement name/id:value {print_name_id}:{print_value}")
                    else:
                        print(f"meas_data.meas_record_len {meas_data.meas_record_len} != ind_frm1.meas_info_lst_len {ind_frm1.meas_info_lst_len}, cannot map value to name")


                # print(f"ind_frm1.meas_info_lst_len {ind_frm1.meas_info_lst_len}")
                # for meas_info in ind_frm1.meas_info_lst:
                #     # print(f"meas_info.meas_type.type {meas_info.meas_type.type}")
                #     if meas_info.meas_type.type == ric.NAME_MEAS_TYPE:
                #         print(f"meas_info.meas_type.name {meas_info.meas_type.name}")
                #     elif meas_info.meas_type.type == ric.ID_MEAS_TYPE:
                #         print(f"meas_info.meas_type.id {meas_info.meas_type.id}")
                #     else:
                #         print(f"unknown meas info type")

                print(f"ind_frm1.gran_period_ms {ind_frm1.gran_period_ms}")
        else:
            print(f"not implement KPM indication format {ind.msg.type}")



def get_oran_tti(tti):
    if tti == 1:
        return ric.Interval_ms_1
    elif tti == 2:
        return ric.Interval_ms_2
    elif tti == 5:
        return ric.Interval_ms_5
    elif tti == 10:
        return ric.Interval_ms_10
    elif tti == 100:
        return ric.Interval_ms_100
    elif tti == 1000:
        return ric.Interval_ms_1000
    else:
        print(f"Unknown tti {tti}")
        exit()

####################
####  GENERAL 
####################

ric.init(sys.argv)
oran_sm = ric.get_oran_sm_conf()

conn = ric.conn_e2_nodes()
assert(len(conn) > 0)

print("Connected E2 nodes =", len(conn))
for i in range(0, len(conn)):
    print("Global E2 Node [" + str(i) + "]: PLMN MCC = " + str(conn[i].id.plmn.mcc))
    print("Global E2 Node [" + str(i) + "]: PLMN MNC = " + str(conn[i].id.plmn.mnc))


####################
#### KPM INDICATION
####################

kpm_hndlr = []
n_hndlr = 0
for sm_info in oran_sm:
    sm_name = sm_info.name
    if sm_name != "KPM":
        print(f"not support {sm_name} in python")
        continue
    sm_time = sm_info.time
    tti = get_oran_tti(sm_time)
    sm_format = sm_info.format
    ran_type = sm_info.ran_type
    act_len = sm_info.act_len
    act = []
    for a in sm_info.actions:
        act.append(a.name)
    for i in range(0, len(conn)):
        if conn[i].id.type == ric.e2ap_ngran_eNB:
            continue
        if ran_type == ric.get_e2ap_ngran_name(conn[i].id.type):
            kpm_cb = KPMCallback()
            hndlr = ric.report_kpm_sm(conn[i].id, tti, act, kpm_cb)
            kpm_hndlr.append(hndlr)
            n_hndlr += 1
            time.sleep(1)


time.sleep(10)

### End

for i in range(0, n_hndlr):
    ric.rm_report_kpm_sm(kpm_hndlr[i])

# Avoid deadlock. ToDo revise architecture 
while ric.try_stop == 0:
    time.sleep(1)

print("Test xApp run SUCCESSFULLY")
