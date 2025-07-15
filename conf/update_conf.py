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
        default='trirematics',
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
        if ip:
            results.append((name, ip))
    return results


def choose_entry(entries, title):
    if not entries:
        print(f"No entries found for {title}.", file=sys.stderr)
        return None, None
    print(f"Select the {title} to configure:")
    for i, (name, ip) in enumerate(entries, start=1):
        print(f"  {i}) {name} ({ip})")
    choice = input(f"Choice [1-{len(entries)}]: ").strip()
    if not choice.isdigit() or not (1 <= int(choice) <= len(entries)):
        print("Invalid selection.", file=sys.stderr)
        return None, None
    return entries[int(choice) - 1]


def detect_local_ip():
    cmd = ['ip', 'route']
    try:
        out = subprocess.check_output(cmd, text=True)
    except subprocess.CalledProcessError:
        return None
    for line in out.splitlines():
        if 'dev cilium_host' in line and 'src' in line:
            parts = line.split()
            if 'src' in parts:
                return parts[parts.index('src') + 1]
    return None


def update_yaml(config_path, ric_ip, local_ip, db_ip=None):
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
    if db_ip and 'db' in cfg['xapp']:
        cfg['xapp']['db']['ip'] = db_ip

    with open(config_path, 'w') as f:
        yaml.dump(cfg, f)
    print(f"Config '{config_path}' updated: ip_ric={ric_ip}, ip_xapp={local_ip}" +
          (f", db.ip={db_ip}" if db_ip else ""))


def main():
    args = parse_args()

    if not args.config.is_file():
        sys.exit(f"Config file '{args.config}' not found.")

    ric_entries = kubectl_get_ips(args.namespace, 'app.kubernetes.io/component=flexric')
    _, ric_ip = choose_entry(ric_entries, 'RIC')
    if not ric_ip:
        sys.exit("RIC selection failed.")

    local_ip = detect_local_ip()

    db_ip = None
    if not args.skip_db and 'db' in YAML().load(args.config)['xapp']:
        db_entries = kubectl_get_ips(args.namespace, 'app.kubernetes.io/component=mysql-db')
        _, db_ip = choose_entry(db_entries, 'Database')
        if not db_ip:
            print("Skipping database IP update.", file=sys.stderr)

    update_yaml(args.config, ric_ip, local_ip, db_ip)

if __name__ == '__main__':
    main()