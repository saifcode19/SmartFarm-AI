# Smart Farm AI — Hardware Documentation

## Overview

Smart Farm AI is built around an **ESP32 DevKit** as the main farm-automation controller and an **ESP32-CAM** as the camera-based plant-monitoring controller.

The hardware was developed incrementally, with individual sensors and actuators tested before being combined into the larger prototype.

The current hardware system focuses on:

- Soil-moisture monitoring
- Temperature and humidity monitoring
- Experimental TDS monitoring
- Automatic irrigation
- Relay-controlled pump operation
- LED status indication
- ESP32-CAM plant image capture
- A physical mobile camera cart

The current camera cart is manually operated. Autonomous movement is planned as a future development.

---

## Main Controllers

| Controller | Purpose | Status |
|---|---|---|
| ESP32 DevKit | Main farm automation and IoT controller | Implemented / Tested |
| ESP32-CAM | Plant image capture and AI experimentation | Implemented / Tested |

The project does **not** use an ESP8266 controller.

---

## ESP32 DevKit

The ESP32 DevKit is the primary controller for the farm automation subsystem.

It is responsible for:

- Reading the soil-moisture sensor
- Reading environmental sensor data
- Processing sensor values
- Applying irrigation thresholds
- Controlling the relay
- Controlling the water pump
- Driving status LEDs
- Communicating with Blynk through Wi-Fi
- Providing manual control through the IoT interface

### Main Data Flow

```text
Sensors
   |
   v
ESP32 DevKit
   |
   +-- Sensor Processing
   |
   +-- Irrigation Decision
   |
   +-- Relay Control
   |
   +-- LED Indication
   |
   +-- Blynk Communication
```

---

## ESP32-CAM

The ESP32-CAM is used as the plant-monitoring camera platform.

Its main purpose is to:

- Capture plant images
- Provide images to the software-processing pipeline
- Support experimental plant-health classification
- Operate as the camera system mounted on the physical cart

### Camera Data Flow

```text
Plant
  |
  v
ESP32-CAM
  |
  v
Image Capture
  |
  v
Python / Flask
  |
  v
AI Processing
```

The ESP32-CAM system is currently an experimental plant-health monitoring subsystem.

---

## Soil Moisture Sensor

The soil moisture sensor is one of the most important sensors in the project.

It provides an analog reading representing the moisture condition of the soil.

The ESP32 reads this analog value and converts it into an approximate moisture percentage using calibrated wet and dry reference values.

### Calibration Values

```text
WET_ADC = 1500
DRY_ADC = 3500
```

### Purpose

The soil moisture value is used to:

- Determine whether the soil is dry
- Start irrigation when required
- Monitor moisture while irrigation is active
- Stop irrigation after the target moisture level is reached
- Display soil moisture information through Blynk

### Irrigation Thresholds

```text
Pump ON  → Moisture below 40%
Pump OFF → Moisture reaches 80%
```

The separate ON and OFF thresholds help prevent rapid switching around a single threshold.

---

## DHT11 Temperature & Humidity Sensor

The DHT11 was used for environmental monitoring.

It provides:

- Temperature
- Humidity

The DHT11 was successfully tested during development.

### Data Flow

```text
DHT11
  |
  v
ESP32
  |
  v
Temperature / Humidity Data
```

---

## TDS Sensor

The TDS sensor was explored for experimental monitoring related to fertilizer/nutrient solutions.

The TDS subsystem is separate from the soil-moisture irrigation system.

### Concept

```text
Fertilizer / Water Solution
          |
          v
       TDS Sensor
          |
          v
         ESP32
          |
          v
      TDS Reading
```

A soil-water sample approach was also explored during development.

### Important Limitation

The TDS sensor is **not treated as a complete soil NPK analyzer**.

The TDS-based nutrient/fertilizer functionality remains experimental and is not presented as scientifically validated soil-fertility measurement.

---

## Relay Module

A relay module is used to control the irrigation pump from the ESP32.

The ESP32 provides the control signal while the relay switches the pump circuit.

### Control Path

```text
ESP32
  |
  v
Relay Control Signal
  |
  v
Relay Module
  |
  v
Water Pump
```

The relay was integrated into the automatic irrigation system.

---

## Water Pump

