/*
  Project 1: Obstacle Detection using Ultrasonic Sensor (HC-SR04)
  Board   : Arduino Uno
  Author  : Akshay
  Description:
    Continuously measures distance to the nearest obstacle using an
    HC-SR04 ultrasonic sensor. If an obstacle is closer than a set
    threshold, an LED and buzzer are triggered as a warning.
*/

// ---------- Pin Definitions ----------
const int TRIG_PIN   = 9;
const int ECHO_PIN   = 10;
const int LED_PIN    = 7;
const int BUZZER_PIN = 6;

// ---------- Configuration ----------
const int THRESHOLD_CM   = 15;   // distance below which obstacle is "detected"
const unsigned long TIMEOUT_US = 25000UL; // ~4m max range timeout for pulseIn

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(TRIG_PIN, LOW);
  Serial.begin(9600);
  Serial.println("Obstacle Detection System Initialized");
}

long readDistanceCM() {
  // Send a 10us HIGH pulse to trigger the sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read echo pulse duration (microseconds)
  long duration = pulseIn(ECHO_PIN, HIGH, TIMEOUT_US);

  if (duration == 0) {
    return -1; // no echo received (out of range)
  }

  // Speed of sound = 343 m/s => 0.0343 cm/us; divide by 2 for round trip
  long distanceCM = duration * 0.0343 / 2;
  return distanceCM;
}

void loop() {
  long distance = readDistanceCM();

  if (distance == -1) {
    Serial.println("Out of range");
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
  } else {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance <= THRESHOLD_CM) {
      digitalWrite(LED_PIN, HIGH);
      tone(BUZZER_PIN, 1000); // 1kHz warning tone
    } else {
      digitalWrite(LED_PIN, LOW);
      noTone(BUZZER_PIN);
    }
  }

  delay(200); // ~5 readings per second
}
