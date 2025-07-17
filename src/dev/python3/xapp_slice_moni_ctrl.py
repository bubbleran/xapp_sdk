import time
import os
import json
import pdb
import csv
import sys
cur_dir = os.path.dirname(os.path.abspath(__file__))
# print("Current Directory:", cur_dir)
sdk_path = cur_dir + "/../xapp_sdk/"
sys.path.append(sdk_path)

import xapp_sdk as ric

####################
####  SLICE INDICATION MSG TO JSON
####################
assoc_rnti = 0
def slice_ind_to_dict_json(ind):

    slice_stats = {
        "RAN" : {
            "dl" : {},
            "ul" : {}
        },
        "UE" : {}
    }

    # RAN - dl
    dl_dict = slice_stats["RAN"]["dl"]
    if ind.slice_stats.dl.len_slices <= 0:
        dl_dict["num_of_slices"] = ind.slice_stats.dl.len_slices
        dl_dict["slice_sched_algo"] = "null"
        dl_dict["ue_sched_algo"] = ind.slice_stats.dl.sched_name[0]
    else:
        dl_dict["num_of_slices"] = ind.slice_stats.dl.len_slices
        dl_dict["slice_sched_algo"] = "null"
        dl_dict["slices"] = []
        slice_algo = ""
        for s in ind.slice_stats.dl.slices:
            if s.params.type == 1: # TODO: convert from int to string, ex: type = 1 -> STATIC
                slice_algo = "STATIC"
            elif s.params.type == 2:
                slice_algo = "NVS"
            elif s.params.type == 4:
                slice_algo = "EDF"
            elif s.params.type == 5:
                slice_algo = "EEDF"
            elif s.params.type == 6:
                slice_algo = "PR"
            else:
                slice_algo = "unknown"
            dl_dict.update({"slice_sched_algo" : slice_algo})

            slices_dict = {
                "index" : s.id,
                "label" : s.label[0],
                "ue_sched_algo" : s.sched[0],
            }
            if dl_dict["slice_sched_algo"] == "STATIC":
                slices_dict["slice_algo_params"] = {
                    "pos_low" : s.params.u.sta.pos_low,
                    "pos_high" : s.params.u.sta.pos_high
                }
            elif dl_dict["slice_sched_algo"] == "NVS":
                if s.params.u.nvs.conf == 0: # TODO: convert from int to string, ex: conf = 0 -> RATE
                    slices_dict["slice_algo_params"] = {
                        "type" : "RATE",
                        "mbps_rsvd" : s.params.u.nvs.u.rate.u1.mbps_required,
                        "mbps_ref" : s.params.u.nvs.u.rate.u2.mbps_reference
                    }
                elif s.params.u.nvs.conf == 1: # TODO: convert from int to string, ex: conf = 1 -> CAPACITY
                    slices_dict["slice_algo_params"] = {
                        "type" : "CAPACITY",
                        "pct_rsvd" : s.params.u.nvs.u.capacity.u.pct_reserved
                    }
                else:
                    slices_dict["slice_algo_params"] = {"type" : "unknown"}
            elif dl_dict["slice_sched_algo"] == "EDF":
                slices_dict["slice_algo_params"] = {
                    "deadline" : s.params.u.edf.deadline,
                    "guaranteed_prbs" : s.params.u.edf.guaranteed_prbs,
                    "max_replenish" : s.params.u.edf.max_replenish
                }
            elif dl_dict["slice_sched_algo"] == "EEDF":
                if s.params.u.eedf.conf == 0:
                    slices_dict["slice_algo_params"] = {
                        "type" : "SLICE_SM_EEDF_V0_STATIC",
                        "reserved_prbs" : s.params.u.eedf.u.fixed.reserved_prbs
                    }
                    if s.params.u.eedf.u.fixed.reserved_type == 0:
                        slices_dict["slice_algo_params"]["reserved_type"] = "EEDF_STATIC_HARD"
                    elif s.params.u.eedf.u.fixed.reserved_type == 1:
                        slices_dict["slice_algo_params"]["reserved_type"] = "EEDF_STATIC_SOFT"
                    else:
                        slices_dict["slice_algo_params"]["reserved_type"] = "unknown"
                elif s.params.u.eedf.conf == 1:
                    slices_dict["slice_algo_params"] = {
                        "type" : "SLICE_SM_EEDF_V0_RATE",
                        "deadline" : s.params.u.eedf.u.rate.deadline,
                        "guaranteed_rate" : s.params.u.eedf.u.rate.guaranteed_rate
                    }
                else:
                    slices_dict["slice_algo_params"] = {"type" : "unknown"}
            elif dl_dict["slice_sched_algo"] == "PR":
                slices_dict["slice_algo_params"] = {
                    "max_ratio" : s.params.u.pr.max_ratio,
                    "min_ratio" : s.params.u.pr.min_ratio,
                    "dedicated_ratio" : s.params.u.pr.dedicated_ratio
                }
            else:
                print("unknown slice algorithm, cannot handle params")
            dl_dict["slices"].append(slices_dict)

    # RAN - ul
    ul_dict = slice_stats["RAN"]["ul"]
    if ind.slice_stats.ul.len_slices <= 0:
        ul_dict["num_of_slices"] = ind.slice_stats.ul.len_slices
        ul_dict["slice_sched_algo"] = "null"
        ul_dict["ue_sched_algo"] = ind.slice_stats.ul.sched_name[0]
    else:
        ul_dict["num_of_slices"] = ind.slice_stats.ul.len_slices
        ul_dict["slice_sched_algo"] = "null"
        ul_dict["slices"] = []
        slice_algo = ""
        for s in ind.slice_stats.ul.slices:
            if s.params.type == 1: # TODO: convert from int to string, ex: type = 1 -> STATIC
                slice_algo = "STATIC"
            elif s.params.type == 2:
                slice_algo = "NVS"
            elif s.params.type == 4:
                slice_algo = "EDF"
            elif s.params.type == 5:
                slice_algo = "EEDF"
            elif s.params.type == 6:
                slice_algo = "PR"
            else:
                slice_algo = "unknown"
            ul_dict.update({"slice_sched_algo" : slice_algo})

            slices_dict = {
                "index" : s.id,
                "label" : s.label[0],
                "ue_sched_algo" : s.sched[0],
            }
            if ul_dict["slice_sched_algo"] == "STATIC":
                slices_dict["slice_algo_params"] = {
                    "pos_low" : s.params.u.sta.pos_low,
                    "pos_high" : s.params.u.sta.pos_high
                }
            elif ul_dict["slice_sched_algo"] == "NVS":
                if s.params.u.nvs.conf == 0: # TODO: convert from int to string, ex: conf = 0 -> RATE
                    slices_dict["slice_algo_params"] = {
                        "type" : "RATE",
                        "mbps_rsvd" : s.params.u.nvs.u.rate.u1.mbps_required,
                        "mbps_ref" : s.params.u.nvs.u.rate.u2.mbps_reference
                    }
                elif s.params.u.nvs.conf == 1: # TODO: convert from int to string, ex: conf = 1 -> CAPACITY
                    slices_dict["slice_algo_params"] = {
                        "type" : "CAPACITY",
                        "pct_rsvd" : s.params.u.nvs.u.capacity.u.pct_reserved
                    }
                else:
                    slices_dict["slice_algo_params"] = {"type" : "unknown"}
            elif ul_dict["slice_sched_algo"] == "EDF":
                slices_dict["slice_algo_params"] = {
                    "deadline" : s.params.u.edf.deadline,
                    "guaranteed_prbs" : s.params.u.edf.guaranteed_prbs,
                    "max_replenish" : s.params.u.edf.max_replenish
                }
            elif ul_dict["slice_sched_algo"] == "EEDF":
                if s.params.u.eedf.conf == 0:
                    slices_dict["slice_algo_params"] = {
                        "type" : "SLICE_SM_EEDF_V0_STATIC",
                        "reserved_prbs" : s.params.u.eedf.u.fixed.reserved_prbs
                    }
                    if s.params.u.eedf.u.fixed.reserved_type == 0:
                        slices_dict["slice_algo_params"]["reserved_type"] = "EEDF_STATIC_HARD"
                    elif s.params.u.eedf.u.fixed.reserved_type == 1:
                        slices_dict["slice_algo_params"]["reserved_type"] = "EEDF_STATIC_SOFT"
                    else:
                        slices_dict["slice_algo_params"]["reserved_type"] = "unknown"
                elif s.params.u.eedf.conf == 1:
                    slices_dict["slice_algo_params"] = {
                        "type" : "SLICE_SM_EEDF_V0_RATE",
                        "deadline" : s.params.u.eedf.u.rate.deadline,
                        "guaranteed_rate" : s.params.u.eedf.u.rate.guaranteed_rate
                    }
                else:
                    slices_dict["slice_algo_params"] = {"type" : "unknown"}
            elif ul_dict["slice_sched_algo"] == "PR":
                slices_dict["slice_algo_params"] = {
                    "max_ratio" : s.params.u.pr.max_ratio,
                    "min_ratio" : s.params.u.pr.min_ratio,
                    "dedicated_ratio" : s.params.u.pr.dedicated_ratio
                }
            else:
                print("unknown slice algorithm, cannot handle params")
            ul_dict["slices"].append(slices_dict)

    # UE
    global assoc_rnti
    ue_dict = slice_stats["UE"]
    if ind.ue_slice_stats.len_ue_slice <= 0:
        ue_dict["num_of_ues"] = ind.ue_slice_stats.len_ue_slice
    else:
        ue_dict["num_of_ues"] = ind.ue_slice_stats.len_ue_slice
        ue_dict["ues"] = []
        for u in ind.ue_slice_stats.ues:
            ues_dict = {}
            dl_id = "null"
            ul_id = "null"
            if u.dl_id >= 0 and dl_dict["num_of_slices"] > 0:
                dl_id = u.dl_id
            if u.ul_id >= 0 and ul_dict["num_of_slices"] > 0:
                ul_id = u.ul_id
            ues_dict = {
                "rnti" : hex(u.rnti),
                "assoc_dl_slice_id" : dl_id,
                "assoc_ul_slice_id" : ul_id
            }
            ue_dict["ues"].append(ues_dict)
            assoc_rnti = u.rnti

    ind_dict = slice_stats
    ind_json = json.dumps(ind_dict)

    with open("rt_slice_stats.json", "w") as outfile:
        outfile.write(ind_json)
    # print(ind_dict)

    return json

