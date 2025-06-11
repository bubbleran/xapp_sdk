#!/usr/bin/env bash
set -euo pipefail

# Default namespace and config file
NAMESPACE="trirematics"
CONF_FILE="default.conf"

# Parse options
usage() {
  echo "Usage: $0 [-c <config-file>]" >&2
  exit 1
}

while getopts ":c:" opt; do
  case $opt in
    c)
      CONF_FILE="$OPTARG"
      ;;
    *)
      usage
      ;;
  esac
done

# Validate config file
if [[ ! -f "$CONF_FILE" ]]; then
  echo "Config file '$CONF_FILE' not found." >&2
  exit 1
fi

# 1) Gather all FlexRIC pods with their element-name and IP
mapfile -t RIC_ENTRIES < <(kubectl get pods -n "$NAMESPACE" \
  -l app.kubernetes.io/component=flexric \
  -o jsonpath='{range .items[*]}{.metadata.labels.athena\.t9s\.io\/element-name}{"="}{.status.podIP}{"\n"}{end}')

if [[ ${#RIC_ENTRIES[@]} -eq 0 ]]; then
  echo "No FlexRIC pods found in namespace '$NAMESPACE'."
  exit 1
fi

echo "Select the RIC to configure (enter number):"
for i in "${!RIC_ENTRIES[@]}"; do
  entry="${RIC_ENTRIES[$i]}"
  name="${entry%%=*}"
  ip="${entry##*=}"
  printf "  %d) %s (%s)\n" "$((i+1))" "$name" "$ip"
done

read -rp "Choice [1-${#RIC_ENTRIES[@]}]: " choice

if ! [[ "$choice" =~ ^[0-9]+$ ]] || (( choice < 1 || choice > ${#RIC_ENTRIES[@]} )); then
  echo "Invalid selection." >&2
  exit 1
fi



SELECTED_ENTRY="${RIC_ENTRIES[$((choice-1))]}"
SELECTED_RIC_NAME="${SELECTED_ENTRY%%=*}"
SELECTED_RIC_IP="${SELECTED_ENTRY##*=}"

echo "Selected RIC: $SELECTED_RIC_NAME with IP $SELECTED_RIC_IP"

# 2) Determine local IP to reach that pod
# Use ip route get and awk without backslash issues
LOCAL_IP=$(ip route | awk '/dev cilium_host/ { for(i=1;i<=NF;i++) if($i=="src") { print $(i+1); exit } }')

if [[ -z "$LOCAL_IP" ]]; then
  echo "WARNING: could not determine local source IP from cilium_host route" >&2
  exit 1
fi

echo "Local IP for xApp: $LOCAL_IP"



# 3) Optionally update Database if block exists
if grep -q '^[[:space:]]*Database' "$CONF_FILE"; then
  # Gather all MySQL DB pods with their element-name and IP
  mapfile -t DB_ENTRIES < <(kubectl get pods -n "$NAMESPACE" \
    -l app.kubernetes.io/component=mysql-db \
    -o jsonpath='{range .items[*]}{.metadata.labels.athena\.t9s\.io\/element-name}{"="}{.status.podIP}{"\n"}{end}')

  if [[ ${#DB_ENTRIES[@]} -eq 0 ]]; then
    echo "Warning: No MySQL DB pods found. Skipping database IP update." >&2
    SKIP_DB=1
  else
    echo "Select the Database to configure (enter number):"
    for i in "${!DB_ENTRIES[@]}"; do
      entry="${DB_ENTRIES[$i]}"
      name="${entry%%=*}"
      ip="${entry##*=}"
      printf "  %d) %s (%s)\n" "$((i+1))" "$name" "$ip"
    done

    read -rp "Choice [1-${#DB_ENTRIES[@]}]: " db_choice

    if ! [[ "$db_choice" =~ ^[0-9]+$ ]] || (( db_choice < 1 || db_choice > ${#DB_ENTRIES[@]} )); then
      echo "Invalid selection. Skipping database IP update." >&2
      SKIP_DB=1
    else
      SELECTED_DB_ENTRY="${DB_ENTRIES[$((db_choice-1))]}"
      SELECTED_DB_IP="${SELECTED_DB_ENTRY##*=}"
      SKIP_DB=0
      echo "Selected Database IP: $SELECTED_DB_IP"
    fi
  fi
else
  SKIP_DB=1
fi

# 4) Update the config file

sed -i "/^NearRT_RIC/,/^}/ s/^[[:space:]]*ip = \".*\"/    ip = \"$SELECTED_RIC_IP\"/" "$CONF_FILE"

sed -i "/^xApp/,/^}/ s/^[[:space:]]*ip = \".*\"/    ip = \"$LOCAL_IP\"/" "$CONF_FILE"

#   - Database block, if applicable
if [[ ${SKIP_DB:-1} -eq 0 ]]; then
  sed -i '/^[[:space:]]*Database = {/,/^[[:space:]]*}/ s/^[[:space:]]*ip = ".*"/        ip = "'"$SELECTED_DB_IP"'"/' "$CONF_FILE"
fi

 echo "Config file '$CONF_FILE' updated successfully."


