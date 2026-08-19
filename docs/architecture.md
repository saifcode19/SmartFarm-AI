# Smart Farm AI — System Architecture

## Overview

Smart Farm AI is organized into two main technical subsystems:

1. **ESP32-based farm automation**
2. **ESP32-CAM-based plant health monitoring**

The farm automation subsystem focuses on sensor monitoring, automatic irrigation, relay control, and Blynk-based IoT interaction.

The plant monitoring subsystem focuses on image capture using the ESP32-CAM and experimental AI-based plant health classification through a Python/Flask processing workflow.

The current prototype does not represent a fully autonomous farming system. The mobile camera cart is currently operated manually, while autonomous movement is planned for future development.

---

## High-Level Architecture

```text
                         SMART FARM AI
                              |
              +---------------+---------------+
              |                               |
              v                               v
       FARM AUTOMATION                 PLANT MONITORING
              |                               |
              v                               v
        ESP32 DevKit                    ESP32-CAM
              |                               |
      +-------+-------+                       |
      |       |       |                       v
      v       v       v                 Image Capture
    Soil    DHT11    TDS                      |
   Sensor  Sensor   Sensor                    v
      |       |       |                 Python / Flask
      +-------+-------+                       |
              |                               v
              v                           AI Model
        Decision Logic                       |
              |                               v
              v                       Healthy / Diseased
        Relay Control
              |
              v
          Water Pump
              |
              v
       Automatic Irrigation
              |
              v
            Blynk
```

---

## 1. Farm Automation Subsystem

The ESP32 DevKit acts as the primary controller for the farm automation subsystem.

It receives sensor data and uses programmed logic to control the irrigation system.

### Main Components

```text
ESP32 DevKit
    |
    +-- Soil Moisture Sensor
    |
    +-- DHT11
    |
    +-- TDS Sensor
    |
    +-- Relay Module
    |
    +-- Water Pump
    |
    +-- Status LEDs
    |
    +-- Wi-Fi / Blynk
```

---

## 2. Soil Moisture Monitoring

The soil moisture sensor provides an analog reading to the ESP32.

The raw ADC value is converted into an approximate moisture percentage using calibrated wet and dry reference values.

### Calibration

```text
WET_ADC = 1500
DRY_ADC = 3500
```

The resulting moisture value is used by the irrigation decision logic.

```text
Soil
  |
  v
Moisture Sensor
  |
  v
ESP32 ADC
  |
  v
Calibration
  |
  v
Moisture Percentage
  |
  v
Irrigation Decision
```

---

## 3. Automatic Irrigation Architecture

The irrigation system uses threshold-based control.

```text
Read Soil Moisture
       |
       v
Calculate Moisture %
       |
       v
Moisture < 40% ?
    +------+------+
    |             |
   YES            NO
    |             |
    v             v
 Pump ON      Continue Monitoring
    |
    v
Monitor Moisture
    |
    v
Moisture reaches 80%
    |
    v
 Pump OFF
```

The system uses separate ON and OFF thresholds to reduce rapid relay switching around a single threshold.

### Thresholds

```text
Pump ON  → Moisture below 40%
Pump OFF → Moisture reaches 80%
```

---

## 4. Temperature and Humidity Monitoring

The DHT11 is connected to the ESP32 for environmental monitoring.

The sensor provides:

- Temperature
- Humidity

The DHT11 was successfully tested during development.

A DHT22 was also evaluated but encountered integration problems and is not considered part of the verified implementation.

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

## 5. TDS Monitoring

The TDS sensor was explored as part of the fertilizer and nutrient-monitoring concept.

The TDS subsystem is separate from the soil-moisture irrigation logic.

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
          |
          v
 Experimental Nutrient Logic
```

A soil-water sample approach was also explored during development.

The TDS sensor is **not treated as a complete soil NPK analyzer**. This part of the system remains experimental.

---

## 6. Relay and Pump Control

The ESP32 controls the irrigation pump through a relay.

```text
ESP32
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

The relay is activated when the soil moisture falls below the configured irrigation threshold and is deactivated when the target moisture level is reached.

---

## 7. Blynk IoT Architecture

Blynk provides the IoT monitoring and control layer.

The ESP32 communicates through Wi-Fi with the Blynk platform.

```text
Sensors
   |
   v
ESP32
   |
   | Wi-Fi
   v
Blynk
   |
   +-- Soil Moisture Monitoring
   |
   +-- Relay Control
   |
   +-- Manual Control
```

### Virtual Pin Mapping

| Virtual Pin | Function |
|---|---|
| V0 | Soil moisture data |
| V1 | Relay control/status |
| V2 | Manual control switch |