####################
#### SLICE INDICATION CALLBACK
####################

class SLICECallback(ric.slice_cb):
    # Define Python class 'constructor'
    def __init__(self):
        # Call C++ base class constructor
        ric.slice_cb.__init__(self)
    # Override C++ method: virtual void handle(swig_slice_ind_msg_t a) = 0;
    def handle(self, ind):
        # Print swig_slice_ind_msg_t
        # if (ind.slice_stats.dl.len_slices > 0):
        #     print('SLICE Indication tstamp = ' + str(ind.tstamp))
        #     print('SLICE STATE: len_slices = ' + str(ind.slice_stats.dl.len_slices))
        #     print('SLICE STATE: sched_name = ' + str(ind.slice_stats.dl.sched_name[0]))
        # if (ind.ue_slice_stats.len_ue_slice > 0):
        #    print('UE ASSOC SLICE STATE: len_ue_slice = ' + str(ind.ue_slice_stats.len_ue_slice))
        slice_ind_to_dict_json(ind)

####################
####  SLICE CONTROL FUNCS
####################
def create_slice(slice_params, slice_sched_algo):
    s = ric.fr_slice_t()
    s.id = slice_params["id"]
    s.label = slice_params["label"]
    s.len_label = len(slice_params["label"])
    s.sched = slice_params["ue_sched_algo"]
    s.len_sched = len(slice_params["ue_sched_algo"])
    if slice_sched_algo == "STATIC":
        s.params.type = ric.SLICE_ALG_SM_V0_STATIC
        s.params.u.sta.pos_low = slice_params["slice_algo_params"]["pos_low"]
        s.params.u.sta.pos_high = slice_params["slice_algo_params"]["pos_high"]
    elif slice_sched_algo == "NVS":
        s.params.type = ric.SLICE_ALG_SM_V0_NVS
        if slice_params["type"] == "SLICE_SM_NVS_V0_RATE":
            s.params.u.nvs.conf = ric.SLICE_SM_NVS_V0_RATE
            s.params.u.nvs.u.rate.u1.mbps_required = slice_params["slice_algo_params"]["mbps_rsvd"]
            s.params.u.nvs.u.rate.u2.mbps_reference = slice_params["slice_algo_params"]["mbps_ref"]
            # print("ADD NVS DL SLCIE: id", s.id,
            # ", conf", s.params.u.nvs.conf,
            # ", mbps_rsrv", s.params.u.nvs.u.rate.u1.mbps_required,
            # ", mbps_ref", s.params.u.nvs.u.rate.u2.mbps_reference)
        elif slice_params["type"] == "SLICE_SM_NVS_V0_CAPACITY":
            s.params.u.nvs.conf = ric.SLICE_SM_NVS_V0_CAPACITY
            s.params.u.nvs.u.capacity.u.pct_reserved = slice_params["slice_algo_params"]["pct_rsvd"]
            # print("ADD NVS DL SLCIE: id", s.id,
            # ", conf", s.params.u.nvs.conf,
            # ", pct_rsvd", s.params.u.nvs.u.capacity.u.pct_reserved)
        else:
            print("Unkown NVS conf")
    elif slice_sched_algo == "EDF":
        s.params.type = ric.SLICE_ALG_SM_V0_EDF
        s.params.u.edf.deadline = slice_params["slice_algo_params"]["deadline"]
        s.params.u.edf.guaranteed_prbs = slice_params["slice_algo_params"]["guaranteed_prbs"]
        s.params.u.edf.max_replenish = slice_params["slice_algo_params"]["max_replenish"]
    elif slice_sched_algo == "EEDF":
        s.params.type = ric.SLICE_ALG_SM_V0_EEDF
        if slice_params["type"] == "SLICE_SM_EEDF_V0_STATIC":
            s.params.u.eedf.conf = ric.SLICE_SM_EEDF_V0_STATIC
            s.params.u.eedf.u.fixed.reserved_prbs = slice_params["slice_algo_params"]["reserved_prbs"]
            if slice_params["slice_algo_params"]["reserved_type"] == "EEDF_STATIC_HARD":
                s.params.u.eedf.u.fixed.reserved_type = ric.EEDF_STATIC_HARD
            elif slice_params["slice_algo_params"]["reserved_type"] == "EEDF_STATIC_SOFT":
                s.params.u.eedf.u.fixed.reserved_type = ric.EEDF_STATIC_SOFT
            else:
                print("Unkown EEDF STATIC Type")
        elif slice_params["type"] == "SLICE_SM_EEDF_V0_RATE":
            s.params.u.eedf.conf = ric.SLICE_SM_EEDF_V0_RATE
            s.params.u.eedf.u.rate.deadline = slice_params["slice_algo_params"]["deadline"]
            s.params.u.eedf.u.rate.guaranteed_rate = slice_params["slice_algo_params"]["guaranteed_rate"]
        else:
            print("Unkown EEDF conf")
    elif slice_sched_algo == "PR":
        s.params.type = ric.SLICE_ALG_SM_V0_PR
        s.params.u.pr.max_ratio = slice_params["slice_algo_params"]["max_ratio"]
        s.params.u.pr.min_ratio = slice_params["slice_algo_params"]["min_ratio"]
        s.params.u.pr.dedicated_ratio = slice_params["slice_algo_params"]["dedicated_ratio"]
    else:
        print("Unkown slice algo type")


    return s

