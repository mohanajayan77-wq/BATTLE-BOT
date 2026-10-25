# BATTLE-BOT

**A low-cost autonomous AI-based safety and inspection system for monitoring hazardous and restricted areas.**

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Arduino](https://img.shields.io/badge/Arduino-Uno-blue.svg)](https://www.arduino.cc/)
[![Wadhwani Foundation](https://img.shields.io/badge/Wadhwani-Foundation-red.svg)](https://www.wadhwani.org/)

Team from **Sri Sairam Engineering College, Chennai**  
Members: Mohana Priya D (ECE), Jayajeevee S S (ECE), Krishna Priya D (AIDS)

---

## Problem
Many industries, defense, and disaster-response teams still rely on manual monitoring of restricted or dangerous areas. This exposes personnel to risk, increases costs, and delays threat detection.

## Solution
**BATTLE-BOT** is a sensor-based robot that remotely inspects hazardous or restricted areas, detects obstacles and unsafe conditions early, and alerts operators before human entry is required.

The current open-source prototype implements the core sensing and alerting layer using Arduino. Future releases will add Edge AI vision, night-vision/thermal, GPS, long-range wireless, and autonomous mobility.

### Key Features (Prototype)
- Real-time ultrasonic obstacle detection
- Ambient light / visibility sensing
- Multi-level visual (LED) and audio (buzzer) alerts
- Serial telemetry for monitoring and logging
- Fully offline operation (no cloud dependency)
- Low-cost, modular, open-source design

---

## Repository Structure
```
BATTLE-BOT/
├── code/
│   └── BattleBot.ino          # Main Arduino sketch
├── docs/
│   ├── ARCHITECTURE.md       # System architecture & roadmap
│   └── CIRCUIT.md            # Wiring diagram & pinout
├── tests/
│   └── TEST_CASES.md         # Functional tests + sample data
├── LICENSE                   # MIT License
└── README.md                 # This file
```

---

## Hardware Requirements
- Arduino Uno (or compatible board)
- HC-SR04 Ultrasonic Sensor
- LDR (Photoresistor) + 10 kΩ resistor
- 3 × LEDs (Red, Yellow, Green) + ~220 Ω resistors
- Buzzer
- Breadboard, jumper wires, USB cable

See [docs/CIRCUIT.md](docs/CIRCUIT.md) for complete wiring.

---

## Quick Start / Setup

### 1. Clone the repository
```bash
git clone https://github.com/mohanajayan77-wq/BATTLE-BOT.git
cd BATTLE-BOT
```

### 2. Open the sketch
- Launch Arduino IDE
- Open `code/BattleBot.ino`
- Select board: **Arduino Uno**
- Select the correct COM port

### 3. Upload
- Click Upload
- Open **Serial Monitor** at **9600 baud**

### 4. Observe
You will see continuous output:
```
Distance(cm) | LightLevel | Status
45 cm | 612 | CLEAR
18 cm | 320 | OBSTACLE DETECTED | LOW VISIBILITY
```

Green LED = Clear area  
Yellow LED = Warning / low visibility  
Red LED + Buzzer = Critical obstacle

---

## Configuration
Thresholds can be tuned at the top of `BattleBot.ino`:

```cpp
const int OBSTACLE_DISTANCE_CM = 20;   // Critical alert
const int WARNING_DISTANCE_CM = 40;    // Warning zone
const int LOW_LIGHT_THRESHOLD = 400;   // Poor visibility
```

---

## Architecture
See [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md) for system design, data flow, and future Edge-AI roadmap.

## Test Cases & Sample Data
See [tests/TEST_CASES.md](tests/TEST_CASES.md) for functional test cases, expected behavior, and sample serial logs.

---

## Roadmap
- [x] Basic ultrasonic + light sensing prototype
- [x] Visual & audio alerts
- [x] Open-source release with documentation
- [ ] Edge AI object / hazard classification (TinyML)
- [ ] Camera + night-vision / thermal support
- [ ] Long-range wireless telemetry (LoRa / ESP-NOW)
- [ ] Differential-drive mobility + autonomous navigation
- [ ] Android control & monitoring application
- [ ] Field trials with disaster-response / industrial partners

---

## License
This project is released under the **MIT License**. See [LICENSE](LICENSE) for details.

You are free to use, modify, and distribute for educational, research, or commercial purposes, provided the copyright notice is retained.

---

## Acknowledgments
- Wadhwani Foundation for the Venture Viability program
- Sri Sairam Engineering College, Chennai
- Mentors and peers who supported the project

---

## Contact
For questions or collaboration: open an Issue on this repository.

**Stay safe. Let the robot go first.**
