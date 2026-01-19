import time
import os
from tabulate import tabulate
import signal
import sys

cur_dir = os.path.dirname(os.path.abspath(__file__))
sdk_path = cur_dir + "/../xapp_sdk/"
sys.path.append(sdk_path)

import xapp_sdk as ric

# -----------------------------------------------------------------------------
# Callbacks
# -----------------------------------------------------------------------------

class MACCallback(ric.mac_cb):
    def __init__(self):
        super().__init__()
    def handle(self, ind):
        if len(ind.ue_stats) > 0:
            t_now = time.time_ns() / 1000.0
            t_mac = ind.tstamp / 1.0
            t_diff = t_now - t_mac
            print(f"MAC Indication tstamp {t_now} diff {t_diff} E2-node type {ind.id.type} nb_id {ind.id.nb_id.nb_id}")

class RLCCallback(ric.rlc_cb):
    def __init__(self):
        super().__init__()
    def handle(self, ind):
        if len(ind.rb_stats) > 0:
            t_now = time.time_ns() / 1000.0
            t_rlc = ind.tstamp / 1.0
            t_diff = t_now - t_rlc
            print(f"RLC Indication tstamp {t_now} diff {t_diff} E2-node type {ind.id.type} nb_id {ind.id.nb_id.nb_id}")

class PDCPCallback(ric.pdcp_cb):
    def __init__(self):
        super().__init__()
    def handle(self, ind):
        if len(ind.rb_stats) > 0:
            t_now = time.time_ns() / 1000.0
            t_pdcp = ind.tstamp / 1.0
            t_diff = t_now - t_pdcp
            print(f"PDCP Indication tstamp {t_now} diff {t_diff} E2-node type {ind.id.type} nb_id {ind.id.nb_id.nb_id}")

class GTPCallback(ric.gtp_cb):
    def __init__(self):
        super().__init__()
    def handle(self, ind):
        if len(ind.gtp_stats) > 0:
            t_now = time.time_ns() / 1000.0
            t_gtp = ind.tstamp / 1.0
            t_diff = t_now - t_gtp
            print(f"GTP Indication tstamp {t_now} diff {t_diff} e2 node type {ind.id.type} nb_id {ind.id.nb_id.nb_id}")

class SliceCallback(ric.slice_cb):
    def __init__(self):
        super().__init__()
    def handle(self, ind):
        t_now = time.time_ns() / 1000.0
        t_slice = ind.tstamp / 1.0
        t_diff = t_now - t_slice
        print(f"Slice Indication tstamp {t_now} diff {t_diff} E2-node type {ind.id.type} nb_id {ind.id.nb_id.nb_id}")

