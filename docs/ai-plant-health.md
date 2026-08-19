# Smart Farm AI — AI Plant Health Monitoring

## Overview

The Smart Farm AI project includes an experimental plant-health monitoring subsystem built around an **ESP32-CAM**.

The purpose of this subsystem is to capture plant images and explore the use of AI-based image classification to distinguish between:

```text
Healthy
   vs
Diseased
```

The current implementation should be considered an **experimental computer-vision prototype**, not a validated plant-disease diagnosis system.

---

## Objective

The plant-health subsystem was developed to explore how a low-cost camera and an AI model could be used to monitor plant conditions.

The intended workflow is:

```text
Plant
  ↓
ESP32-CAM
  ↓
Image Capture
  ↓
Image Processing
  ↓
AI Model
  ↓
Classification
  ↓
Healthy / Diseased
```

The system was developed as an extension to the sensor-based Smart Farm automation system.

---

## Hardware

The primary hardware used for this subsystem is:

| Component | Purpose | Status |
|---|---|---|
| ESP32-CAM | Plant image capture | Implemented / Tested |
| Camera Module | Captures plant images | Implemented / Tested |
| Physical Cart | Mobile camera platform | Built / Manual |

The current project does not use an ESP8266 controller.

---

## ESP32-CAM

The ESP32-CAM is used as the camera controller and image-capture device.

Its responsibilities include:

- Camera initialization
- Image capture
- Providing captured images to the software-processing workflow
- Supporting the experimental plant-health detection system

### Basic Workflow

```text
ESP32-CAM
    |
    v
Camera Initialization
    |
    v
Capture Image
    |
    v
Image Available
    |
    v
Software Processing
```

---

## Image Capture

The ESP32-CAM was configured to capture images of plant leaves.

The development workflow used a camera capture endpoint so that captured images could be accessed by the software-processing pipeline.

Conceptually:

```text
ESP32-CAM
    |
    v
Capture Endpoint
    |
    v
Plant Image
    |
    v
Python / Flask
```

The quality of the captured image directly affects the reliability of the AI classification.

---

## AI Processing Pipeline

The experimental AI pipeline was developed using Python and Flask around the ESP32-CAM image source.

The overall workflow is:

```text
Plant Leaf
    |
    v
ESP32-CAM
    |
    v
Image Capture
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
Classification
    |
    +------------+
    |            |
    v            v
 Healthy      Diseased
```

---

## Dataset and Model Experimentation

The project included experimentation with plant/leaf image datasets and image-classification models.

Development involved:

- A Kaggle plant/leaf dataset
- Healthy and diseased image classes
- Google Teachable Machine
- Model export
- Python-based processing

The model-related files used during the experimentation included:

```text
metadata
model
weights.bin
```

The exact final model architecture is not sufficiently documented in the available project records and is therefore not claimed here.

---

## Classification Classes

The intended classification structure was:

```text
Input Plant Image
       |
       v
     AI Model
       |
   +---+---+
   |       |
   v       v
Healthy  Diseased
```

The system was intended to provide a classification result based on the captured plant image.

---

## Testing

The AI system was tested using images captured through the ESP32-CAM workflow.

Testing involved:

- ESP32-CAM image capture
- Sending/accessing captured images
- Running the Python/Flask processing workflow
- Passing images through the AI model
- Observing classification results
- Comparing observed predictions with expected classifications

---

## Observed AI Behavior

A significant issue was observed during testing.

The model frequently produced a very strong prediction toward the **Diseased** class.

Observed outputs were approximately:

```text
98–100% Diseased
```

This was observed even when the expected classification was different.

### Important Interpretation

The value:

```text
98–100% Diseased
```

is **not model accuracy**.

It represents the model's observed prediction confidence/output during testing.

Therefore, this project does **not** claim:

```text
98–100% disease-detection accuracy
```

The behavior indicates that the current model/pipeline requires further investigation and validation.

---

## AI Limitations

The current plant-health system has several limitations.

