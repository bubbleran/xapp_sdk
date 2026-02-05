import sys
import argparse
import subprocess
import json
from ruamel.yaml import YAML
from pathlib import Path

def parse_args():
    parser = argparse.ArgumentParser(
        description="Update of a given xApp config YAML with Kubernetes-discovered RIC and DB IPs"
    )
    parser.add_argument(
        'config',
        type=Path,
        help='Path to the YAML config file to update'
    )
    parser.add_argument(
        '-n', '--namespace',
        nargs='+',
        default=['trirematics', 'monitoring'],
        help='Kubernetes namespace to search pods in'
    )
    parser.add_argument(
        '--skip-db',
        action='store_true',
        help='Skip database IP discovery even if a db section exists'
    )
    return parser.parse_args()


def kubectl_get_ips(namespace, label_selector):
    cmd = [
        'kubectl', 'get', 'pods', '-n', namespace,
        '-l', label_selector, '-o', 'json'
    ]
    try:
        out = subprocess.check_output(cmd)
    except subprocess.CalledProcessError as e:
        print(f"Error calling kubectl: {e}", file=sys.stderr)
        return []

    data = json.loads(out)
    results = []
    for item in data.get('items', []):
        labels = item.get('metadata', {}).get('labels', {})
        name = labels.get('athena.t9s.io/element-name') or item['metadata']['name']
        ip = item.get('status', {}).get('podIP')
        namespace = item.get('metadata', {}).get('namespace')
        if ip:
            results.append((name, ip, namespace, 'pod'))
    return results


def kubectl_get_svcs(namespace, label_selector):
    cmd = [
        'kubectl', 'get', 'services', '-n', namespace,
        '-l', label_selector, '-o', 'json'
    ]
    try:
        out = subprocess.check_output(cmd)
    except subprocess.CalledError as e:
        print(f"Error calling kubectl: {e}", file=sys.stderr)
        return []

    data = json.loads(out)
    results = []
    for item in data.get('items', []):
        name = item.get('metadata', {}).get('name')
        ip = item.get('spec', {}).get('clusterIP')
        namespace = item.get('metadata', {}).get('namespace')
        if ip:
            results.append((name, ip, namespace, 'svc'))
    return results


def choose_entry(entries, title):
    if not entries:
        print(f"No entries found for {title}.", file=sys.stderr)
        return None
    print(f"Select the {title} to configure:")
    for i, (name, ip, namespace, entry_type) in enumerate(entries, start=1):
        print(f"  {i}) {name} ({ip} - {namespace}, {entry_type})")
    choice = input(f"Choice [1-{len(entries)}]: ").strip()
    if not choice.isdigit() or not (1 <= int(choice) <= len(entries)):
        print("Invalid selection.", file=sys.stderr)
        return None
    return entries[int(choice) - 1]


def detect_local_ip():
    cmd = ['ip', 'route']
    try:
        out = subprocess.check_output(cmd, text=True)
    except subprocess.CalledError:
        return None
    for line in out.splitlines():
        if 'dev cilium_host' in line and 'src' in line:
            parts = line.split()
            if 'src' in parts:
                return parts[parts.index('src') + 1]
    return None


def update_yaml(config_path, ric_ip, local_ip, db_choice=None):
    yaml = YAML()
    yaml.preserve_quotes = True
    yaml.indent(mapping=4, sequence=4, offset=4)
    cfg = yaml.load(config_path)

    # RIC
    if 'xapp' in cfg:
        cfg['xapp']['ip_ric'] = ric_ip
    else:
        sys.exit("No 'xapp' section found in config.")

    # Local cluster IP
    if local_ip:
        cfg['xapp']['ip_xapp'] = local_ip
    else:
        print("Warning: could not determine local IP, skipping ip_xapp update.", file=sys.stderr)

    # DB
    db_ip = None
    if db_choice and 'db' in cfg['xapp']:
        db_name, db_ip, _, db_type = db_choice
        cfg['xapp']['db'] = {}  # Clear existing db section
        if 'mysql' in db_name:
            cfg['xapp']['db']['ip'] = db_ip
            cfg['xapp']['db']['dir'] = '/tmp/'
            cfg['xapp']['db']['usr'] = 'xapp'
            cfg['xapp']['db']['psw'] = 'BubbleRAN'
            cfg['xapp']['db']['filename'] = 'testdb'
        else:  # Assume VictoriaMetrics
            scenario = input("Enter the scenario name for VictoriaMetrics: ").strip().lower().replace(' ', '')
            cfg['xapp']['db']['ip'] = db_ip
            cfg['xapp']['db']['port'] = 8428
            cfg['xapp']['db']['filename'] = scenario

    with open(config_path, 'w') as f:
        yaml.dump(cfg, f)
    print(f"Config '{config_path}' updated: ip_ric={ric_ip}, ip_xapp={local_ip}" +
          (f", db.ip={db_ip}" if db_ip else ""))


def main():
    args = parse_args()

    if not args.config.is_file():
        sys.exit(f"Config file '{args.config}' not found.")

    ric_entries = []
    for namespace in args.namespace:
        ric_entries.extend(kubectl_get_ips(namespace, 'app.kubernetes.io/component=flexric'))

    ric_choice = choose_entry(ric_entries, 'RIC')
    if not ric_choice:
        sys.exit("RIC selection failed.")
    _, ric_ip, _, _ = ric_choice

    local_ip = detect_local_ip()

    db_choice = None
    if not args.skip_db and 'db' in YAML().load(args.config)['xapp']:
        db_entries = []
        for namespace in args.namespace:
            db_entries.extend(kubectl_get_ips(namespace, 'app.kubernetes.io/component=mysql-db'))
            db_entries.extend(kubectl_get_svcs(namespace, 'app.kubernetes.io/name=vmsingle'))

        db_choice = choose_entry(db_entries, 'Database')
        if not db_choice:
            print("Skipping database IP update.", file=sys.stderr)
        else:
            db_name, _, db_namespace, db_type = db_choice
            if db_namespace != 'trirematics':
                port = 3306 if 'mysql' in db_name else 8428
                target_name = f'svc/{db_name}' if db_type == 'svc' else db_name
                cmd = ['kubectl', 'port-forward', '-n', db_namespace, target_name, f'{port}:{port}']
                subprocess.Popen(cmd, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
                print(f"Port-forwarding enabled for {db_name} on port {port}.")
                db_choice = (db_name, "localhost", db_namespace, db_type)

    update_yaml(args.config, ric_ip, local_ip, db_choice)

if __name__ == '__main__':
    main()