####################
####  SLICE CONTROL PARAMETER EXAMPLE - ADD SLICE
####################
add_static_slices = {
    "num_slices" : 3,
    "slice_sched_algo" : "STATIC",
    "slices" : [
        {
            "id" : 0,
            "label" : "s1",
            "ue_sched_algo" : "PF", # ue_sched_algo can be "RR"(round-robin), "PF"(proportional fair) or "MT"(maximum throughput) and it has to be set in any len_slices
            "slice_algo_params" : {"pos_low" : 0, "pos_high" : 2},
        },
        {
            "id" : 2,
            "label" : "s2",
            "ue_sched_algo" : "PF",
            "slice_algo_params" : {"pos_low" : 3, "pos_high" : 10},
        },
        {
            "id" : 5,
            "label" : "s3",
            "ue_sched_algo" : "PF",
            "slice_algo_params" : {"pos_low" : 11, "pos_high" : 13},
        }
    ]
}

add_nvs_slices_rate = {
    "num_slices" : 2,
    "slice_sched_algo" : "NVS",
    "slices" : [
        {
            "id" : 0,
            "label" : "s1",
            "ue_sched_algo" : "PF",
            "type" : "SLICE_SM_NVS_V0_RATE",
            "slice_algo_params" : {"mbps_rsvd" : 60, "mbps_ref" : 120},
        },
        {
            "id" : 2,
            "label" : "s2",
            "ue_sched_algo" : "PF",
            "type" : "SLICE_SM_NVS_V0_RATE",
            "slice_algo_params" : {"mbps_rsvd" : 60, "mbps_ref" : 120},
        }
    ]
}

