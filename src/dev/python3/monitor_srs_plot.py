import os
import time
import argparse
import numpy as np
import matplotlib.pyplot as plt


POLL_INTERVAL_SEC = 0.2
INT_SCALE = 1.0

NUM_ANTENNAS = 4

# Show only the latest N seconds on the plots
PLOT_WINDOW_SEC = 20.0

# Keep a little extra history outside the visible window
HISTORY_MARGIN_SEC = 5.0


# ============================================================
# Load file: timestamp I Q
# ============================================================

def load_iq_txt(path, scale=1.0):
    if not os.path.isfile(path) or os.path.getsize(path) == 0:
        return None, None

    try:
        data = np.loadtxt(path, dtype=np.float64)
    except (OSError, ValueError):
        return None, None

    if data.size == 0:
        return None, None

    # Single sample
    if data.ndim == 1:
        if data.shape[0] < 3:
            return None, None

        ts = np.array(
            [int(data[0])],
            dtype=np.int64
        )

        iq = np.array(
            [data[1] + 1j * data[2]],
            dtype=np.complex64
        ) * scale

        return ts, iq

    # Multiple samples
    if data.ndim == 2 and data.shape[1] >= 3:
        ts = data[:, 0].astype(np.int64)

        I = data[:, 1] * scale
        Q = data[:, 2] * scale

        iq = (I + 1j * Q).astype(np.complex64)

        return ts, iq

    return None, None


# ============================================================
# CIR computation
# ============================================================

def compute_cir_from_est(H_freq):
    H_unshift = np.fft.ifftshift(H_freq)
    return np.fft.ifft(H_unshift)


# ============================================================
# Rough SNR
# ============================================================

def rough_snr_from_rx(rx, noise):
    if rx is None or noise is None:
        return None

    p_rx = np.mean(np.abs(rx) ** 2)
    p_noise = np.mean(np.abs(noise) ** 2) + 1e-12

    return 10 * np.log10(
        p_rx / p_noise + 1e-12
    )


# ============================================================
# Remove old samples
# ============================================================

def trim_history(time_list, value_list, min_time):
    while time_list and time_list[0] < min_time:
        time_list.pop(0)
        value_list.pop(0)


# ============================================================
# Real-time SRS monitoring
# ============================================================

