#!/usr/bin/env bash

set -u

# =========================
# Configurable parameters
# =========================

BUILD_DIR="./build"
CONF_DIR="./conf"
LOG_DIR="./test-all-xapp-logs"
SLEEP_BETWEEN_XAPPS=5
XAPP_TIMEOUT=60

RIC_IP="127.0.0.1"
XAPP_IP="127.0.0.1"

timestamp() {
  date +"%Y%m%d_%H%M%S"
}

echo_info() {
  echo -e "\033[1;34m[INFO]\033[0m $1"
}

echo_error() {
  echo -e "\033[1;31m[ERROR]\033[0m $1"
}

usage() {
  echo "Usage: $0 [-r ric_ip] [-x xapp_ip] {oai|amr|ocudu}"
  echo ""
  echo "Options:"
  echo "  -r ric_ip   IP of the FlexRIC nearRT-RIC (ip_ric), default: $RIC_IP"
  echo "  -x xapp_ip  IP the xApp binds its SCTP client to (ip_xapp), default: $XAPP_IP"
  echo "  -h          Show this help"
  echo ""
  echo "Run from the xapp_sdk root folder after building into $BUILD_DIR."
  echo ""
  echo "Examples:"
  echo "  $0 oai"
  echo "  $0 -r 10.0.2.10 -x 10.0.2.1 amr"
  echo "  $0 -r 192.168.70.150 -x 192.168.70.1 ocudu"
}

is_ipv4() {
  [[ "$1" =~ ^([0-9]{1,3}\.){3}[0-9]{1,3}$ ]]
}

# =========================
# Read input
# =========================

while getopts ":r:x:h" opt; do
  case "$opt" in
    r) RIC_IP="$OPTARG" ;;
    x) XAPP_IP="$OPTARG" ;;
    h) usage; exit 0 ;;
    :) echo_error "Option -$OPTARG requires an argument."; usage; exit 1 ;;
    *) echo_error "Unknown option: -$OPTARG"; usage; exit 1 ;;
  esac
done
shift $((OPTIND - 1))