add_nvs_slices_cap = {
    "num_slices" : 2,
    "slice_sched_algo" : "NVS",
    "slices" : [
        {
            "id" : 0,
            "label" : "s1",
            "ue_sched_algo" : "PF",
            "type" : "SLICE_SM_NVS_V0_CAPACITY",
            "slice_algo_params" : {"pct_rsvd" : 0.5},
        },
        {
            "id" : 2,
            "label" : "s2",
            "ue_sched_algo" : "PF",
            "type" : "SLICE_SM_NVS_V0_CAPACITY",
            "slice_algo_params" : {"pct_rsvd" : 0.5},
        }
    ]
}

add_nvs_slices = {
    "num_slices" : 3,
    "slice_sched_algo" : "NVS",
    "slices" : [
        {
            "id" : 0,
            "label" : "s1",
            "ue_sched_algo" : "PF",
            "type" : "SLICE_SM_NVS_V0_CAPACITY",
            "slice_algo_params" : {"pct_rsvd" : 0.65},
        },
        {
            "id" : 2,
            "label" : "s2",
            "ue_sched_algo" : "PF",
            "type" : "SLICE_SM_NVS_V0_RATE",
            "slice_algo_params" : {"mbps_rsvd" : 25, "mbps_ref" : 100},
        },
        {
            "id" : 5,
            "label" : "s3",
            "ue_sched_algo" : "PF",
            "type" : "SLICE_SM_NVS_V0_RATE",
            "slice_algo_params" : {"mbps_rsvd" : 5, "mbps_ref" : 100},
        }
    ]
}

