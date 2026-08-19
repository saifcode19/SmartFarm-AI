# Smart Farm AI — ESP32 IoT Agriculture Automation & Plant Health Monitoring

## Project Overview

Smart Farm AI is an ESP32-based agricultural automation prototype designed to monitor soil and environmental conditions and automate selected farming operations.

The project combines:

- Embedded systems
- Sensor-based monitoring
- Automatic irrigation
- Relay-controlled hardware
- IoT monitoring through Blynk
- ESP32-CAM image capture
- Python/Flask processing
- Experimental AI-based plant health classification

The project was developed as a practical prototype to explore how sensing, embedded decision-making, physical actuation, IoT monitoring, and computer vision can be combined into a smart agriculture system.

> **Current status:** Prototype / partially implemented system.  
> The strongest verified subsystem is the ESP32-based soil-moisture irrigation automation. The ESP32-CAM plant-health system and mobile camera platform are experimental and under further development.

---

## Problem

Traditional farming operations often depend on manual observation and manual control of irrigation and other activities.

This project explores solutions for:

- Manual irrigation decisions
- Monitoring soil conditions
- Monitoring environmental conditions
- Remote monitoring and control
- Experimental plant-health monitoring using computer vision

The objective is not to claim a production-ready autonomous farm, but to demonstrate a practical embedded system that can sense conditions, make basic decisions, and control physical hardware.

---

## Core System

The project consists of two main subsystems:

### 1. Farm Automation

```text
Soil / Environmental Sensors
            ↓
         ESP32
            ↓
      Decision Logic
            ↓
       Relay Control
            ↓
        Water Pump
            ↓
     Automatic Irrigation
            ↓
        Blynk / IoT
```

### 2. AI Plant Monitoring

```text
Plant
  ↓
ESP32-CAM
  ↓
Image Capture
  ↓
Python / Flask
  ↓
AI Model
  ↓
Healthy / Diseased
```

The two subsystems represent different parts of the overall Smart Farm concept. Complete end-to-end integration between all subsystems is still under development.

---

## Key Features

### Implemented / Tested

- ESP32-based farm automation
- Analog soil-moisture sensing
- Soil-moisture calibration
- Automatic irrigation logic
- Relay-controlled water pump
- Moisture-based LED indication
- Blynk IoT monitoring and control
- DHT11 temperature/humidity testing
- ESP32-CAM image capture
- Python/Flask camera-processing workflow
- Experimental healthy-vs-diseased plant classification
- Physical mobile camera cart prototype

### Experimental / In Development

- TDS-based fertilizer/nutrient monitoring concept
- AI plant-health classification reliability
- Improved ESP32-CAM image quality
- Mobile plant-monitoring workflow
- Autonomous movement of the camera cart
- More complete integration between farm automation and AI monitoring

---

## Hardware

| Component | Purpose | Status |
|---|---|---|
| ESP32 DevKit | Main farm automation controller | Implemented / Tested |
| ESP32-CAM | Plant image capture and AI experiment | Implemented / Tested |
| Soil Moisture Sensor | Soil moisture measurement | Implemented / Tested |
| DHT11 | Temperature and humidity monitoring | Tested |
| TDS Sensor | Experimental fertilizer/nutrient monitoring | Experimental |
| Relay Module | Pump/control switching | Implemented / Tested |
| Water Pump | Automatic irrigation | Implemented / Tested |
| LEDs | System/moisture indication | Implemented / Tested |
| Mobile Cart | Physical camera platform | Prototype / Manual |

---

## Automatic Irrigation

Automatic irrigation is the most developed part of the project.

The soil moisture sensor provides an analog reading to the ESP32. The reading is converted into an approximate moisture percentage using calibrated wet and dry reference values.

### Calibration

```text
WET_ADC = 1500
DRY_ADC = 3500
```

### Control Logic

```text
Read Soil Moisture
       ↓
Convert ADC → Moisture %
       ↓
Moisture < 40% ?
    ┌──────┴──────┐
   YES            NO
    ↓              ↓
 Pump ON       Continue Monitoring
    ↓
Monitor Moisture
    ↓
Moisture reaches 80%
    ↓
 Pump OFF
```

The separate ON and OFF thresholds provide hysteresis and help prevent rapid switching around a single threshold.

### LED Indication