if [[ $# -ne 1 ]]; then
  echo_error "Missing test target."
  usage
  exit 1
fi

TARGET="$1"

for ip in "$RIC_IP" "$XAPP_IP"; do
  if ! is_ipv4 "$ip"; then
    echo_error "Invalid IPv4 address: $ip"
    exit 1
  fi
done

# =========================
# xApp list
# Format:
# "xapp_type" "xapp_binary config_file timeout [extra args]"
# config_file is relative to CONF_DIR; it is copied and patched with RIC_IP / XAPP_IP
# =========================

DEV_C="$BUILD_DIR/src/dev/c"
DEV_PY="$BUILD_DIR/src/dev/python3"
USR_C="$BUILD_DIR/src/usr/c"
USR_PY="$BUILD_DIR/src/usr/python3"

XAPPS_FOR_OAI=(
# dev C
  "c $DEV_C/xapp_all_moni xapp_all_sm.yaml 10" # stop by ctrl+c
  "c $DEV_C/xapp_cust_moni xapp_cust_sm.yaml 20" # stop by runtime_sec
  "c $DEV_C/xapp_cust_moni_simple xapp.yaml 15"
  "c $DEV_C/xapp_oran_kpm_moni xapp_oran_sm_oai.yaml 20" # stop by runtime_sec
  "c $DEV_C/xapp_oran_rc_moni_rrc xapp.yaml 15" # stop by ctrl+c
  "c $DEV_C/xapp_oran_llc_moni_srs xapp.yaml 60"
  "c $DEV_C/xapp_oran_ccc_slice_moni_ctrl xapp.yaml 20"
  "c $DEV_C/xapp_oran_rc_slice_ctrl xapp.yaml 10"
  "c $DEV_C/xapp_oran_rc_slice_delete xapp.yaml 10"
#  "c $DEV_C/xapp_oran_rc_handover_ctrl xapp.yaml 10"

# dev Python
#  "py $DEV_PY/xapp_all_moni.py xapp_all_sm.yaml 10" # stop by ctrl+c
#  "py $DEV_PY/xapp_cust_moni.py xapp_cust_sm.yaml 10" # stop by ctrl+c
#  "py $DEV_PY/xapp_oran_moni.py xapp_oran_sm_oai.yaml 10" # stop by ctrl+c

# usr C (note: only work for single UE scenario)
  "c $USR_C/xapp_sdk_moni xapp.yaml 5"
  "c $USR_C/xapp_sdk_moni_cb xapp.yaml 5"
  "c $USR_C/xapp_sdk_moni_slice xapp.yaml 65" # this causes the quectel disconnect
  "c $USR_C/xapp_sdk_moni_ue xapp.yaml 5"
  "c $USR_C/xapp_sdk_moni_ue_cb xapp.yaml 15"
  "c $USR_C/xapp_sdk_moni_rrc xapp.yaml 15"
  "c $USR_C/xapp_slice_sdk xapp.yaml 10"
#  "c $USR_C/xapp_ho_sdk xapp.yaml 5"

# usr Python (note: only work for single UE scenario)
  "py $USR_PY/mntr.py xapp.yaml 5"
  "py $USR_PY/mntr_cb.py xapp.yaml 10"
  "py $USR_PY/mntr_ue.py xapp.yaml 5"
  "py $USR_PY/mntr_ue_cb.py xapp.yaml 10"
  "py $USR_PY/mntr_cb_rrc.py xapp.yaml 15"
  "py $USR_PY/slicing.py xapp.yaml 5"
#  "py $USR_PY/ho.py xapp.yaml 5"
)

XAPPS_FOR_OCUDU=(
# dev C
  "c $DEV_C/xapp_oran_kpm_moni xapp_oran_sm_ocudu.yaml 20" # stop by runtime_sec

# dev Python
#  "py $DEV_PY/xapp_oran_moni.py xapp_oran_sm_ocudu.yaml 10" # stop by ctrl+c

# usr C (note: only work for single UE scenario)
  "c $USR_C/xapp_sdk_moni xapp.yaml 10"
  "c $USR_C/xapp_sdk_moni_cb xapp.yaml 10"
  "c $USR_C/xapp_sdk_moni_ue xapp.yaml 10"
  "c $USR_C/xapp_sdk_moni_ue_cb xapp.yaml 15"

# usr Python (note: only work for single UE scenario)
  "py $USR_PY/mntr.py xapp.yaml 10"
  "py $USR_PY/mntr_cb.py xapp.yaml 10"
  "py $USR_PY/mntr_ue.py xapp.yaml 10"
  "py $USR_PY/mntr_ue_cb.py xapp.yaml 10"
)

XAPPS_FOR_AMR=(
# dev C
  "c $DEV_C/xapp_oran_kpm_moni xapp_oran_sm_amr.yaml 15"
  "c $DEV_C/xapp_oran_ccc_bwp_ctrl xapp.yaml 10 1 0 20" # configure downlink (1) BWP by specifying start RB from 0 and allocate 20 RBs
  "c $DEV_C/xapp_oran_ccc_bwp_ctrl xapp.yaml 10 2 3 25" # configure uplink (2) BWP by specifying start RB from 3 and allocate 25 RBs
  "c $DEV_C/xapp_oran_llc_moni_srs xapp.yaml 20"
#  "c $DEV_C/xapp_oran_rc_handover_ctrl xapp.yaml 10"

# dev Python
  "py $DEV_PY/xapp_oran_moni.py xapp_oran_sm_amr.yaml 10" # stop by ctrl+c

# usr C (note: only work for single UE scenario)
  "c $USR_C/xapp_sdk_moni xapp.yaml 10"
  "c $USR_C/xapp_sdk_moni_cb xapp.yaml 10"
  "c $USR_C/xapp_sdk_moni_ue xapp.yaml 10"
  "c $USR_C/xapp_sdk_moni_ue_cb xapp.yaml 15"
  "c $USR_C/xapp_bwp_sdk xapp.yaml 10"
#  "c $USR_C/xapp_ho_sdk xapp.yaml 5"

# usr Python (note: only work for single UE scenario)
  "py $USR_PY/mntr.py xapp.yaml 10"
  "py $USR_PY/mntr_cb.py xapp.yaml 10"
  "py $USR_PY/mntr_ue.py xapp.yaml 10"
  "py $USR_PY/mntr_ue_cb.py xapp.yaml 10"
  "py $USR_PY/bwp.py xapp.yaml 10"
#  "py $USR_PY/ho.py xapp.yaml 5"
)

# =========================
# Select xApp array based on input
# =========================

case "$TARGET" in
  oai)
    echo_info "Selected target: OAI"
    XAPPS=("${XAPPS_FOR_OAI[@]}")
    ;;

  amr|amari|amarisoft)
    echo_info "Selected target: AMR / Amarisoft"
    XAPPS=("${XAPPS_FOR_AMR[@]}")
    ;;

  ocudu)
    echo_info "Selected target: OCUDU"
    XAPPS=("${XAPPS_FOR_OCUDU[@]}")
    ;;

  *)
    echo_error "Unknown target: $TARGET"
    usage
    exit 1
    ;;
esac

