# Smart Farm AI — Automatic Irrigation System

## Overview

Automatic irrigation is the most developed and verified subsystem of the Smart Farm AI prototype.

The system uses an analog soil-moisture sensor connected to the ESP32 DevKit. The ESP32 reads the sensor value, converts it into an approximate soil-moisture percentage using calibrated reference values, and controls a water pump through a relay.

The basic control process is:

```text
Soil Moisture Sensor
        ↓
     ESP32 ADC
        ↓
Calibration
        ↓
Moisture Percentage
        ↓
Decision Logic
        ↓
Relay
        ↓
Water Pump
        ↓
Irrigation
```

---

## Objective

The irrigation subsystem was developed to demonstrate automatic watering based on the moisture condition of the soil.

The system is designed to:

- Detect dry soil
- Automatically start the water pump
- Continue monitoring soil moisture
- Stop the pump after reaching the target moisture level
- Provide visual LED indication
- Send soil-moisture information to Blynk
- Allow manual relay control through the IoT interface

---

## Hardware Used

| Component | Purpose |
|---|---|
| ESP32 DevKit | Main controller |
| Soil Moisture Sensor | Measures soil moisture |
| Relay Module | Switches the water pump |
| Water Pump | Provides irrigation |
| LEDs | Moisture/status indication |
| Blynk | Remote monitoring and manual control |

---

## Soil Moisture Measurement

The soil-moisture sensor provides an analog voltage that is read by the ESP32 ADC.

The raw ADC value depends on the moisture condition of the soil.

The system uses two reference values for calibration:

```text
WET_ADC = 1500
DRY_ADC = 3500
```

These values represent the calibrated wet and dry reference points used during development.

---

## Moisture Calculation

The calibrated ADC value is converted into an approximate moisture percentage.

Conceptually:

```text
Raw ADC Reading
      ↓
Compare with Wet/Dry Calibration
      ↓
Convert to Moisture %
      ↓
Apply Irrigation Threshold
```

The moisture percentage is an approximate control value based on the calibration performed for the prototype.

It should not be interpreted as a laboratory-grade measurement of soil water content.

---

## Irrigation Control Logic

The automatic irrigation logic uses separate ON and OFF thresholds.

### Pump ON Condition

When:

```text
Soil Moisture < 40%
```

the ESP32 activates the relay and turns the water pump ON.

### Pump OFF Condition

The system continues monitoring the soil moisture while the pump is running.

When:

```text
Soil Moisture ≥ 80%
```

the ESP32 turns the relay OFF and stops the water pump.

---

## Control Flow

```text
Start
  ↓
Read Soil Moisture
  ↓
Convert ADC Reading to Moisture %
  ↓
Is Moisture < 40%?
  |
  +------ YES ------+
  |                 |
  v                 v
Relay ON          Continue
  |              Monitoring
  v
Pump ON
  |
  v
Continue Reading
  |
  v
Is Moisture ≥ 80%?
  |
  +------ NO ------+
  |                |
  |                v
  |          Continue Pumping
  |
  +----- YES -----> Relay OFF
                         |
                         v
                      Pump OFF
                         |
                         v
                    Continue Monitoring
```

---

## Threshold Hysteresis

The system uses different thresholds for starting and stopping irrigation:

```text
Pump ON  → Below 40%
Pump OFF → At or above 80%
```

Using separate thresholds prevents the pump from rapidly switching ON and OFF around a single boundary value.

The wide separation between the thresholds was selected for the prototype's control behavior.

---

## Relay Control

The ESP32 does not directly power the water pump.

Instead, the control path is:

```text
ESP32
  ↓
Relay Control Signal
  ↓
Relay Module
  ↓
Water Pump
```

The relay acts as the switching interface between the ESP32 control logic and the pump.

---

## LED Indication

LEDs were used to provide a simple visual indication of soil-moisture conditions.

The configured behavior was:

```text
Moisture < 40%
      ↓
LED1 ON
```

and:

```text
Moisture > 45%
      ↓
LED2 ON
```

The LEDs were used as visual feedback during operation and testing.

---

## Blynk Integration

The irrigation system was connected to Blynk through the ESP32's Wi-Fi connection.

Blynk was used for:

- Soil-moisture monitoring
- Relay control
- Manual control
- Remote interaction with the irrigation system

### Virtual Pin Mapping

| Virtual Pin | Function |
|---|---|
| V0 | Soil moisture data |
| V1 | Relay control/status |
| V2 | Manual control switch |