add_edf_slices = {
    "num_slices" : 3,
    "slice_sched_algo" : "EDF",
    "slices" : [
        {
            "id" : 0,
            "label" : "s1",
            "ue_sched_algo" : "PF",
            "slice_algo_params" : {"deadline" : 10, "guaranteed_prbs" : 80, "max_replenish" : 0},
        },
        {
            "id" : 2,
            "label" : "s2",
            "ue_sched_algo" : "PF",
            "slice_algo_params" : {"deadline" : 20, "guaranteed_prbs" : 50, "max_replenish" : 0},
        },
        {
            "id" : 5,
            "label" : "s3",
            "ue_sched_algo" : "PF",
            "slice_algo_params" : {"deadline" : 40, "guaranteed_prbs" : 10, "max_replenish" : 0},
        }
    ]
}

add_eedf_slices = {
    "num_slices" : 3,
    "slice_sched_algo" : "EEDF",
    "slices" : [
        {
            "id" : 0,
            "label" : "s1",
            "ue_sched_algo" : "PF",
            "type" : "SLICE_SM_EEDF_V0_STATIC",
            "slice_algo_params" : {"reserved_type" : "EEDF_STATIC_HARD", "reserved_prbs" : 30},
        },
        {
            "id" : 1,
            "label" : "s2",
            "ue_sched_algo" : "PF",
            "type" : "SLICE_SM_EEDF_V0_STATIC",
            "slice_algo_params" : {"reserved_type" : "EEDF_STATIC_SOFT", "reserved_prbs" : 40},
        },
        {
            "id" : 2,
            "label" : "s3",
            "ue_sched_algo" : "PF",
            "type" : "SLICE_SM_EEDF_V0_RATE",
            "slice_algo_params" : {"deadline" : 10, "guaranteed_rate" : 40},
        }
    ]
}