The water pump is the main irrigation actuator.

It is controlled through the relay according to the soil moisture decision logic.

### Irrigation Sequence

```text
Soil Moisture < 40%
        |
        v
     Relay ON
        |
        v
     Pump ON
        |
        v
    Irrigation
        |
        v
Moisture reaches 80%
        |
        v
     Relay OFF
        |
        v
     Pump OFF
```

---

## LED Indicators

LEDs were used as simple visual status indicators.

The project used moisture-based LED indication.

```text
Moisture < 40%
      ↓
LED1 ON

Moisture > 45%
      ↓
LED2 ON
```

The LEDs provide a quick visual indication of the moisture condition during testing and operation.

---

## Blynk Hardware Interaction

The ESP32 connects to Blynk through Wi-Fi.

Blynk provides remote monitoring and control of the hardware system.

### Virtual Pin Mapping

| Virtual Pin | Function |
|---|---|
| V0 | Soil moisture data |
| V1 | Relay control/status |
| V2 | Manual control switch |

### Hardware-to-Blynk Flow

```text
Soil Sensor
     |
     v
   ESP32
     |
     | Wi-Fi
     v
   Blynk
     |
     +---- Soil Moisture
     |
     +---- Relay Status/Control
     |
     +---- Manual Control
```

---

## Mobile Camera Cart

A physical cart was built to provide a mobile platform for the ESP32-CAM.

The current prototype includes:

- Physical cart
- ESP32-CAM
- Camera mounting/fixing
- Camera software
- Image capture workflow

The cart was manually moved during testing.

### Current Hardware Configuration

```text
        ESP32-CAM
            |
            v
      Camera Module
            |
            v
      Physical Cart
            |
            v
      Manual Movement
```

The current hardware does **not** implement autonomous navigation.

---

## Future Rover Hardware

Autonomous movement is planned as a future upgrade.

The planned hardware may include:

- DC motors
- Motor driver
- Appropriate power supply
- Mechanical drive system
- Navigation/positioning hardware

The future concept is:

```text
ESP32-CAM
    +
Motor Driver
    +
DC Motors
    +
Navigation System
        |
        v
Automatic Movement
```

These components are **future/planned hardware** and should not be considered part of the current verified implementation.

---

## Hardware Integration

The current hardware architecture can be summarized as:

```text
                    SMART FARM AI
                         |
          +--------------+--------------+
          |                             |
          v                             v
      ESP32 SYSTEM                 ESP32-CAM SYSTEM
          |                             |
     +----+----+                        |
     |    |    |                        v
     v    v    v                  Camera Capture
   Soil DHT11 TDS                       |
   Sensor Sensor Sensor                 v
     |    |    |                   AI / Software
     +----+----+                   Processing
          |
          v
    Decision Logic
          |
          v
       Relay
          |
          v
      Water Pump
          |
          v
      Irrigation
```

---

## Hardware Testing Status

| Hardware | Current Status |
|---|---|
| ESP32 DevKit | Working / Tested |
| ESP32-CAM | Working / Tested |
| Soil Moisture Sensor | Working / Tested |
| DHT11 | Tested |
| DHT22 | Problematic / Not used in verified system |
| TDS Sensor | Experimental |
| Relay | Tested |
| Water Pump | Tested |
| LEDs | Tested |
| Mobile Camera Cart | Built / Manual operation |
| Autonomous Rover Hardware | Planned |

---

## Hardware Limitations

The current prototype has several hardware-related limitations:

- The mobile camera cart currently requires manual movement.
- Autonomous navigation has not yet been implemented.
- ESP32-CAM image quality requires further improvement for reliable plant-health classification.
- TDS-based nutrient monitoring remains experimental.
- The complete farm automation and camera-monitoring systems are not yet fully integrated into one autonomous platform.

---

## Current Hardware Architecture

The verified hardware system consists primarily of:

```text
ESP32 DevKit
    |
    +-- Soil Moisture Sensor
    +-- DHT11
    +-- TDS Sensor
    +-- Relay
    +-- Water Pump
    +-- LEDs
    +-- Wi-Fi / Blynk


ESP32-CAM
    |
    +-- Camera
    |
    +-- Physical Manual Cart
```

This architecture represents the current prototype and separates implemented hardware from future development concepts.