if [[ ${#XAPPS[@]} -eq 0 ]]; then
  echo_error "No xApps configured for target: $TARGET"
  exit 1
fi

echo_info "nearRT-RIC IP (ip_ric): $RIC_IP"
echo_info "xApp IP (ip_xapp): $XAPP_IP"
echo_info "Number of xApps to test: ${#XAPPS[@]}"

# =========================
# Generate config files with the given IPs
# =========================

RUN_CONF_DIR="$LOG_DIR/conf_${TARGET}_$(timestamp)"
mkdir -p "$RUN_CONF_DIR"

for cfg in "$CONF_DIR"/*.yaml; do
  sed -E \
    -e "s/^([[:space:]]*ip_ric:).*/\1 $RIC_IP/" \
    -e "s/^([[:space:]]*ip_xapp:).*/\1 $XAPP_IP/" \
    "$cfg" > "$RUN_CONF_DIR/$(basename "$cfg")"
done

echo_info "Generated configs under: $RUN_CONF_DIR"

# =========================
# Check nearRT-RIC / gNB / UE manually
# =========================

echo_info "Please make sure the nearRT-RIC is running at $RIC_IP and the gNB and UE are connected to it."
read -rp "Press Enter to start xApp E2E test..."

# =========================
# Run xApps one by one
# =========================

FAILED_XAPPS=()

for entry in "${XAPPS[@]}"; do
  # Split entry into array fields
  read -r -a FIELDS <<< "$entry"

  XAPP_TYPE="${FIELDS[0]}"
  XAPP_BIN="${FIELDS[1]}"
  XAPP_CFG="$RUN_CONF_DIR/${FIELDS[2]}"
  CURRENT_TIMEOUT="${FIELDS[3]:-}"

  # Everything after timeout is treated as optional extra args
  XAPP_EXTRA_ARGS=("${FIELDS[@]:4}")

  # Use global default if timeout is not provided
  if [[ -z "$CURRENT_TIMEOUT" ]]; then
    CURRENT_TIMEOUT="$XAPP_TIMEOUT"
  fi

  XAPP_NAME=$(basename "$XAPP_BIN")
  XAPP_LOG="$LOG_DIR/${TARGET}_${XAPP_NAME}_$(timestamp).log"

  echo_info "========================================"
  echo_info "Running xApp: $XAPP_NAME"
  echo_info "Log: $XAPP_LOG"

  if [[ ! -f "$XAPP_BIN" ]]; then
    echo_error "xApp file not found: $XAPP_BIN"
    FAILED_XAPPS+=("$XAPP_NAME")
    continue
  fi

  if [[ "$XAPP_TYPE" == "c" && ! -x "$XAPP_BIN" ]]; then
    echo_error "C xApp binary not executable: $XAPP_BIN"
    FAILED_XAPPS+=("$XAPP_NAME")
    continue
  fi

  if [[ ! -f "$XAPP_CFG" ]]; then
    echo_error "Config file not found: $XAPP_CFG"
    FAILED_XAPPS+=("$XAPP_NAME")
    continue
  fi

  case "$XAPP_TYPE" in
    c)
      echo_info "Running Command Line: timeout --kill-after=5s ${CURRENT_TIMEOUT}s $XAPP_BIN $XAPP_CFG ${XAPP_EXTRA_ARGS[*]}"
      timeout --kill-after=5s "${CURRENT_TIMEOUT}s" "$XAPP_BIN" "$XAPP_CFG" "${XAPP_EXTRA_ARGS[@]}" > "$XAPP_LOG" 2>&1
      RET=$?
      ;;

    python|py)
      echo_info "Running Command Line: timeout --kill-after=5s ${CURRENT_TIMEOUT}s python3 -u $XAPP_BIN $XAPP_CFG ${XAPP_EXTRA_ARGS[*]}"
      timeout --kill-after=5s "${CURRENT_TIMEOUT}s" python3 -u "$XAPP_BIN" "$XAPP_CFG" "${XAPP_EXTRA_ARGS[@]}" > "$XAPP_LOG" 2>&1
      RET=$?
      ;;

    *)
      echo_error "Unknown xApp type: $XAPP_TYPE"
      FAILED_XAPPS+=("$XAPP_NAME")
      continue
      ;;
  esac

  if [[ $RET -eq 0 ]]; then
    echo_info "xApp finished successfully: $XAPP_NAME"
  elif [[ $RET -eq 124 ]]; then
      if grep -q "Test xApp run SUCCESSFULLY" "$XAPP_LOG"; then
        echo_info "xApp ran for ${CURRENT_TIMEOUT}s and stopped cleanly: $XAPP_NAME"
      else
        echo_error "xApp timed out after ${CURRENT_TIMEOUT}s: $XAPP_NAME"
        FAILED_XAPPS+=("$XAPP_NAME")
      fi
  else
    echo_error "xApp failed with exit code $RET: $XAPP_NAME"
    FAILED_XAPPS+=("$XAPP_NAME")
  fi

  echo_info "Waiting ${SLEEP_BETWEEN_XAPPS}s before next xApp..."
  sleep "$SLEEP_BETWEEN_XAPPS"
done

# =========================
# Summary
# =========================

echo_info "========================================"
echo_info "E2E xApp test finished."
echo_info "Target: $TARGET"
echo_info "nearRT-RIC IP: $RIC_IP, xApp IP: $XAPP_IP"

if [[ ${#FAILED_XAPPS[@]} -eq 0 ]]; then
  echo_info "All xApps finished successfully."
else
  echo_error "Some xApps failed:"
  for xapp in "${FAILED_XAPPS[@]}"; do
    echo "  - $xapp"
  done
fi

echo_info "Logs are saved under: $LOG_DIR"
