import time
import os
import sys
import signal
# from tabulate import tabulate

cur_dir = os.path.dirname(os.path.abspath(__file__))
sdk_path = cur_dir + "/../xapp_sdk/"
sys.path.append(sdk_path)

import xapp_sdk as ric

# -----------------------------------------------------------------------------
# Callbacks
# -----------------------------------------------------------------------------

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
        self.kpm_hndlr = {}

        self.kpm_cbs = []

        self.e2nodes_map = {}
        self.oran_sm = ric.get_sub_oran_sm_conf(argv)

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
        for sm_info in self.oran_sm.elm:
            if sm_info.name.upper() != "KPM":
                continue
            tti = self._get_tti(sm_info.periodicity_ms)
            if tti is None:
                print(f"Unknown tti {sm_info.periodicity_ms}")
                continue

            if node.id.type != ric.e2ap_ngran_eNB and sm_info.ran_type == self._get_ngran_name(node.id.type):
                actions = [str(a.name) for a in sm_info.actions if a.name is not None]
                key = self._gen_id_key(node.id)

                print(f"<<<< Subscribe to KPM with time period {sm_info.periodicity_ms} >>>>")

                kpm_cb = KPMCallback()
                self.kpm_cbs.append(kpm_cb)

                hndlr = ric.report_kpm_sm(node.id, tti, actions, kpm_cb)
                self.kpm_hndlr.setdefault(key, []).append(hndlr)

    def _unsubscribe_node(self, node_id):
        key_to_remove = self._gen_id_key(node_id)

        if key_to_remove in self.kpm_hndlr:
            for h in self.kpm_hndlr[key_to_remove]:
                ric.rm_report_kpm_sm(h)
            del self.kpm_hndlr[key_to_remove]

    # def _print_e2_nodes(self):
    #     conn = ric.conn_e2_nodes()
    #     headers = ["idx", "nb_id", "mcc", "mnc", "ran_type"]
    #     e2nodes_data = [
    #         [i, node.id.nb_id.nb_id, node.id.plmn.mcc, node.id.plmn.mnc, self._get_ngran_name(node.id.type)]
    #         for i, node in enumerate(conn)
    #     ]
    #     print(tabulate(e2nodes_data, headers=headers, tablefmt="grid"))

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
            #self._print_e2_nodes()

    def run(self):
        print("xApp running. Waiting for E2 nodes to connect...")
        start_time = time.time()
        timeout = self.oran_sm.runtime_sec

        while not self.shutdown_flag:
            self._handle_node_changes()

            if timeout > 0 and (time.time() - start_time) > timeout:
                print(f"Timeout of {timeout} seconds reached.")
                break

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
