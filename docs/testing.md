# Smart Farm AI — Testing & Validation

## Testing Overview

Testing was performed incrementally during the development of the Smart Farm AI prototype.

Individual hardware modules were tested before being combined into larger subsystems. The testing process focused on verifying sensor readings, automatic irrigation behavior, IoT communication, ESP32-CAM image capture, AI experimentation, and the physical camera cart.

The project is documented according to the actual prototype state, including working features, experimental features, and known limitations.

---

## Testing Strategy

The general development and testing process was:

```text
Hardware Setup
      ↓
Individual Component Testing
      ↓
Sensor Testing
      ↓
Firmware Configuration
      ↓
Calibration
      ↓
Subsystem Testing
      ↓
IoT Integration
      ↓
ESP32-CAM Testing
      ↓
AI Experimentation
      ↓
Physical Cart Testing
      ↓
Debugging
      ↓
Prototype Validation
```

---

## 1. ESP32 Controller Testing

The ESP32 DevKit was tested as the main controller for the farm-automation subsystem.

### Tested

- ESP32 initialization
- Sensor interfacing
- Analog sensor reading
- Digital sensor communication
- Relay control
- LED control
- Wi-Fi communication
- Blynk communication
- Automatic irrigation logic

### Status

**Working / Tested**

---

## 2. Soil Moisture Sensor Testing

The soil-moisture sensor was tested using different soil moisture conditions.

The raw analog readings were used to establish calibration values.

### Calibration Values

```text
WET_ADC = 1500
DRY_ADC = 3500
```

These values were used as the reference points for converting the sensor reading into an approximate moisture percentage.

### Tested

- Raw ADC readings
- Wet reference condition
- Dry reference condition
- Moisture percentage calculation
- Threshold-based decision making

### Status

**Working / Tested**

---

## 3. Automatic Irrigation Testing

The automatic irrigation subsystem was tested using the soil-moisture reading as the control input.

### Pump ON Test

The configured behavior was:

```text
Moisture < 40%
       ↓
Relay ON
       ↓
Pump ON
```

### Pump OFF Test

The configured behavior was:

```text
Moisture reaches 80%
       ↓
Relay OFF
       ↓
Pump OFF
```

### Tested

- Moisture threshold detection
- Relay activation
- Pump activation
- Continuous moisture monitoring
- Pump stop condition
- Automatic control behavior

### Status

**Working / Tested**

---

## 4. Relay Testing

The relay module was tested as the switching interface between the ESP32 and irrigation pump.

### Test Path

```text
ESP32
  ↓
Relay Signal
  ↓
Relay Module
  ↓
Water Pump
```

The relay was tested both through automatic irrigation logic and manual control.

### Issue Encountered

During development, the relay was observed remaining ON unexpectedly.

Debugging involved checking:

- GPIO configuration
- Relay logic
- Control conditions
- Firmware behavior
- Wiring

### Status

**Tested**

The relay behavior was investigated as part of the iterative debugging process.

---

## 5. Water Pump Testing

The water pump was tested as the irrigation actuator.

### Tested

- Pump activation through relay
- Pump deactivation through relay
- Automatic irrigation response
- Manual relay control

### Status

**Working / Tested**

No quantitative water-saving or agricultural productivity results are claimed.

---

## 6. LED Testing

LEDs were used to provide visual feedback based on the soil-moisture condition.

### Configured Behavior

```text
Moisture < 40%
      ↓
LED1 ON
```

```text
Moisture > 45%
      ↓
LED2 ON
```

### Tested

- GPIO output
- LED activation
- Moisture-based indication

### Status

**Tested**

---

## 7. DHT11 Testing

The DHT11 was tested for environmental monitoring.

### Tested

- Temperature reading
- Humidity reading
- Sensor initialization
- Communication with ESP32

### Status

**Tested / Working**

The DHT11 was the environmental sensor successfully tested during the project.

---



## 9. TDS Sensor Testing

The TDS sensor was explored as part of the experimental fertilizer/nutrient-monitoring concept.

