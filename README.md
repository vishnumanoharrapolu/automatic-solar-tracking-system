# 🌞 Automated Solar Tracking System

An **IoT-powered dual-axis solar tracker** built with Arduino/ESP32, LDR sensors, and servo motors to maximize solar panel efficiency by continuously aligning with the sun’s position.

---

## 🔧 Features
- **Dual-axis tracking** using 4 LDR sensors (East–West & North–South)
- **Servo control** for azimuth and elevation adjustment
- **Safety mechanisms**:
  - Rain sensor → auto-park panels
  - PIR sensor → pause motion when activity detected
- **Environmental monitoring** with DHT11 (temperature & humidity)
- **Cloud logging** via ThingSpeak (ESP32 version) for real-time data visualization
- **Arduino Uno/Nano version** for pure tracking without Wi-Fi
  
---

## ⚙️ Hardware Requirements
- Arduino Uno/Nano **or** ESP32 DevKit
- 2 × Servo motors (SG90/MG996R)
- 4 × LDR sensors + 10kΩ resistors
- Rain sensor module
- PIR motion sensor
- DHT11/DHT22 sensor (optional)
- External 5V power supply for servos (≥2A)

---

## 🚀 Getting Started

### 1. Clone the repository
```bash
git clone https://github.com/your-username/automated-solar-tracker.git