class KPMCallback(ric.kpm_cb):
    def __init__(self):
        super().__init__()

    def handle(self, ind):
        if ind.hdr:
            t_now = time.time_ns() / 1000.0
            t_kpm = ind.hdr.kpm_ric_ind_hdr_format_1.collectStartTime / 1.0
            t_diff = t_now - t_kpm
            print(f"KPM Indication tstamp {t_now} diff {t_diff} E2-node type {ind.id.type} nb_id {ind.id.nb_id.nb_id}")
        
        # Uncomment below to enable KPM format printing

        if ind.msg.type == ric.FORMAT_1_INDICATION_MESSAGE:
            self._handle_kpm_format_1(ind.msg.frm_1)
        elif ind.msg.type == ric.FORMAT_3_INDICATION_MESSAGE:
            self._handle_kpm_format_3(ind.msg.frm_3)
        else:
            print(f"not implement KPM indication format {ind.msg.type}")

    def _handle_kpm_format_1(self, ind_frm1):
        print(f"ind_frm1.meas_data_lst_len {ind_frm1.meas_data_lst_len}")
        for index, meas_data in enumerate(ind_frm1.meas_data_lst):
            print(f"meas data idx {index}")
            if meas_data.incomplete_flag == ric.TRUE_ENUM_VALUE:
                print(f"<<< Measurement Record not reliable >>> ")
            if meas_data.meas_record_len == ind_frm1.meas_info_lst_len:
                for meas_record, meas_info in zip(meas_data.meas_record_lst, ind_frm1.meas_info_lst):
                    self._print_kpm_meas_record(meas_record, meas_info)
            else:
                print(f"meas_data.meas_record_len {meas_data.meas_record_len} != ind_frm1.meas_info_lst_len {ind_frm1.meas_info_lst_len}, cannot map value to name")
        print(f"ind_frm1.gran_period_ms {ind_frm1.gran_period_ms}")

    def _handle_kpm_format_3(self, frm_3):
        for ue_meas in frm_3.meas_report_per_ue:
            self._print_kpm_ue_id(ue_meas.ue_meas_report_lst)
            self._handle_kpm_format_1(ue_meas.ind_msg_format_1)

    def _print_kpm_meas_record(self, meas_record, meas_info):
        if meas_record.value == ric.INTEGER_MEAS_VALUE:
            print_value = meas_record.int_val
        elif meas_record.value == ric.REAL_MEAS_VALUE:
            print_value = meas_record.real_val
        elif meas_record.value == ric.NO_VALUE_MEAS_VALUE:
            print_value = "NoValue"
        else:
            print(f"unknown meas_record")
            return

        if meas_info.meas_type.type == ric.NAME_MEAS_TYPE:
            print_name_id = meas_info.meas_type.name
        elif meas_info.meas_type.type == ric.ID_MEAS_TYPE:
            print_name_id = meas_info.meas_type.id
        else:
            print(f"unknown meas info type")
            return
        
        print(f"Measurement name/id:value {print_name_id}:{print_value}")

    def _print_kpm_ue_id(self, ue):
        if ue.type == ric.GNB_UE_ID_E2SM:
            print(f"ue.gnb.amf_ue_ngap_id {ue.gnb.amf_ue_ngap_id}, "
                  f"ue.gnb.guami.plmn_id.mcc {ue.gnb.guami.plmn_id.mcc}, "
                  f"ue.gnb.guami.plmn_id.mnc {ue.gnb.guami.plmn_id.mnc}")
        elif ue.type == ric.GNB_DU_UE_ID_E2SM:
            print(f"ue.gnb_du.gnb_cu_ue_f1ap {ue.gnb_du.gnb_cu_ue_f1ap}")
        elif ue.type == ric.GNB_CU_UP_UE_ID_E2SM:
            print(f"ue.gnb_cu_up.gnb_cu_cp_ue_e1ap {ue.gnb_cu_up.gnb_cu_cp_ue_e1ap}")
        else:
            print("python3: not support ue_id_e2sm type")

# -----------------------------------------------------------------------------
# Main Application Class
# -----------------------------------------------------------------------------