add_pr_slices = {
    "num_slices" : 3,
    "slice_sched_algo" : "PR",
    "slices" : [
        {
            "id" : 0,
            "label" : "s1",
            "ue_sched_algo" : "PF",
            "slice_algo_params" : {"max_ratio" : 100, "min_ratio" : 0, "dedicated_ratio" : 0},
        },
        {
            "id" : 1,
            "label" : "s2",
            "ue_sched_algo" : "PF",
            "slice_algo_params" : {"max_ratio" : 20, "min_ratio" : 20, "dedicated_ratio" : 20},
        },
        {
            "id" : 2,
            "label" : "s3",
            "ue_sched_algo" : "PF",
            "slice_algo_params" : {"max_ratio" : 40, "min_ratio" : 20, "dedicated_ratio" : 0},
        }
    ]
}

reset_slices = {
    "num_slices" : 0
}

####################
####  SLICE CONTROL PARAMETER EXAMPLE - DELETE SLICE
####################
delete_slices = {
    "num_dl_slices" : 1,
    "delete_dl_slice_id" : [2],
    "num_ul_slices" : 0,
    "delete_ul_slice_id" : [2]
}

####################
####  SLICE CONTROL PARAMETER EXAMPLE - ASSOC UE SLICE
####################
assoc_ue_slice = {
    "num_ues" : 1,
    "ues" : [
        {
            "rnti" : assoc_rnti, # TODO: get rnti from slice_ind_to_dict_json()
            "assoc_dl_slice_id" : 2, # if set to -1, gNB will not perform DL slice association.
            "assoc_ul_slice_id" : -1  # if set to -1, gNB will not perform UL slice association.
        }
    ]
}


