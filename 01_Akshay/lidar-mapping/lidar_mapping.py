"""
lidar_mapping.py
Reads live 360-degree scan data from an RPLiDAR A1 (A1M8) and plots a
real-time 2D point-cloud map of the surrounding environment.

Hardware:
    RPLiDAR A1 (A1M8) connected via its USB adapter board.

Requirements:
    pip install rplidar-roboticia matplotlib numpy

Usage:
    python lidar_mapping.py COM5        (Windows)
    python lidar_mapping.py /dev/ttyUSB0  (Linux/Mac/Raspberry Pi)
"""

import sys
import numpy as np
import matplotlib.pyplot as plt
from rplidar import RPLidar

PORT = sys.argv[1] if len(sys.argv) > 1 else "COM5"
MAX_DISTANCE_MM = 6000  # RPLiDAR A1 typical usable range ~6-12 m indoors


def main():
    lidar = RPLidar(PORT)

    plt.ion()
    fig, ax = plt.subplots(subplot_kw={"projection": "polar"})
    ax.set_theta_zero_location("N")
    ax.set_theta_direction(-1)
    ax.set_rmax(MAX_DISTANCE_MM / 1000)  # meters
    scatter = ax.scatter([], [], s=4)

    print(f"Connecting to RPLiDAR on {PORT} ...")
    info = lidar.get_info()
    print("Device info:", info)

    health = lidar.get_health()
    print("Health status:", health)

    try:
        for scan in lidar.iter_scans():
            # Each scan is a list of (quality, angle_deg, distance_mm) tuples
            angles = np.radians([point[1] for point in scan])
            distances = np.array([point[2] for point in scan]) / 1000.0  # -> meters

            scatter.set_offsets(np.c_[angles, distances])
            ax.set_title("RPLiDAR A1 - Live 2D Map")
            plt.pause(0.01)

    except KeyboardInterrupt:
        print("\nStopped by user.")
    finally:
        lidar.stop()
        lidar.stop_motor()
        lidar.disconnect()


if __name__ == "__main__":
    main()