class MoniXApp:
    def __init__(self, argv):
        ric.init(argv)
        
        self.shutdown_flag = False
        self.mac_hndlr = {}
        self.rlc_hndlr = {}
        self.pdcp_hndlr = {}
        self.gtp_hndlr = {}
        self.slice_hndlr = {}
        self.kpm_hndlr = {}
        
        # Keep callback objects alive
        self.mac_cbs = []
        self.rlc_cbs = []
        self.pdcp_cbs = []
        self.gtp_cbs = []
        self.slice_cbs = []
        self.kpm_cbs = []

        self.e2nodes_map = {}

        self.cust_oran = ric.get_sub_all_sm_conf(argv)
        self.cust_sm = self.cust_oran.cust
        self.oran_sm = self.cust_oran.oran
        
        signal.signal(signal.SIGINT, self._sig_handler)

    def _sig_handler(self, signum, frame):
        print("Ctrl-C Detected")
        self.shutdown_flag = True

    def _get_ngran_name(self, ran_type):
        return {
            0: "ngran_eNB", 2: "ngran_gNB",
            5: "ngran_gNB_CU", 7: "ngran_gNB_DU"
        }.get(ran_type, "Unknown")

    def _gen_id_key(self, node_id):
        plmn = "PLMN_" + str(node_id.plmn.mcc) + str(node_id.plmn.mnc)
        nb_id = "NBID_" + str(node_id.nb_id.nb_id)
        ran_type = self._get_ngran_name(node_id.type)
        return plmn + "-" + nb_id + "-" + ran_type

    def _get_tti(self, tti_ms):
        return {
            1: ric.Interval_ms_1, 2: ric.Interval_ms_2, 5: ric.Interval_ms_5,
            10: ric.Interval_ms_10, 100: ric.Interval_ms_100,
            500: ric.Interval_ms_500, 1000: ric.Interval_ms_1000
        }.get(tti_ms)

    def _send_subscription_req(self, node):
        for sm_info in self.cust_sm.sub_cust_sm:
            sm_name = sm_info.name.upper()
            tti = self._get_tti(sm_info.periodicity_ms)
            if tti is None:
                print(f"Unknown tti {sm_info.periodicity_ms}")
                continue

            print(f"<<<< Subscribe to {sm_name} with time period {sm_info.periodicity_ms} >>>>")
            key = self._gen_id_key(node.id)
            
            if sm_name == "MAC" and (node.id.type in [ric.e2ap_ngran_gNB, ric.e2ap_ngran_gNB_DU, ric.e2ap_ngran_eNB]):
                mac_cb = MACCallback()
                self.mac_cbs.append(mac_cb)
                hndlr = ric.report_mac_sm(node.id, tti, mac_cb)
                self.mac_hndlr.setdefault(key, []).append(hndlr)
            elif sm_name == "RLC" and (node.id.type in [ric.e2ap_ngran_gNB, ric.e2ap_ngran_gNB_DU, ric.e2ap_ngran_eNB]):
                rlc_cb = RLCCallback()
                self.rlc_cbs.append(rlc_cb)
                hndlr = ric.report_rlc_sm(node.id, tti, rlc_cb)
                self.rlc_hndlr.setdefault(key, []).append(hndlr)
            elif sm_name == "PDCP" and (node.id.type in [ric.e2ap_ngran_gNB, ric.e2ap_ngran_gNB_CU, ric.e2ap_ngran_eNB]):
                pdcp_cb = PDCPCallback()
                self.pdcp_cbs.append(pdcp_cb)
                hndlr = ric.report_pdcp_sm(node.id, tti, pdcp_cb)
                self.pdcp_hndlr.setdefault(key, []).append(hndlr)
            elif sm_name == "GTP" and (node.id.type in [ric.e2ap_ngran_gNB, ric.e2ap_ngran_gNB_CU, ric.e2ap_ngran_eNB]):
                gtp_cb = GTPCallback()
                self.gtp_cbs.append(gtp_cb)
                hndlr = ric.report_gtp_sm(node.id, tti, gtp_cb)
                self.gtp_hndlr.setdefault(key, []).append(hndlr)
            elif sm_name == "SLICE" and (node.id.type in [ric.e2ap_ngran_gNB, ric.e2ap_ngran_gNB_CU, ric.e2ap_ngran_eNB]):
                slice_cb = SliceCallback()
                self.slice_cbs.append(slice_cb)
                hndlr = ric.report_slice_sm(node.id, tti, slice_cb)
                self.slice_hndlr.setdefault(key, []).append(hndlr)
            else:
                print(f"Subscription for {sm_name} not implemented or invalid for this node type.")

        for sm_info in self.oran_sm.elm:
            if sm_info.name.upper() != "KPM":
                continue
            tti = self._get_tti(sm_info.periodicity_ms)
            if not tti:
                print(f"Unknown tti {sm_info.periodicity_ms}")
                continue
            
            if node.id.type != ric.e2ap_ngran_eNB and sm_info.ran_type == self._get_ngran_name(node.id.type):
                actions = [str(a.name) for a in sm_info.actions if a.name is not None]
                key = self._gen_id_key(node.id)
                kpm_cb = KPMCallback()
                self.kpm_cbs.append(kpm_cb)
                hndlr = ric.report_kpm_sm(node.id, tti, actions, kpm_cb)
                self.kpm_hndlr.setdefault(key, []).append(hndlr)

    def _unsubscribe_node(self, node_id):
        key_to_remove = self._gen_id_key(node_id)
        
        rm_funcs = {
            "MAC": ric.rm_report_mac_sm, "RLC": ric.rm_report_rlc_sm,
            "PDCP": ric.rm_report_pdcp_sm, "GTP": ric.rm_report_gtp_sm,
            "KPM": ric.rm_report_kpm_sm, "SLICE": ric.rm_report_slice_sm
        }

        hndlr_map = {
            "MAC": self.mac_hndlr, "RLC": self.rlc_hndlr, "PDCP": self.pdcp_hndlr,
            "GTP": self.gtp_hndlr, "KPM": self.kpm_hndlr, "SLICE": self.slice_hndlr
        }

        for sm_name, hndlr_dict in hndlr_map.items():
            if key_to_remove in hndlr_dict:
                for h in hndlr_dict[key_to_remove]:
                    rm_funcs[sm_name](h)
                del hndlr_dict[key_to_remove]

    def _print_e2_nodes(self):
        conn = ric.conn_e2_nodes()
        headers = ["idx", "nb_id", "mcc", "mnc", "ran_type"]
        e2nodes_data = [
            [i, node.id.nb_id.nb_id, node.id.plmn.mcc, node.id.plmn.mnc, self._get_ngran_name(node.id.type)]
            for i, node in enumerate(conn)
        ]
        print(tabulate(e2nodes_data, headers=headers, tablefmt="grid"))

    def _handle_node_changes(self):
        conn = ric.conn_e2_nodes()
        
        current_nodes_map = {}
        for i, node in enumerate(conn):
            plmn = "PLMN_" + str(node.id.plmn.mcc) + str(node.id.plmn.mnc)
            nbid = "NBID_" + str(node.id.nb_id.nb_id)
            ran_type = self._get_ngran_name(node.id.type)
            info = frozenset({nbid, plmn, ran_type})
            current_nodes_map[info] = node

        current_set = set(current_nodes_map.keys())
        previous_set = set(self.e2nodes_map.keys())

        new_sets = current_set - previous_set
        leave_sets = previous_set - current_set

        if not conn and not leave_sets:
            print("No E2 nodes connected. Waiting...")
            return

        if leave_sets:
            print("Left E2-Nodes: ", leave_sets)
            for info in leave_sets:
                node_to_remove = self.e2nodes_map[info]
                self._unsubscribe_node(node_to_remove.id)

        if new_sets:
            print("New E2-Nodes: ", new_sets)
            for info in new_sets:
                new_node = current_nodes_map[info]
                self._send_subscription_req(new_node)
        
        self.e2nodes_map = current_nodes_map
        
        if new_sets or leave_sets:
            print("Update connected E2 nodes")
            self._print_e2_nodes()

    def run(self):
        print("xApp running. Waiting for E2 nodes to connect...")
        while not self.shutdown_flag:
            self._handle_node_changes()
            time.sleep(1)
        
        self.stop()

    def stop(self):
        print("Deregistering subscriptions...")
        for node in self.e2nodes_map.values():
            self._unsubscribe_node(node.id)
        
        # Avoid deadlock. ToDo revise architecture
        while ric.try_stop == 0:
            time.sleep(1)

        print("xApp stopped")
        os._exit(0)

if __name__ == "__main__":
    app = MoniXApp(sys.argv)
    app.run()