def fill_slice_ctrl_msg(ctrl_type, ctrl_msg):
    msg = ric.slice_ctrl_msg_t()
    if (ctrl_type == "ADDMOD"):
        msg.type = ric.SLICE_CTRL_SM_V0_ADD
        dl = ric.ul_dl_slice_conf_t()
        ul = ric.ul_dl_slice_conf_t()

        # DL SLICE CTRL ADD
        if "dl_conf" in ctrl_msg:
            dl_conf = ctrl_msg["dl_conf"]
            slice_sched_algo = "NULL"
            if "slice_sched_algo" in dl_conf:
                slice_sched_algo = dl_conf["slice_sched_algo"]
            dl.sched_name = slice_sched_algo
            dl.len_sched_name = len(slice_sched_algo)

            dl.len_slices = dl_conf["num_slices"]
            slices = ric.slice_array(dl_conf["num_slices"])
            for i in range(0, dl_conf["num_slices"]):
                slices[i] = create_slice(dl_conf["slices"][i], dl_conf["slice_sched_algo"])

            dl.slices = slices
            msg.u.add_mod_slice.dl = dl
        
        # UL SLICE CTRL ADD
        if "ul_conf" in ctrl_msg:
            ul_conf = ctrl_msg["ul_conf"]
            slice_sched_algo = "NULL"
            if "slice_sched_algo" in ul_conf:
                slice_sched_algo = ul_conf["slice_sched_algo"]
            ul.sched_name = slice_sched_algo
            ul.len_sched_name = len(slice_sched_algo)

            ul.len_slices = ul_conf["num_slices"]
            slices = ric.slice_array(ul_conf["num_slices"])
            for i in range(0, ul_conf["num_slices"]):
                slices[i] = create_slice(ul_conf["slices"][i], ul_conf["slice_sched_algo"])
                
            ul.slices = slices
            msg.u.add_mod_slice.ul = ul
        
    elif (ctrl_type == "DEL"):
        msg.type = ric.SLICE_CTRL_SM_V0_DEL

        # DL SLCIE CTRL DEL
        msg.u.del_slice.len_dl = ctrl_msg["num_dl_slices"]
        del_dl_id = ric.del_dl_array(ctrl_msg["num_dl_slices"])
        for i in range(ctrl_msg["num_dl_slices"]):
            del_dl_id[i] = ctrl_msg["delete_dl_slice_id"][i]
        # print("DEL DL SLICE: id", del_dl_id)
        msg.u.del_slice.dl = del_dl_id

        # UL SLCIE CTRL DEL
        msg.u.del_slice.len_ul = ctrl_msg["num_ul_slices"]
        del_ul_id = ric.del_ul_array(ctrl_msg["num_ul_slices"])
        for i in range(ctrl_msg["num_ul_slices"]):
            del_ul_id[i] = ctrl_msg["delete_ul_slice_id"][i]
        # print("DEL UL SLICE: id", del_ul_id)
        msg.u.del_slice.ul = del_ul_id

    elif (ctrl_type == "ASSOC_UE_SLICE"):
        msg.type = ric.SLICE_CTRL_SM_V0_UE_SLICE_ASSOC

        msg.u.ue_slice.len_ue_slice = ctrl_msg["num_ues"]
        assoc = ric.ue_slice_assoc_array(ctrl_msg["num_ues"])
        for i in range(ctrl_msg["num_ues"]):
            a = ric.ue_slice_assoc_t()
            a.rnti = ctrl_msg["ues"][i]["rnti"] # TODO: assign the rnti after get the indication msg from slice_ind_to_dict_json()
            a.dl_id = ctrl_msg["ues"][i]["assoc_dl_slice_id"]
            a.ul_id = ctrl_msg["ues"][i]["assoc_ul_slice_id"]
            assoc[i] = a
            # print("ASSOC DL SLICE: <rnti:", a.rnti, "(NEED TO FIX)>, id", a.dl_id, a.ul_id)
        msg.u.ue_slice.ues = assoc

    return msg


####################
####  GENERAL
####################

ric.init(sys.argv)

conn = ric.conn_e2_nodes()
assert(len(conn) > 0)

node_idx = -1
for i in range(0, len(conn)):
    if (conn[i].id.type == ric.e2ap_ngran_gNB or conn[i].id.type == ric.e2ap_ngran_gNB_DU):
        # Assuming this xApp only support 1 node
        node_idx = i
        break
assert(node_idx > -1 and "Node type should be DU or gNB")

#for i in range(0, len(conn)):
#    if conn[i].id.plmn.mcc == 1:
#        node_idx = i

#print("Global E2 Node [" + str(node_idx) + "]: PLMN MCC = " + str(conn[node_idx].id.plmn.mcc))
#print("Global E2 Node [" + str(node_idx) + "]: PLMN MNC = " + str(conn[node_idx].id.plmn.mnc))

####################
#### SLICE INDICATION
####################

slice_cb = SLICECallback()
hndlr = ric.report_slice_sm(conn[node_idx].id, ric.Interval_ms_1000, slice_cb)
time.sleep(5)

####################
####  SLICE CTRL ADD
####################

ul_dl_conf = {
    "dl_conf": add_pr_slices,
    #"ul_conf": add_nvs_slices_cap
}

