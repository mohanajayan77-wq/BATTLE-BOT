# BATTLE-BOT System Architecture

## Overview
BATTLE-BOT is a low-cost, modular safety inspection robot designed for monitoring hazardous, restricted, or low-visibility areas. The initial prototype focuses on core sensing and alerting using Arduino. Future iterations will add Edge AI, camera/night-vision, GPS, long-range wireless, and autonomous navigation.

## High-Level Architecture

```
+-------------------+       +------------------+       +-------------------+
|   Sensors Layer   | ----> |  Processing Unit | ----> |  Actuation/Alert  |
|                   |       |                  |       |                   |
| - HC-SR04 Ultrasonic|     |  Arduino Uno     |       | - RGB LEDs        |
| - LDR (Light)     |       |  (Edge logic)    |       | - Buzzer          |
| (Future: Camera,  |       |                  |       | (Future: Motors,  |
|  Thermal, GPS)    |       |                  |       |  Wireless Tx)     |
+-------------------+       +------------------+       +-------------------+
                                      |
                                      v
                            +------------------+
                            | Serial / Logging |
                            | (Monitoring)     |
                            +------------------+
```

## Components (Prototype)

| Component          | Role                              | Interface     |
|--------------------|-----------------------------------|---------------|
| Arduino Uno        | Central microcontroller           | -             |
| HC-SR04            | Distance / obstacle detection     | Digital D9/D10|
| LDR + 10k resistor | Ambient light / visibility        | Analog A0     |
| Red LED            | Critical alert                    | Digital D11   |
| Yellow LED         | Warning / low visibility          | Digital D12   |
| Green LED          | All clear                         | Digital D13   |
| Buzzer             | Audible alert                     | Digital D8    |

## Data Flow
1. **Sense**: Ultrasonic measures distance every ~200ms. LDR samples light level.
2. **Process**: Compare against thresholds (obstacle <20cm critical, <40cm warning; light <400 low visibility).
3. **Act**: Activate appropriate LED(s) and buzzer. Log status to Serial.
4. **Monitor**: Serial output can be captured by a laptop or future Android control app for remote situational awareness.

## Future Architecture (Roadmap)
- **Edge AI Module**: On-device TinyML / TensorFlow Lite for object classification and hazard recognition (night-vision compatible).
- **Vision Pipeline**: Camera + IR illuminators → local inference → alert payload.
- **Communication**: LoRa / ESP-NOW / long-range RF for network-independent telemetry.
- **Mobility**: Differential drive motors + autonomous navigation with obstacle avoidance.
- **Control Interface**: Android app for real-time map, video stream (when available), and command uplink.
- **Power**: Modular battery pack with status monitoring.

## Design Principles
- **Affordability**: Commodity sensors and Arduino ecosystem.
- **Modularity**: Easy to swap/add sensors or upgrade MCU (e.g., to ESP32 or Raspberry Pi).
- **Offline-first**: Core detection works without cloud or internet.
- **Open Source**: Full code, circuit, and docs released under MIT for community and institutional adoption.

## Safety & Limitations (Prototype)
- Detection range limited by HC-SR04 (~2-400cm practical).
- No mobility or autonomous path planning in current prototype.
- Light sensing is ambient only (not thermal).
- Intended for demonstration and controlled testing; not yet certified for operational deployment.
