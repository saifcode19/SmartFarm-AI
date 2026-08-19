# Smart Farm AI — Development Status & Future Improvements

## Overview

Smart Farm AI is an evolving embedded agriculture prototype. The core farm-automation subsystem has been developed and tested, while additional capabilities such as AI-based plant monitoring and mobile automation are being developed progressively.

The project follows an iterative engineering approach in which new capabilities are added and validated step by step.

---

## Current Development Status

### Core System — Implemented

The ESP32-based farm automation subsystem currently supports:

- Soil-moisture monitoring
- Soil-moisture calibration
- Automatic irrigation
- Relay-controlled water pump
- Moisture-based LED indication
- DHT11 temperature/humidity monitoring
- Blynk-based IoT monitoring and control

This represents the most developed part of the current prototype.

---

## Plant Health Monitoring — Experimental Development

The ESP32-CAM subsystem provides the foundation for visual plant monitoring.

Current capabilities include:

- ESP32-CAM integration
- Plant image capture
- Python/Flask processing
- AI model integration
- Healthy/diseased classification experimentation
- Physical camera-cart platform

Further development is focused on improving image quality, model reliability, and validation.

---

## Mobile Monitoring Platform

A physical cart was built to provide a mobile platform for the ESP32-CAM.

The current prototype uses manual movement during testing, allowing the camera and software workflow to be evaluated on a physical mobile platform.

```text
ESP32-CAM
    ↓
Image Capture
    ↓
AI / Software Processing
    ↓
Physical Camera Cart
    ↓
Manual Movement
```

Autonomous movement is planned as a future upgrade.

---

## AI Development

The AI component is currently an experimental plant-health classification system.

The project uses a two-class concept:

```text
Healthy
   ↔
Diseased
```

During development, the model showed a tendency toward the Diseased class. This provides a clear direction for future model improvement and validation.

Future work will focus on:

- Better training data
- Improved image quality
- Model refinement
- Independent validation
- More reliable classification

The current observed prediction behavior is treated as a development result rather than as a final accuracy claim.

---

## TDS-Based Monitoring

The TDS sensor is being explored for experimental nutrient/fertilizer-related monitoring.

The current work focuses on understanding how TDS measurements can be incorporated into the broader agricultural monitoring concept.

Future development may investigate:

- Better measurement methodology
- Controlled testing conditions
- More meaningful nutrient-related interpretation
- Integration with the farm automation workflow

The TDS subsystem is kept separate from the verified soil-moisture irrigation system.

---

## Sensor Development

The project uses the following primary sensing components:

```text
Soil Moisture
      +
DHT11
      +
TDS
```

The DHT22 was also evaluated during development but was not retained as part of the verified implementation.

Future sensor development may focus on improving measurement reliability and expanding environmental monitoring capabilities.

---

## Future Rover Development

The current mobile platform is manually operated.

The planned development path is:

```text
Manual Camera Cart
       ↓
Motorized Movement
       ↓
Controlled Navigation
       ↓
Automatic Crop-Row Movement
       ↓
Automatic Image Capture
       ↓
Mobile Plant Monitoring
```

This provides a clear upgrade path from the current physical prototype toward a more autonomous monitoring platform.

---

## System Integration Roadmap

Future development can progressively connect the two existing subsystems:

```text
ESP32 Farm Automation
        +
ESP32-CAM Plant Monitoring
        ↓
Shared Smart Farm Workflow
        ↓
Plant Monitoring
        +
Environmental Monitoring
        +
Irrigation Automation
        ↓
More Integrated Agriculture Platform
```

The goal is to gradually move from individual working subsystems toward a more integrated smart-farming platform.

---

## Development Priorities

The next development priorities are:

1. Improve AI plant-health classification
2. Improve ESP32-CAM image quality
3. Continue testing the TDS monitoring concept
4. Develop controlled movement for the camera cart
5. Explore autonomous crop-row navigation
6. Integrate plant-monitoring information with the farm-automation system
7. Perform longer-duration testing

---

## Engineering Approach

The project is being developed using an incremental approach:

```text
Build
  ↓
Test
  ↓
Identify Issues
  ↓
Improve
  ↓
Retest
  ↓
Integrate
  ↓
Expand
```

This approach allows individual subsystems to be developed and validated before introducing additional complexity.

---

## Current Project Position

Smart Farm AI currently provides a working foundation for:

- Embedded agriculture automation
- Sensor-based monitoring
- Automatic irrigation
- IoT control
- Camera-based plant monitoring
- Experimental AI integration
- Physical mobile monitoring

The project remains under active development, with the next stage focused on improving AI reliability and extending the physical capabilities of the camera platform.

---

## Future Vision

The long-term direction of the project is to combine the existing technologies into a more capable agricultural monitoring and automation platform.

```text
                    SMART FARM AI
                         |
          +--------------+--------------+
          |                             |
          v                             v
    Farm Automation              Plant Monitoring
          |                             |
       ESP32                       ESP32-CAM
          |                             |
   Sensors + Pump                  Camera + AI
          |                             |
          +-------------+-------------+
                        |
                        v
              Integrated Monitoring
                        |
                        v
              Smarter Farm Decisions
```

The current prototype provides the hardware and software foundation for continued development toward this vision.