msg = fill_slice_ctrl_msg("ADDMOD", ul_dl_conf)
ric.control_slice_sm(conn[node_idx].id, msg)
time.sleep(5)

####################
####  SLICE CTRL ASSOC
####################
while(assoc_rnti == 0):
    time.sleep(1)
assoc_ue_slice["ues"][0]["rnti"] = assoc_rnti
assoc_ue_slice["ues"][0]["assoc_dl_slice_id"] = 2
msg = fill_slice_ctrl_msg("ASSOC_UE_SLICE", assoc_ue_slice)
ric.control_slice_sm(conn[node_idx].id, msg)
time.sleep(5)

####################
####  SLICE CTRL ADD
####################

ul_dl_conf = {
    "dl_conf": add_eedf_slices,
    #"ul_conf": add_nvs_slices_cap
}

msg = fill_slice_ctrl_msg("ADDMOD", ul_dl_conf)
ric.control_slice_sm(conn[node_idx].id, msg)
time.sleep(5)

####################
####  SLICE CTRL ASSOC
####################
while(assoc_rnti == 0):
    time.sleep(1)
assoc_ue_slice["ues"][0]["rnti"] = assoc_rnti
assoc_ue_slice["ues"][0]["assoc_dl_slice_id"] = 2
msg = fill_slice_ctrl_msg("ASSOC_UE_SLICE", assoc_ue_slice)
ric.control_slice_sm(conn[node_idx].id, msg)
time.sleep(5)

####################
####  SLICE CTRL ADD
####################

ul_dl_conf = {
    "dl_conf": add_edf_slices,
    #"ul_conf": add_nvs_slices_cap
}

msg = fill_slice_ctrl_msg("ADDMOD", ul_dl_conf)
ric.control_slice_sm(conn[node_idx].id, msg)
time.sleep(5)

####################
####  SLICE CTRL ASSOC
####################
while(assoc_rnti == 0):
    time.sleep(1)
assoc_ue_slice["ues"][0]["rnti"] = assoc_rnti
assoc_ue_slice["ues"][0]["assoc_dl_slice_id"] = 2
msg = fill_slice_ctrl_msg("ASSOC_UE_SLICE", assoc_ue_slice)
ric.control_slice_sm(conn[node_idx].id, msg)
time.sleep(5)

####################
####  SLICE CTRL ADD
####################

ul_dl_conf = {
    "dl_conf": add_nvs_slices,
    #"ul_conf": add_nvs_slices_cap
}

msg = fill_slice_ctrl_msg("ADDMOD", ul_dl_conf)
ric.control_slice_sm(conn[node_idx].id, msg)
time.sleep(5)

####################
####  SLICE CTRL ASSOC
####################
while(assoc_rnti == 0):
    time.sleep(1)
assoc_ue_slice["ues"][0]["rnti"] = assoc_rnti
assoc_ue_slice["ues"][0]["assoc_dl_slice_id"] = 2
msg = fill_slice_ctrl_msg("ASSOC_UE_SLICE", assoc_ue_slice)
ric.control_slice_sm(conn[node_idx].id, msg)
time.sleep(5)

####################
####  SLICE CTRL DEL
####################

msg = fill_slice_ctrl_msg("DEL", delete_slices)
ric.control_slice_sm(conn[node_idx].id, msg)
time.sleep(5)

####################
####  SLICE CTRL RESET
####################

ul_dl_conf = {
    "dl_conf": reset_slices,
    #"ul_conf": reset_slices
}

msg = fill_slice_ctrl_msg("ADDMOD", ul_dl_conf)
ric.control_slice_sm(conn[node_idx].id, msg)
time.sleep(5)

with open("rt_slice_stats.json", "w") as outfile:
    outfile.write(json.dumps({}))

### End
ric.rm_report_slice_sm(hndlr)

# Avoid deadlock. ToDo revise architecture 
while ric.try_stop == 0:
    time.sleep(1)

print('Test finished' )