def monitor_srs(nbid, ueid, input_dir, symbol=0):
    input_dir = os.path.abspath(input_dir)

    print("[INFO] Monitoring SRS")
    print(f"[INFO] NBID: {nbid}")
    print(f"[INFO] UEID: {ueid}")
    print(f"[INFO] Antennas: 0-{NUM_ANTENNAS - 1}")
    print(f"[INFO] Symbol: {symbol}")
    print(f"[INFO] Input directory: {input_dir}")
    print(f"[INFO] Plot window: {PLOT_WINDOW_SEC} sec")
    print()

    # ========================================================
    # Build filenames for all antennas
    # ========================================================

    files = {}

    for ant in range(NUM_ANTENNAS):
        files[ant] = {
            "rx": os.path.join(
                input_dir,
                f"iq_srs_rx_ant{ant}_symbol{symbol}_"
                f"nbid{nbid}_ueid{ueid}.txt"
            ),

            "noise": os.path.join(
                input_dir,
                f"iq_srs_noise_ant{ant}_symbol{symbol}_"
                f"nbid{nbid}_ueid{ueid}.txt"
            ),

            "est": os.path.join(
                input_dir,
                f"iq_srs_estimated_ant{ant}_symbol{symbol}_"
                f"nbid{nbid}_ueid{ueid}.txt"
            ),
        }

    for ant in range(NUM_ANTENNAS):
        print(f"[ANT {ant}]")
        print(f"  RX:    {files[ant]['rx']}")
        print(f"  Noise: {files[ant]['noise']}")
        print(f"  EST:   {files[ant]['est']}")

    print()

    plt.ion()

    # ========================================================
    # FIGURE 1 — SNR
    # ========================================================

    fig1, ax1 = plt.subplots()

    fig1.canvas.manager.set_window_title(
        f"NBID {nbid} UEID {ueid} - SNR"
    )

    ax1.set_title(
        f"NBID {nbid} UEID {ueid} - SNR"
    )

    ax1.set_xlabel("Time (sec)")
    ax1.set_ylabel("SNR (dB)")
    ax1.grid(True)

    snr_lines = {}
    snr_time = {}
    snr_values = {}

    for ant in range(NUM_ANTENNAS):
        line, = ax1.plot(
            [],
            [],
            label=f"Antenna {ant}"
        )

        snr_lines[ant] = line
        snr_time[ant] = []
        snr_values[ant] = []

    ax1.legend()

    # ========================================================
    # FIGURE 2 — CIR Peak
    # ========================================================

    fig2, ax2 = plt.subplots()

    fig2.canvas.manager.set_window_title(
        f"NBID {nbid} UEID {ueid} - CIR Peak"
    )

    ax2.set_title(
        f"NBID {nbid} UEID {ueid} - CIR Peak"
    )

    ax2.set_xlabel("Time (sec)")
    ax2.set_ylabel("Peak |h[n]|")
    ax2.grid(True)

    cir_lines = {}
    cir_time = {}
    cir_values = {}

    for ant in range(NUM_ANTENNAS):
        line, = ax2.plot(
            [],
            [],
            label=f"Antenna {ant}"
        )

        cir_lines[ant] = line
        cir_time[ant] = []
        cir_values[ant] = []

    ax2.legend()

    # ========================================================
    # Time reference
    # ========================================================

    start_ts = None

    # Last processed timestamp per antenna
    last_ts = {
        ant: None
        for ant in range(NUM_ANTENNAS)
    }

    # ========================================================
    # Monitoring loop
    # ========================================================

    while True:

        updated = False

        for ant in range(NUM_ANTENNAS):

            # ------------------------------------------------
            # Load data
            # ------------------------------------------------

            rx_ts, rx = load_iq_txt(
                files[ant]["rx"],
                INT_SCALE
            )

            noise_ts, noise = load_iq_txt(
                files[ant]["noise"],
                INT_SCALE
            )

            est_ts, H_est = load_iq_txt(
                files[ant]["est"],
                INT_SCALE
            )

            # Estimated channel is required
            if H_est is None or est_ts is None:
                continue

            current_ts = est_ts[0]

            # ------------------------------------------------
            # Skip duplicate data
            # ------------------------------------------------

            if last_ts[ant] == current_ts:
                continue

            last_ts[ant] = current_ts

            # ------------------------------------------------
            # Establish global time reference
            # ------------------------------------------------

            if start_ts is None:
                start_ts = current_ts

                print(
                    f"[INFO] First timestamp: {start_ts}"
                )

            # ------------------------------------------------
            # Convert timestamp to relative seconds
            #
            # This assumes the timestamp is in microseconds.
            # If your timestamp is nanoseconds, change 1e6
            # to 1e9.
            # ------------------------------------------------

            t_sec = (
                current_ts - start_ts
            ) / 1e6

            # =================================================
            # SNR
            # =================================================

            snr_db = rough_snr_from_rx(
                rx,
                noise
            )

            snr_time[ant].append(t_sec)

            snr_values[ant].append(
                snr_db
                if snr_db is not None
                else np.nan
            )

            # =================================================
            # CIR
            # =================================================

            h_td = compute_cir_from_est(
                H_est
            )

            peak_val = np.max(
                np.abs(h_td)
            )

            cir_time[ant].append(t_sec)
            cir_values[ant].append(peak_val)

            # =================================================
            # Remove old samples
            # =================================================

            history_start = (
                t_sec
                - PLOT_WINDOW_SEC
                - HISTORY_MARGIN_SEC
            )

            trim_history(
                snr_time[ant],
                snr_values[ant],
                history_start
            )

            trim_history(
                cir_time[ant],
                cir_values[ant],
                history_start
            )

            # =================================================
            # Update line data
            # =================================================

            snr_lines[ant].set_data(
                snr_time[ant],
                snr_values[ant]
            )

            cir_lines[ant].set_data(
                cir_time[ant],
                cir_values[ant]
            )

            # =================================================
            # Logging
            # =================================================

            snr_str = (
                f"{snr_db:.2f} dB"
                if snr_db is not None
                else "N/A"
            )

            cir_str = f"{peak_val:.3f}"

            print(
                f"[t={t_sec:.3f}s] "
                f"ANT={ant} | "
                f"SNR={snr_str} | "
                f"CIR peak={cir_str}"
            )

            updated = True

        # =====================================================
        # Update plots
        # =====================================================

        if updated:

            # Get latest timestamp among all antennas
            latest_time = max(
                (
                    times[-1]
                    for times in snr_time.values()
                    if times
                ),
                default=0.0
            )

            # -------------------------------------------------
            # Moving x-axis
            # -------------------------------------------------

            if latest_time < PLOT_WINDOW_SEC:
                x_min = 0.0
                x_max = PLOT_WINDOW_SEC
            else:
                x_min = (
                    latest_time
                    - PLOT_WINDOW_SEC
                )

                x_max = latest_time

            # =================================================
            # SNR plot
            # =================================================

            ax1.set_xlim(
                x_min,
                x_max
            )

            # Autoscale Y only
            ax1.relim()

            ax1.autoscale_view(
                scalex=False,
                scaley=True
            )

            fig1.canvas.draw_idle()
            fig1.canvas.flush_events()

            # =================================================
            # CIR plot
            # =================================================

            ax2.set_xlim(
                x_min,
                x_max
            )

            # Autoscale Y only
            ax2.relim()

            ax2.autoscale_view(
                scalex=False,
                scaley=True
            )

            fig2.canvas.draw_idle()
            fig2.canvas.flush_events()

        time.sleep(POLL_INTERVAL_SEC)


# ============================================================
# Main
# ============================================================

def main():
    parser = argparse.ArgumentParser(
        description="Real-time SRS IQ monitoring"
    )

    parser.add_argument(
        "nbid",
        help="E2 Node NBID"
    )

    parser.add_argument(
        "ueid",
        help="UE ID"
    )

    parser.add_argument(
        "input_dir",
        help="Directory containing SRS IQ files"
    )

    parser.add_argument(
        "--symbol",
        type=int,
        default=0,
        help="SRS symbol index (default: 0)"
    )

    args = parser.parse_args()

    if not os.path.isdir(args.input_dir):
        parser.error(
            f"Input directory does not exist: "
            f"{args.input_dir}"
        )

    try:
        monitor_srs(
            nbid=args.nbid,
            ueid=args.ueid,
            input_dir=args.input_dir,
            symbol=args.symbol
        )

    except KeyboardInterrupt:
        print("\n[INFO] Monitoring stopped.")


if __name__ == "__main__":
    main()
