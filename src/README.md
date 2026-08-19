# Smart Farm AI — ESP32 Firmware

## Overview

This directory contains the public ESP32 firmware used for the Smart Farm AI prototype.

The firmware demonstrates the core embedded-control logic of the system, including:

- Soil-moisture monitoring
- Automatic irrigation
- Relay-controlled water pump
- DHT11 temperature and humidity monitoring
- TDS sensor reading
- LED status indication
- Blynk IoT monitoring
- Manual control through Blynk

The code is provided as a public implementation reference for the project.

---

## Controller

The firmware is designed for:

```text
ESP32 DevKit
```

The ESP32 acts as the primary controller for the farm-automation subsystem.

---

## Sensor Inputs

### Soil Moisture

The soil-moisture sensor is connected to an ESP32 analog input.

The firmware uses the following calibration references:

```text
WET_ADC = 1500
DRY_ADC = 3500
```

The ADC reading is converted into an approximate soil-moisture percentage.

---

### DHT11

The DHT11 provides:

- Temperature
- Humidity

The readings are periodically collected by the ESP32.

---

### TDS

The TDS sensor provides an analog reading that is processed by the ESP32.

The TDS-related functionality represents the experimental nutrient/fertilizer-monitoring part of the project.

It should not be interpreted as complete soil NPK measurement.

---

## Automatic Irrigation

The firmware implements threshold-based irrigation control.

### Pump ON

```text
Soil Moisture < 40%
        ↓
Relay ON
        ↓
Water Pump ON
```

### Pump OFF

```text
Soil Moisture ≥ 80%
        ↓
Relay OFF
        ↓
Water Pump OFF
```

Separate ON and OFF thresholds are used to reduce rapid switching around a single threshold.

---

## Blynk Integration

The firmware communicates with Blynk through Wi-Fi.

The configured virtual pins are:

| Virtual Pin | Function |
|---|---|
| V0 | Soil moisture |
| V1 | Relay control/status |
| V2 | Manual pump control |

Blynk provides remote monitoring and manual interaction with the irrigation system.

---

## Manual Control

The firmware supports manual pump control through the Blynk interface.

```text
Blynk
  ↓
Manual Control
  ↓
ESP32
  ↓
Relay
  ↓
Water Pump
```

Automatic threshold-based control is used when manual control is not active.

---

## LED Indication

The firmware uses LED indicators to provide visual feedback based on soil moisture.

```text
Moisture < 40%
      ↓
Low-moisture indication
```

```text
Moisture > 45%
      ↓
Higher-moisture indication
```

---

## Sensor Update Interval

Sensor monitoring is scheduled using a Blynk timer.

The configured interval is:

```text
5000 ms
```

or approximately:

```text
5 seconds
```

---

## Serial Monitoring

The firmware outputs sensor information through the Serial Monitor for development and debugging.

The monitored values include:

- Soil moisture
- Temperature
- Humidity
- TDS raw reading

The Serial Monitor can therefore be used to observe the system during testing.

---

## Required Libraries

The firmware uses the following main libraries:

```text
WiFi.h
BlynkSimpleEsp32.h
DHT.h
```

The exact library versions should be selected according to the ESP32 development environment used for the project.

---

## Configuration

Sensitive credentials are intentionally excluded from the public repository.

Before using the firmware, configure:

```cpp
#define BLYNK_TEMPLATE_ID "YOUR_BLYNK_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_BLYNK_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"

char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";
```

Replace these placeholders with your own local configuration.

### Security

Do not commit:

- Wi-Fi passwords
- Blynk authentication tokens
- API keys
- Personal credentials

to a public repository.

---

## Hardware Configuration

The exact GPIO configuration should match the hardware wiring used in the project.

The public firmware uses placeholder pin definitions where deployment-specific values should be configured.

```cpp
#define DHTPIN YOUR_DHT_PIN
#define SOIL_PIN YOUR_SOIL_SENSOR_PIN
#define TDS_PIN YOUR_TDS_SENSOR_PIN

#define WATER_RELAY_PIN YOUR_WATER_RELAY_PIN
#define FERTILIZER_RELAY_PIN YOUR_FERTILIZER_RELAY_PIN

#define LED_LOW YOUR_LOW_MOISTURE_LED_PIN
#define LED_HIGH YOUR_HIGH_MOISTURE_LED_PIN
```

---

## Firmware Flow

```text
Start
  ↓
Initialize ESP32
  ↓
Initialize Sensors
  ↓
Connect to Wi-Fi / Blynk
  ↓
Read Sensors
  ↓
Calculate Soil Moisture
  ↓
Check Irrigation Condition
  ↓
Control Relay / Pump
  ↓
Update LED Status
  ↓
Send Data to Blynk
  ↓
Repeat
```

---

## Public Code Scope

This directory provides the public firmware implementation for the core Smart Farm automation subsystem.

The repository is primarily intended to demonstrate the embedded engineering work behind:

- Sensor integration
- Calibration
- Decision logic
- Actuator control
- IoT communication
- Hardware/software integration

Sensitive deployment configuration is intentionally excluded.

---

## Current Status

The firmware represents the ESP32-based farm-automation portion of the Smart Farm AI prototype.

The separate ESP32-CAM plant-health monitoring system is documented in:

```text
docs/ai-plant-health.md
```

The overall system architecture is documented in:

```text
docs/architecture.md
```
