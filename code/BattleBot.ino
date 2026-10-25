/*
 * BATTLE-BOT - Arduino Prototype
 * Low-cost autonomous safety and inspection robot for hazardous area monitoring.
 * 
 * Features:
 * - Ultrasonic sensor (HC-SR04) for obstacle/distance detection
 * - Photoresistor (LDR) for light level / visibility sensing
 * - Multi-color LED alerts (Red/Yellow/Green)
 * - Buzzer for audio alerts
 * - Serial monitoring for status and data logging
 *
 * Hardware Connections (Arduino Uno):
 * - Ultrasonic Trigger: D9
 * - Ultrasonic Echo:    D10
 * - LDR (with 10k pull-down): A0
 * - LED Red:    D11
 * - LED Yellow: D12
 * - LED Green:  D13
 * - Buzzer:     D8
 *
 * Team: Mohana Priya D, Jayajeevee S S, Krishna Priya D
 * College: Sri Sairam Engineering College, Chennai
 * Wadhwani Foundation Venture
 */

// Pin definitions
const int TRIG_PIN = 9;
const int ECHO_PIN = 10;
const int LDR_PIN = A0;
const int LED_RED = 11;
const int LED_YELLOW = 12;
const int LED_GREEN = 13;
const int BUZZER = 8;

// Thresholds (tunable)
const int OBSTACLE_DISTANCE_CM = 20;   // Alert if object closer than this
const int WARNING_DISTANCE_CM = 40;    // Warning zone
const int LOW_LIGHT_THRESHOLD = 400;   // Below this = poor visibility / dark

// Timing
unsigned long lastReadTime = 0;
const unsigned long READ_INTERVAL = 200; // ms

void setup() {
  Serial.begin(9600);
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  
  // Initial state - all off
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(BUZZER, LOW);
  
  Serial.println("========================================");
  Serial.println("  BATTLE-BOT Safety Monitoring System");
  Serial.println("  Initializing sensors...");
  Serial.println("========================================");
  delay(1000);
  Serial.println("System Ready. Monitoring area...");
  Serial.println("Distance(cm) | LightLevel | Status");
  Serial.println("----------------------------------------");
}

void loop() {
  unsigned long currentTime = millis();
  
  if (currentTime - lastReadTime >= READ_INTERVAL) {
    lastReadTime = currentTime;
    
    // Read sensors
    long distance = getDistance();
    int lightLevel = analogRead(LDR_PIN);
    
    // Determine status and alerts
    String status = "CLEAR";
    bool alert = false;
    bool warning = false;
    
    // Reset LEDs and buzzer
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(BUZZER, LOW);
    
    if (distance > 0 && distance < OBSTACLE_DISTANCE_CM) {
      // Critical obstacle
      status = "OBSTACLE DETECTED";
      digitalWrite(LED_RED, HIGH);
      digitalWrite(BUZZER, HIGH);
      alert = true;
    } else if (distance > 0 && distance < WARNING_DISTANCE_CM) {
      // Warning zone
      status = "WARNING - CLOSE OBJECT";
      digitalWrite(LED_YELLOW, HIGH);
      warning = true;
    } else {
      // Clear
      digitalWrite(LED_GREEN, HIGH);
    }
    
    // Check light level (poor visibility)
    if (lightLevel < LOW_LIGHT_THRESHOLD) {
      status += " | LOW VISIBILITY";
      // Flash yellow if not already in alert
      if (!alert) {
        digitalWrite(LED_YELLOW, HIGH);
      }
    }
    
    // Serial output for monitoring / data logging
    Serial.print(distance);
    Serial.print(" cm | ");
    Serial.print(lightLevel);
    Serial.print(" | ");
    Serial.println(status);
    
    // Short beep pattern for alert
    if (alert) {
      delay(100);
      digitalWrite(BUZZER, LOW);
      delay(100);
    }
  }
}

/**
 * Measure distance using HC-SR04 ultrasonic sensor
 * Returns distance in cm, or -1 on timeout/error
 */
long getDistance() {
  // Clear the trigger pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  // Send 10us pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Read the echo pin (timeout 30ms ~ 5m max)
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  
  if (duration == 0) {
    return -1; // No echo / out of range
  }
  
  // Calculate distance (speed of sound 343 m/s)
  long distance = duration * 0.034 / 2;
  
  return distance;
}
