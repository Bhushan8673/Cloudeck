# ClouDeck 🚀  

![Arduino Library](https://img.shields.io/badge/Arduino-Library-blue)
![License: MIT](https://img.shields.io/badge/License-MIT-green)
![GitHub stars](https://img.shields.io/github/stars/Bhushan8673/Cloudeck?style=social)

A Modular IoT SDK for Cloud-Connected Devices

Cloudeck is a hardware-agnostic, modular IoT SDK designed for Arduino-based IoT devices with built-in Wi-Fi.
It simplifies Wi-Fi and MQTT communication and enables developers to build scalable, cloud-connected IoT solutions using clean and reusable code.

Cloudeck is built with a production-ready mindset and can be reused across multiple projects, from basic MQTT communication to real-world applications such as remote motor and IoT car control.

Officially available via the Arduino Library Manager.

---

## Key Features

- Simple Wi-Fi connection management
- Built-in MQTT publish and subscribe support
- Modular architecture with optional features
- Optional IoT car and motor control module
- Compatible  MQTT brokers
- Supports WebSocket-based dashboards and web interfaces
- Non-blocking, production-safe loop handling

---

## Supported Hardware and IoT Devices

Cloudeck is a hardware-agnostic, modular IoT SDK designed for Arduino-based IoT devices with built-in Wi-Fi.

The library is not limited to ESP devices.  
Cloudeck can be used on any Wi-Fi enabled IoT device that:
- supports the Arduino framework
- provides IP-based networking
- supports MQTT communication

This flexible design allows Cloudeck to scale across multiple IoT devices and evolve with future IoT requirements.

---

### Officially Tested and Supported Devices

The following IoT devices are fully tested and officially supported:

- ESP8266
- ESP32 (including ESP32-S2, ESP32-S3, ESP32-C3)

---

### Broad IoT Device Compatibility

Cloudeck is compatible with a wide range of Arduino-based Wi-Fi IoT devices, including:

- Arduino boards with integrated Wi-Fi
- ESP-based and non-ESP Wi-Fi microcontrollers
- Custom and commercial IoT devices with built-in Wi-Fi modules
- Any Arduino-compatible IoT device supporting Wi-Fi and MQTT

---

### Designed for Growth

Cloudeck is built with a future-ready modular architecture, enabling expansion to additional networking technologies such as:

- Ethernet-based IoT devices
- Cellular IoT devices (GSM, LTE, NB-IoT)
- Cloud-connected industrial IoT devices and gateways

This approach ensures Cloudeck remains adaptable for both current and next-generation IoT systems.

---

## Installation

Cloudeck is officially available through the Arduino Library Manager.

### Install via Arduino Library Manager

1. Open Arduino IDE  
2. Go to Sketch → Include Library → Manage Libraries  
3. Search for Cloudeck  
4. Click Install  

---

### Manual Installation (ZIP)

1. Download this repository as a ZIP file  
2. Open Arduino IDE  
3. Go to Sketch → Include Library → Add .ZIP Library  
4. Select the downloaded ZIP file  

---

### Include in Your Sketch

After installing the library, include Cloudeck in your Arduino sketch:

```cpp
#include <Cloudeck.h>