### 1. Prediction Bias

The model showed a strong tendency to classify images as diseased.

### 2. Image Quality

ESP32-CAM image quality can affect the information available to the classifier.

### 3. Dataset / Model Behavior

The training data, model behavior, and class distribution require further investigation.

### 4. Validation

The current experiment does not provide sufficient evidence for a reliable real-world disease-detection accuracy measurement.

### 5. Web Processing

The Python/Flask interface also required debugging during development.

---

## Python / Flask Processing

Python and Flask were used as part of the image-processing workflow.

The general architecture was:

```text
ESP32-CAM
    |
    v
Image Capture
    |
    v
Python
    |
    v
Flask Server
    |
    v
AI Model
    |
    v
Prediction
```

The Flask application provided the software layer between the camera image and the AI-processing workflow.

---

## Model Files

The AI experimentation involved model-related files such as:

```text
metadata
model
weights.bin
```

These files represent the exported/trained model resources used during the experimentation process.

The repository should only contain model files that are appropriate to redistribute and that do not violate the terms of the source dataset or external platform.

---

## Physical Camera Cart

The ESP32-CAM was also mounted on a physical cart to explore mobile plant monitoring.

The current prototype includes:

- Physical cart
- ESP32-CAM
- Camera mounting
- Image-capture software
- AI-processing workflow

The cart was manually moved during the current testing stage.

### Current Workflow

```text
Plant
  ↓
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

The cart is therefore a **manual mobile camera prototype** at the current stage.

---

## Autonomous Movement

Autonomous movement has **not** been implemented in the current version.

It is planned as a future upgrade.

The intended future system is:

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
Autonomous Movement
        |
        v
Automatic Image Capture
        |
        v
Plant Health Monitoring
```

Future development may include crop-row navigation and automatic movement between plants.

---

## Current Status

### Working / Tested

- ESP32-CAM setup
- Camera initialization
- Plant image capture
- Camera software
- Python/Flask processing workflow
- Physical camera cart
- Manual movement of the cart
- Experimental AI classification pipeline

### Experimental / Partially Working

- Healthy/diseased classification
- AI prediction reliability
- Image-processing workflow
- Web interface
- Integration with the broader Smart Farm system

### Planned

- Improved dataset/model
- Better classification reliability
- Improved image quality
- Automated camera movement
- Crop-row navigation
- Automatic image capture during movement
- More complete integration with farm automation

---

## What This Subsystem Demonstrates

The plant-health subsystem demonstrates practical experimentation with:

- ESP32-CAM hardware
- Embedded camera systems
- Image acquisition
- Python
- Flask
- AI image classification
- Dataset usage
- Model deployment experimentation
- Hardware/software integration
- Debugging of an end-to-end computer-vision workflow

The project also demonstrates the importance of testing AI systems rather than assuming that a high confidence score represents high accuracy.

---

## Limitations and Engineering Honesty

This subsystem is an experimental prototype.

It does not currently claim:

- Production-ready plant disease detection
- Scientifically validated disease diagnosis
- 98–100% classification accuracy
- Autonomous plant-monitoring navigation
- Fully autonomous farm operation

The observed classification bias is documented as a limitation and represents an area for future development.

---

## Future Improvements

Future development may focus on:

- Improving image quality
- Collecting better training data
- Balancing healthy and diseased classes
- Improving model training
- Testing with independent validation images
- Measuring actual classification accuracy
- Improving the Flask interface
- Optimizing ESP32-CAM image capture
- Automating cart movement
- Adding crop-row navigation
- Automatically capturing images while moving
- Integrating plant-health results with the main ESP32 farm-automation system

---

## AI Plant Health Architecture Summary

```text
                    PLANT HEALTH SYSTEM
                            |
                            v
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
                 +----------+----------+
                 |                     |
                 v                     v
              Healthy              Diseased
                 |
                 v
        Experimental Result
```

The current implementation provides a working foundation for further development, while autonomous mobility and reliable plant-health classification remain future goals.