The sensor was considered for measuring dissolved material in a fertilizer/water solution and for experimentation with a soil-water sample.

### Testing Focus

- Sensor reading
- TDS measurement concept
- Fertilizer/water solution monitoring
- Possible use in nutrient-related logic

### Limitation

The TDS sensor was not treated as a complete soil NPK measurement system.

No scientifically validated soil-fertility or NPK results are claimed.

### Status

**Experimental**

---

## 10. Blynk Testing

Blynk was tested as the IoT monitoring and control layer.

### Tested

- Wi-Fi connection
- Blynk connection
- Soil-moisture data transmission
- Relay control
- Manual control
- Dashboard interaction

### Virtual Pins

| Virtual Pin | Function |
|---|---|
| V0 | Soil moisture data |
| V1 | Relay control/status |
| V2 | Manual control switch |

### Issues Encountered

Development included problems involving:

- Blynk template configuration
- Widgets not displaying expected data
- Sensor data visibility
- Relay-control behavior

These issues were investigated through firmware and dashboard configuration changes.

### Status

**Working / Tested with debugging**

---

## 11. ESP32-CAM Testing

The ESP32-CAM was tested separately from the main farm-automation controller.

### Tested

- ESP32-CAM initialization
- Camera configuration
- Image capture
- Camera connectivity
- Image access through the software workflow

### Image Processing Flow

```text
ESP32-CAM
    ↓
Image Capture
    ↓
HTTP / Capture Endpoint
    ↓
Python / Flask
```

### Limitations

Image quality was identified as one of the factors affecting the experimental AI classification system.

### Status

**Working / Tested**

---

## 12. Python / Flask Testing

A Python/Flask application was used as part of the ESP32-CAM image-processing workflow.

### Tested

- Python environment
- Flask server
- ESP32-CAM communication
- Image retrieval
- Image processing workflow
- AI prediction interface

### Status

**Experimental / Tested**

The complete web-processing workflow required debugging during development.

---

## 13. AI Plant Health Testing

The AI subsystem was tested using plant images captured through the ESP32-CAM workflow.

The intended classification was:

```text
Healthy
   vs
Diseased
```

### Tested

- Image input
- AI model loading
- Classification
- Prediction output
- Healthy/diseased result behavior

The development process involved external dataset and model-training resources, including Google Teachable Machine and a Kaggle plant/leaf dataset.

### Status

**Experimental**

---

## 14. AI Prediction Issue

A significant issue was observed during AI testing.

The model frequently produced a strong prediction toward:

```text
Diseased
```

Observed outputs were approximately:

```text
98–100% Diseased
```

This value represents the observed model output and **does not represent classification accuracy**.

The issue indicates that the current AI pipeline requires additional investigation and validation.

### Possible Areas for Further Testing

- Dataset balance
- Training data quality
- Image quality
- Model training
- Validation dataset
- Preprocessing
- Classification thresholds

### Status

**Partially Working / Requires Further Development**

---

## 15. Physical Camera Cart Testing

A physical cart was built as a mobile platform for the ESP32-CAM.

The current prototype includes:

- Physical cart
- ESP32-CAM
- Camera mounting
- Camera software
- Image capture

The cart was manually moved during testing.

### Current Testing Workflow

```text
ESP32-CAM
    ↓
Image Capture
    ↓
AI / Software Processing
    ↓
Physical Cart
    ↓
Manual Movement
```

### Status

**Physical Prototype / Manual Operation**

---

## 16. Autonomous Movement Testing

Autonomous movement has **not** been implemented or validated in the current prototype.

The current cart requires manual movement.

Future development may include:

- Motor control
- Motor driver integration
- Autonomous navigation
- Crop-row movement
- Automatic image capture while moving

### Status

**Not Implemented / Planned**

---

## 17. System Integration Testing

The project contains multiple subsystems that were developed and tested incrementally.

### Farm Automation

```text
Soil Sensor
    ↓
ESP32
    ↓
Decision Logic
    ↓
Relay
    ↓
Water Pump
```