The Blynk interface allows the user to observe the soil-moisture condition and interact with the relay control.

---

## Automatic and Manual Control

The system supports two types of interaction:

### Automatic Mode

The ESP32 determines pump operation from the soil-moisture value.

```text
Dry Soil
   ↓
Automatic Decision
   ↓
Relay ON
   ↓
Pump ON
```

The pump stops after the configured target moisture level is reached.

### Manual Control

A Blynk control was also used to provide manual relay interaction.

```text
Blynk
  ↓
Manual Control
  ↓
ESP32
  ↓
Relay
  ↓
Pump
```

Manual control is useful during testing and provides an alternative to automatic threshold-based operation.

---

## Monitoring Flow

The complete irrigation data flow is:

```text
Soil
  ↓
Soil Moisture Sensor
  ↓
ESP32 ADC
  ↓
Calibration
  ↓
Moisture Percentage
  ↓
+----------------------+
|                      |
v                      v
Irrigation Logic       Blynk
|                      |
v                      v
Relay              Monitoring
|
v
Water Pump
|
v
Irrigation
```

---

## Calibration

The soil sensor was calibrated using wet and dry reference points.

### Configured Values

```text
WET_ADC = 1500
DRY_ADC = 3500
```

The calibration process provides the reference range used by the firmware to estimate the moisture percentage.

Because soil composition, sensor placement, and environmental conditions can affect the readings, these calibration values are specific to the prototype setup.

---

## Testing

The irrigation subsystem was developed and tested incrementally.

The testing process included:

- Reading raw soil-moisture ADC values
- Establishing wet and dry calibration points
- Converting readings to moisture percentage
- Testing the dry-soil threshold
- Testing relay activation
- Testing water-pump operation
- Monitoring moisture while the pump was active
- Testing the pump stop condition
- Testing LED indication
- Testing Blynk monitoring
- Testing manual relay control

---

## Debugging

Several issues were encountered during development of the irrigation system.

### Relay Behavior

A relay remaining ON unexpectedly was investigated during development.

Debugging involved checking:

- Relay logic
- GPIO configuration
- Control conditions
- Firmware behavior
- Wiring

### Blynk Configuration

Blynk configuration also required debugging.

Issues included:

- Template configuration
- Widget visibility
- Sensor data not appearing as expected
- Relay control behavior

These issues were addressed through iterative firmware and configuration testing.

---

## Current Status

### Verified

- Soil-moisture sensing
- ADC calibration
- Moisture percentage calculation
- Automatic irrigation logic
- Relay control
- Water pump operation
- Moisture-based LED indication
- Blynk soil-moisture monitoring
- Blynk manual control

### Limitations

- Moisture percentage is an approximate calibrated value.
- Calibration is specific to the prototype setup.
- The system has not been validated as a production agricultural irrigation controller.
- No quantified water-saving or crop-yield improvement results are claimed.

---

## Irrigation Architecture Summary

```text
                 SOIL
                  |
                  v
        Soil Moisture Sensor
                  |
                  v
             ESP32 ADC
                  |
                  v
          Calibration Logic
                  |
                  v
          Moisture Percentage
                  |
          +-------+-------+
          |               |
          v               v
       Blynk          Decision Logic
          |               |
          |          Moisture < 40%
          |               |
          |               v
          |            Relay ON
          |               |
          |               v
          |           Pump ON
          |               |
          |               v
          |        Monitor Moisture
          |               |
          |       Moisture ≥ 80%
          |               |
          |               v
          |            Relay OFF
          |               |
          |               v
          |            Pump OFF
          |
          v
    Remote Monitoring
```

---

## Future Improvements

Future development may focus on:

- More accurate soil-moisture calibration
- Improved sensor reliability
- Better waterproofing and physical sensor protection
- More robust pump control
- Improved power management
- Long-duration testing
- Field-oriented testing
- Integration with the plant-monitoring subsystem
- More advanced irrigation decision-making

---

## Summary

The automatic irrigation subsystem demonstrates a complete embedded control loop:

```text
Sense
  ↓
Measure
  ↓
Calibrate
  ↓
Decide
  ↓
Actuate
  ↓
Monitor
  ↓
Repeat
```

The ESP32 reads the soil condition, applies calibrated thresholds, controls the irrigation pump through a relay, provides visual feedback, and communicates selected data and controls through Blynk.

This subsystem represents the most developed and verified automation component of the Smart Farm AI prototype.