```text
Moisture < 40%
      ↓
LED1 ON

Moisture > 45%
      ↓
LED2 ON
```

---

## Blynk IoT Monitoring

Blynk was used as the IoT monitoring and control layer.

It provides a way to:

- Monitor sensor data
- Control the relay
- Provide manual control
- Interact with the ESP32 remotely

### Virtual Pin Mapping

| Virtual Pin | Function |
|---|---|
| V0 | Soil moisture data |
| V1 | Relay control/status |
| V2 | Manual control switch |

Blynk configuration and dashboard behavior required debugging during development, including template, widget, and data-display issues.

---

## Environmental Monitoring

The project explored temperature and humidity monitoring using DHT sensors.

### DHT11

The DHT11 was successfully tested for:

- Temperature
- Humidity

### DHT22

The DHT22 was also evaluated but encountered integration problems during development.

Therefore, the project does not claim successful DHT22 implementation.

---

## TDS / Fertilizer Monitoring

A TDS sensor was explored for monitoring dissolved material in a fertilizer/water solution.

The concept was kept separate from soil-moisture-based irrigation:

```text
Soil Moisture
     ↓
Irrigation Decision
     ↓
Water Pump
```

while the experimental nutrient concept was:

```text
Fertilizer / Water Solution
          ↓
       TDS Sensor
          ↓
      TDS Reading
          ↓
 Experimental Fertilizer Logic
```

A soil-water sample approach was also explored.

> **Important:** A TDS sensor is not treated as a complete soil NPK analyzer. This part of the project remains experimental and is not presented as scientifically validated soil-fertility measurement.

---

## AI Plant Health Monitoring

The project was extended with an ESP32-CAM to explore visual plant-health monitoring.

The target classification was:

```text
Healthy
   vs
Diseased
```

### Processing Pipeline

```text
Plant
  ↓
ESP32-CAM
  ↓
Image Capture
  ↓
HTTP / Capture Endpoint
  ↓
Python
  ↓
Flask
  ↓
AI Model
  ↓
Healthy / Diseased
```

The development workflow involved an external plant/leaf dataset and AI model-training experimentation.

Google Teachable Machine and a Kaggle dataset were used during the experimentation phase.

Model-related files included:

```text
metadata
model
weights.bin
```

The exact final model architecture is not documented here because it was not sufficiently established in the project records.

---

## AI Testing & Limitations

The AI plant-health system was experimentally tested.

One major issue was a strong prediction bias toward the **Diseased** class.

Observed predictions were approximately:

```text
98–100% Diseased
```

even when the expected classification was different.

This value **must not be interpreted as 98–100% model accuracy**.

It represents an observed prediction bias during testing.

Other limitations included:

- ESP32-CAM image quality
- Model/inference behavior
- Web interface issues
- Need for better validation
- Need for reliable healthy/diseased classification

The AI system should therefore be considered **experimental**, not a validated plant-disease diagnosis system.

---

## Mobile Camera Cart

A physical cart was developed as a platform for the ESP32-CAM.

The current prototype includes:

- Physical cart
- ESP32-CAM
- Camera mounting/fixing
- Camera software
- Image capture workflow

During the current development stage, the cart was **moved manually** while the camera and software system were tested.

### Current Workflow

```text
ESP32-CAM
    ↓
Camera Capture
    ↓
AI / Software Processing
    ↓
Physical Cart
    ↓
Manual Movement
```

### Future Upgrade

Autonomous movement is planned as a future development stage.

```text
ESP32-CAM
    +
Motor Driver
    +
DC Motors
    +
Autonomous Navigation
        ↓
Automatic Crop-Row Movement
        ↓
Automatic Plant Monitoring
```

The current project does **not** claim autonomous rover navigation.

---

## Development & Debugging

The project involved hands-on debugging across hardware and software.

Important issues encountered included:

- DHT22 integration problems
- Blynk template/configuration problems
- Blynk widgets not displaying expected data
- Relay remaining ON unexpectedly
- ESP32-CAM connectivity problems
- ESP32-CAM image-quality limitations
- AI prediction bias
- Web/Flask interface issues

These issues were part of the iterative development and testing process.

---

## Engineering Approach

The project was developed incrementally:

```text
Problem Identification
        ↓
Hardware Selection
        ↓
Sensor Integration
        ↓
ESP32 Firmware
        ↓
Calibration
        ↓
Automatic Irrigation
        ↓
Blynk IoT Integration
        ↓
ESP32-CAM Integration
        ↓
AI Experimentation
        ↓
Physical Camera Cart
        ↓
Testing & Debugging
        ↓
Future Autonomous Upgrade
```

---

## Current Status

### Working / Verified

- ESP32-based farm controller
- Soil moisture sensing
- Soil moisture calibration
- Automatic irrigation logic
- Relay-controlled pump
- Moisture-based LED indication
- Blynk monitoring/control workflow
- DHT11 testing
- ESP32-CAM image capture
- Python/Flask processing workflow
- Physical camera cart prototype with manual movement

### Experimental / Partially Working

- TDS-based nutrient monitoring
- AI plant-health classification
- ESP32-CAM web interface
- Complete integration between farm automation and AI system

### Planned

- Improved AI classification
- Autonomous cart movement
- Automatic crop-row monitoring
- More complete ESP32 ↔ ESP32-CAM integration
- Improved plant-health detection
- Further field-oriented testing

---

## Important Limitations

This is a **prototype**, not a production agricultural system.

The project does not currently claim:

- Fully autonomous farming
- Autonomous rover navigation
- Validated disease-detection accuracy
- Complete soil NPK analysis using TDS
- Automatic fertilizer optimization
- Quantified water savings
- Increased crop yield
- Production-ready agricultural deployment

The repository documents both successful implementations and development limitations to provide an accurate representation of the project.

---

## External Technologies

The project uses and/or experiments with external technologies including:

- Arduino / ESP32 development environment
- Blynk
- Python
- Flask
- Google Teachable Machine
- External Kaggle dataset resources
- ESP32-CAM software libraries

These technologies are not claimed as original work.

---

## Project Contribution

The project involved hands-on work across:

### Embedded Systems

- ESP32 firmware
- Analog sensor integration
- ADC calibration
- Threshold-based control
- Relay control
- Pump automation

### IoT

- Wi-Fi connectivity
- Blynk configuration
- Sensor monitoring
- Remote/manual control

### AI / Computer Vision

- ESP32-CAM integration
- Image capture
- Python/Flask processing
- Healthy/diseased classification experimentation
- AI debugging

### Hardware

- Sensor wiring
- Relay and pump integration
- ESP32-CAM setup
- Physical camera cart construction
- Hardware/software integration and testing

---

## Future Development

The next development stages are focused on improving reliability and extending the physical system.

### Planned Roadmap

```text
Current Prototype
      ↓
Improve AI Model
      ↓
Improve Camera Quality
      ↓
Automate Cart Movement
      ↓
Crop-Row Navigation
      ↓
Automatic Image Capture
      ↓
Reliable Plant Classification
      ↓
Integrated Smart Farm Platform
```

---
## Project Demo

A demonstration of the Smart Farm AI prototype, including the ESP32-based automation system and ESP32-CAM plant monitoring workflow.

[![Smart Farm AI — Project Demo](https://img.youtube.com/vi/YOUR_VIDEO_ID/maxresdefault.jpg)](https://www.youtube.com/watch?v=ABC123XYZ)

> Click the image above to watch the project demonstration on YouTube.
---

## Project Documentation

Detailed technical documentation will be added to the repository as the project is organized.

Planned documentation includes:

- System architecture
- Hardware and wiring
- Irrigation system
- AI plant-health system
- Testing and validation
- Project limitations
- Development evidence
- [ESP32 Firmware](src/smartfarm.ino)
- [ESP32 Firmware Documentation](src/README.md)

---

## Project Status

**Prototype / Active Development**

Smart Farm AI demonstrates practical work across embedded systems, agriculture automation, IoT, sensor integration, physical hardware, Python-based processing, and experimental computer vision.

The strongest verified subsystem is the **ESP32-based soil-moisture-driven irrigation system**, while the AI camera and mobile monitoring system represent ongoing development.

---

## License & Code Availability

The repository will contain selected project documentation, photographs, diagrams, and appropriate code examples.

Private credentials, API keys, Wi-Fi passwords, Blynk authentication tokens, and other sensitive configuration must never be committed to the public repository.

Complete production code may be kept private where appropriate.
