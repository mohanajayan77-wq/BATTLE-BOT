# BATTLE-BOT Test Cases & Sample Data

## Unit / Functional Test Cases

### TC-01: Clear Area Detection
- **Setup**: No objects within 50 cm; normal room lighting (LDR > 500).
- **Expected**: Green LED ON, Red/Yellow OFF, Buzzer OFF. Serial: "CLEAR".
- **Pass Criteria**: Status remains CLEAR for 10 consecutive readings.

### TC-02: Warning Zone
- **Setup**: Object placed at ~30 cm from ultrasonic sensor.
- **Expected**: Yellow LED ON, Green OFF. Serial contains "WARNING - CLOSE OBJECT".
- **Pass Criteria**: Alert triggers within 1 second of placement.

### TC-03: Critical Obstacle
- **Setup**: Object closer than 20 cm.
- **Expected**: Red LED ON + Buzzer active (intermittent). Serial: "OBSTACLE DETECTED".
- **Pass Criteria**: Immediate response; buzzer pattern audible.

### TC-04: Low Visibility
- **Setup**: Cover LDR or reduce ambient light so reading < 400.
- **Expected**: Status includes "LOW VISIBILITY"; Yellow LED may activate.
- **Pass Criteria**: Correct status string in Serial output.

### TC-05: Combined Hazard
- **Setup**: Obstacle < 20 cm + low light.
- **Expected**: Red LED + Buzzer + "OBSTACLE DETECTED | LOW VISIBILITY".
- **Pass Criteria**: Both conditions reflected simultaneously.

### TC-06: Out-of-Range / Timeout
- **Setup**: Point ultrasonic into open space > 4 m or cover sensor.
- **Expected**: Distance reported as -1 or large value; system stays in safe state (Green preferred).
- **Pass Criteria**: No false critical alerts.

### TC-07: Serial Logging Stability
- **Setup**: Run for 5 minutes continuous.
- **Expected**: Stable 9600 baud output every ~200 ms without hangs or garbage.
- **Pass Criteria**: Continuous readable log; no resets.

## Sample Serial Output (Realistic)

```
========================================
  BATTLE-BOT Safety Monitoring System
  Initializing sensors...
========================================
System Ready. Monitoring area...
Distance(cm) | LightLevel | Status
----------------------------------------
45 cm | 612 | CLEAR
42 cm | 605 | CLEAR
28 cm | 598 | WARNING - CLOSE OBJECT
15 cm | 590 | OBSTACLE DETECTED
12 cm | 320 | OBSTACLE DETECTED | LOW VISIBILITY
35 cm | 310 | WARNING - CLOSE OBJECT | LOW VISIBILITY
55 cm | 680 | CLEAR
```

## Sample Sensor Readings (CSV format for logging)

```csv
timestamp_ms,distance_cm,light_level,status
1000,48,620,CLEAR
1200,47,618,CLEAR
1400,22,615,WARNING - CLOSE OBJECT
1600,18,610,OBSTACLE DETECTED
1800,15,280,OBSTACLE DETECTED | LOW VISIBILITY
2000,40,290,WARNING - CLOSE OBJECT | LOW VISIBILITY
2200,60,700,CLEAR
```

## How to Capture Sample Data
1. Open Arduino Serial Monitor (9600 baud).
2. Or use a serial logger (e.g., `screen`, `minicom`, or Python `pyserial`).
3. Save output to file for analysis / submission evidence.

## Hardware Validation Checklist
- [ ] Ultrasonic responds correctly to hand wave / known distance object.
- [ ] LDR reading changes when light is blocked / increased.
- [ ] All three LEDs light independently when forced HIGH in test sketch.
- [ ] Buzzer produces audible tone.
- [ ] No overheating or unstable power.