### IoT Monitoring

```text
ESP32
    ↓
Wi-Fi
    ↓
Blynk
    ↓
Monitoring / Manual Control
```

### Plant Monitoring

```text
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

These subsystems were not all validated as one completely autonomous end-to-end agricultural platform.

---

## 18. Debugging & Issues

Several hardware and software issues were encountered during development.

| Issue | Testing / Debugging Area | Status |
|---|---|---|
| DHT22 integration problem | Sensor communication | Problematic |
| Relay remaining ON | GPIO / control logic | Investigated |
| Blynk template issues | IoT configuration | Debugged |
| Blynk widgets not displaying data | Dashboard configuration | Debugged |
| ESP32-CAM connectivity | Camera setup | Tested / Debugged |
| ESP32-CAM image quality | Camera system | Limitation identified |
| AI prediction bias | Model/testing | Requires improvement |
| Flask/web interface issues | Software processing | Requires improvement |

These issues were handled through iterative testing, firmware changes, configuration changes, wiring verification, and subsystem isolation.

---

## 19. Verified Features

The following features were tested during development:

- ESP32 farm controller
- Soil-moisture sensing
- Soil calibration
- Automatic irrigation logic
- Relay control
- Water pump control
- LED indication
- DHT11 temperature/humidity monitoring
- Blynk monitoring
- Blynk manual control
- ESP32-CAM image capture
- Python/Flask image-processing workflow
- Physical camera cart
- Manual camera-cart movement

---

## 20. Experimental Features

The following features remain experimental or partially implemented:

- TDS-based nutrient monitoring
- AI plant-health classification
- ESP32-CAM web interface
- Complete integration between farm automation and AI monitoring

---

## 21. Planned Features

Future validation and development may include:

- Improved AI model
- Better image quality
- Independent AI validation dataset
- Quantitative classification accuracy measurement
- Autonomous cart movement
- Crop-row navigation
- Automatic image capture while moving
- Integration between plant-health results and farm automation
- Longer-duration testing
- Field-oriented testing

---

## 22. Validation Approach

The project follows an iterative engineering validation process:

```text
Design
  ↓
Hardware Assembly
  ↓
Individual Component Testing
  ↓
Sensor Calibration
  ↓
Subsystem Testing
  ↓
Firmware Debugging
  ↓
IoT Integration
  ↓
Camera Integration
  ↓
AI Experimentation
  ↓
Physical Prototype Testing
  ↓
Identify Limitations
  ↓
Future Improvement
```

This approach was used to identify problems early and verify individual subsystems before attempting broader integration.

---

## 23. Current Validation Status

### Strongest Verified Subsystem

The ESP32-based automatic irrigation system is the most developed subsystem.

```text
Soil Moisture
     ↓
ESP32
     ↓
Decision Logic
     ↓
Relay
     ↓
Pump
```

This workflow was physically tested.

### Experimental Subsystem

The ESP32-CAM plant-health system demonstrates the camera and software pipeline but requires further AI validation.

### Mobile Platform

The physical camera cart was built and tested through manual movement.

Autonomous movement remains a future development.

---

## 24. Testing Limitations

The current project does not claim:

- Production-ready agricultural automation
- Autonomous farming
- Autonomous rover navigation
- Scientifically validated plant-disease detection
- 98–100% AI accuracy
- Complete soil NPK analysis using TDS
- Quantified water savings
- Increased crop yield
- Long-term field performance

The documented results represent prototype-level testing.

---

## 25. Final Testing Summary

Smart Farm AI was developed through practical hardware and software experimentation.

The testing process verified the core ESP32 irrigation subsystem and established working foundations for:

- Sensor monitoring
- Automatic irrigation
- Relay and pump control
- IoT monitoring
- ESP32-CAM image capture
- Python/Flask processing
- Experimental AI classification
- Physical mobile camera testing

The remaining limitations are explicitly documented so that the repository represents the actual engineering state of the prototype rather than an exaggerated final product.
