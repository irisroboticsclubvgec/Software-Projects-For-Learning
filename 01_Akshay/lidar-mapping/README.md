# Project 1: Obstacle Detection using Ultrasonic Sensor (HC-SR04)

## 1. Objective
Build a simple obstacle-detection system that continuously measures the
distance to the nearest object in front of an ultrasonic sensor and raises
a visual (LED) and audible (buzzer) alert when an obstacle comes within a
set threshold distance. This is the base building block for autonomous
navigation and collision-avoidance systems.

## 2. Hardware Used
| Component            | Qty | Notes                          |
|-----------------------|-----|---------------------------------|
| Arduino Uno            | 1   | Or any 5V Arduino board        |
| HC-SR04 Ultrasonic Sensor | 1 | Trig/Echo based ranging module |
| LED (any color)        | 1   | Visual warning indicator        |
| Buzzer (passive/active) | 1  | Audible warning indicator       |
| 220Ω resistor          | 1   | For LED current limiting        |
| Breadboard + jumper wires | — | For connections                |
| USB cable              | 1   | Programming + power             |

## 3. Software Used
- Arduino IDE (2.x or 1.8.x)
- Board package: **Arduino AVR Boards**
- No external libraries required (uses only built-in `pulseIn()`, `tone()`)

## 4. Circuit Diagram / Wiring

![Circuit diagram for obstacle detection](circuit_diagram.png)

**Connection Table**

| HC-SR04 Pin | Arduino Pin |
|-------------|-------------|
| VCC         | 5V          |
| GND         | GND         |
| TRIG        | D9          |
| ECHO        | D10         |

| Component | Arduino Pin |
|-----------|-------------|
| LED (+)   | D7 (via 220Ω resistor) |
| LED (-)   | GND |
| Buzzer (+)| D6 |
| Buzzer (-)| GND |

## 5. Working Principle
1. The Arduino sends a 10µs HIGH pulse on the `TRIG` pin, causing the
   HC-SR04 to emit an ultrasonic burst (40 kHz).
2. The sensor sets its `ECHO` pin HIGH for a duration equal to the time
   taken for the sound wave to travel to the obstacle and back.
3. `pulseIn()` measures this duration in microseconds.
4. Distance is calculated using the speed of sound (343 m/s):
   ```
   distance (cm) = (duration_us × 0.0343) / 2
   ```
   (divided by 2 because the pulse covers the round trip).
5. If the measured distance is less than or equal to the threshold
   (default 15 cm), the LED lights up and the buzzer sounds a warning
   tone. Otherwise, both stay off.
6. Readings are also printed to the Serial Monitor at 9600 baud for
   debugging/logging.

## 6. How to Run the Code
1. Open `obstacle_detection.ino` in the Arduino IDE.
2. Connect the Arduino Uno via USB and select:
   - **Tools > Board > Arduino Uno**
   - **Tools > Port > (your COM port)**
3. Wire the circuit as shown above.
4. Click **Upload**.
5. Open **Tools > Serial Monitor** (set baud rate to 9600) to view
   live distance readings.
6. Move an object closer than 15 cm to the sensor to trigger the
   LED and buzzer alert.

## 7. Results
- The system reliably detects obstacles within the HC-SR04's effective
  range (~2 cm to 400 cm).
- LED and buzzer activate consistently when an object is within the
  15 cm threshold.
- Serial Monitor shows real-time distance values, useful for
  calibration and demonstration.

## 8. Future Improvements
- Replace fixed threshold with a **user-adjustable potentiometer**.
- Add multiple sensors for **360° obstacle detection**.
- Integrate with a **motor driver** to make a robot stop/reverse
  automatically instead of just alerting.
- Send readings to a mobile app / IoT dashboard via Bluetooth or Wi-Fi
  (e.g., HC-05 or ESP32) for remote monitoring.
- Add a **median filter** on readings to reduce noise from false echoes.

## 9. Demo
- https://wokwi.com/projects/475136739584513025