Blynk was also used during development for remote/manual interaction with the irrigation system.

---

## 8. Plant Health Monitoring Subsystem

The second major subsystem uses an ESP32-CAM.

Its purpose is to capture plant images for experimental plant-health classification.

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
AI Model
  |
  v
Healthy / Diseased
```

The system was developed as an experimental computer-vision pipeline rather than a validated agricultural disease-detection system.

---

## 9. ESP32-CAM Processing Architecture

The ESP32-CAM captures an image and provides it to the software-processing pipeline.

The development workflow included a camera capture endpoint and a Python/Flask application.

```text
ESP32-CAM
    |
    v
Capture Image
    |
    v
HTTP / Capture Endpoint
    |
    v
Python
    |
    v
Flask Application
    |
    v
AI Model
    |
    v
Classification Result
```

The AI workflow used external dataset/model-training resources during experimentation.

---

## 10. AI Classification

The experimental classifier was designed around two classes:

```text
Healthy
   |
   |  VS
   |
Diseased
```

Google Teachable Machine and a Kaggle plant/leaf dataset were used during the development process.

Model-related files included:

```text
metadata
model
weights.bin
```

The AI system currently has limitations and should not be interpreted as a validated plant-disease diagnosis system.

---

## 11. AI Limitations

During testing, the model showed a strong bias toward the **Diseased** class.

Observed predictions were approximately:

```text
98–100% Diseased
```

This value represents an observed prediction behavior and **does not represent model accuracy**.

The main areas requiring further development include:

- Image quality
- Dataset/model behavior
- Classification reliability
- Validation
- Web interface stability

---

## 12. Mobile Camera Cart

A physical cart was developed to provide a mobile platform for the ESP32-CAM.

The current implementation includes:

- Physical cart
- ESP32-CAM
- Camera mounting
- Camera software
- Image capture
- AI/software processing

The cart was manually moved during the current prototype stage.

### Current Architecture

```text
ESP32-CAM
    |
    v
Image Capture
    |
    v
AI / Software Processing
    |
    v
Physical Camera Cart
    |
    v
Manual Movement
```

The current project does **not** implement autonomous rover movement.

---

## 13. Future Autonomous Rover Architecture

Autonomous movement is planned as a future upgrade.

The intended future architecture is:

```text
ESP32-CAM
    |
    +-- Motor Driver
    |
    +-- DC Motors
    |
    +-- Autonomous Navigation
            |
            v
      Crop-Row Movement
            |
            v
      Automatic Image Capture
            |
            v
       Plant Monitoring
```

Autonomous movement is therefore classified as **planned**, not implemented.

---

## 14. Overall Data Flow

The overall Smart Farm concept can be represented as:

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
     v    v    v                  Image Capture
   Soil DHT11 TDS                       |
     |    |    |                        v
     +----+----+                   Python / Flask
          |                             |
          v                             v
    Decision Logic                  AI Model
          |                             |
          v                             v
       Relay                    Healthy / Diseased
          |
          v
      Water Pump
          |
          v
      Irrigation
          |
          v
        Blynk
```

---

## 15. Controller Responsibilities

| Controller | Primary Responsibility |
|---|---|
| ESP32 DevKit | Sensor monitoring, irrigation logic, relay/pump control, LEDs, Blynk communication |
| ESP32-CAM | Plant image capture and experimental AI plant-health workflow |

The project does **not** use an ESP8266 controller.

---

## 16. Current Architecture Status

### Verified

- ESP32-based farm automation
- Soil moisture sensing
- Soil moisture calibration
- Automatic irrigation logic
- Relay-controlled pump
- DHT11 testing
- Blynk monitoring/control
- ESP32-CAM image capture
- Python/Flask processing workflow
- Physical camera cart

### Experimental / Partially Working

- TDS-based nutrient monitoring
- AI plant-health classification
- ESP32-CAM web interface
- Complete integration between farm automation and AI monitoring

### Planned

- Autonomous cart movement
- Crop-row navigation
- Automatic plant-image capture while moving
- Improved AI classification
- More complete integration between the two subsystems

---

## Architecture Summary

Smart Farm AI currently consists of two complementary prototype systems:

```text
ESP32
 ↓
Sensor Monitoring
 ↓
Decision Logic
 ↓
Automatic Irrigation
 ↓
Blynk IoT
```

and:

```text
ESP32-CAM
 ↓
Plant Image Capture
 ↓
Python / Flask
 ↓
Experimental AI Classification
```

The mobile camera cart provides a physical platform for the ESP32-CAM. At the current stage, the cart is manually operated, while autonomous movement is reserved for future development.
