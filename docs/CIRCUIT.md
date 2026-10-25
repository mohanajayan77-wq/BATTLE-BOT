# BATTLE-BOT Circuit Diagram & Wiring Guide

## Tinkercad / Physical Prototype Wiring

### Components Required
- 1 × Arduino Uno (or compatible)
- 1 × HC-SR04 Ultrasonic Sensor
- 1 × LDR (Photoresistor)
- 1 × 10kΩ resistor (for LDR voltage divider)
- 3 × LEDs (Red, Yellow, Green) + current-limiting resistors (~220Ω each recommended)
- 1 × Passive or Active Buzzer
- Breadboard + jumper wires
- USB cable for power/programming

### Pin Connections

| Arduino Pin | Component          | Notes                              |
|-------------|--------------------|------------------------------------|
| D9          | HC-SR04 Trigger    |                                    |
| D10         | HC-SR04 Echo       |                                    |
| A0          | LDR junction       | LDR to 5V, 10k to GND              |
| D11         | Red LED (+)        | via ~220Ω resistor to GND         |
| D12         | Yellow LED (+)     | via ~220Ω resistor to GND         |
| D13         | Green LED (+)      | via ~220Ω resistor to GND         |
| D8          | Buzzer (+)         | other side to GND                  |
| 5V          | VCC (sensors)      | HC-SR04 VCC, LDR side              |
| GND         | Common Ground      | All components                     |

### LDR Voltage Divider
```
5V ---- LDR ---- A0 ---- 10kΩ ---- GND
```
Higher light → lower resistance of LDR → higher voltage at A0.

### Recommended Thresholds (code defaults)
- Critical obstacle: < 20 cm
- Warning zone: 20–40 cm
- Low light / poor visibility: LDR reading < 400 (0–1023 scale)

These can be adjusted in `BattleBot.ino` constants.

### Power
Powered via USB for prototype. For field use, add battery pack (7-12V to Vin or regulated 5V).

### Simulation
A matching Tinkercad circuit is available (search "Battle-Bot Prototype" or recreate using the pinout above). Serial Monitor at 9600 baud shows live Distance | LightLevel | Status.

### Safety Notes
- Do not exceed 5V on sensor VCC.
- Use current-limiting resistors for LEDs.
- Secure wiring before powering.
