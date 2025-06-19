# 🛡️ Real-Time Health Monitoring System for Soldiers

An IoT-based health surveillance system for soldiers, designed to continuously monitor vital signs and location data in remote environments. Powered by LoRa and integrated with ThingSpeak, this project aims to enhance battlefield safety, provide real-time alerts, and support emergency medical interventions.

---

## 🎯 Objectives

* Monitor vital health parameters (temperature, heart rate, SPO2)
* Track real-time location using GPS
* Use LoRa for long-range, low-power communication
* Provide emergency alerts with a danger switch and voice playback
* Upload data to ThingSpeak for cloud-based monitoring and visualization

---

## 🧰 Hardware Components

* Arduino Nano
* DHT11 Temperature and Humidity Sensor
* MLX90612 Infrared Body Temperature Sensor
* 10K Potentiometer (Heart rate simulation)
* GPS Module (NEO-6M)
* LoRa Module (XL1278-SMT)
* ISD1820 Voice Playback Module
* 16×2 LCD Display with I2C
* ESP8266 WiFi Module
* Emergency Push Button

---

## ☁️ Cloud Platform

**ThingSpeak** is used for data logging, visualization, and remote access.

* Sensor data is uploaded via ESP8266
* Visualized in real-time using graphs
* Alert data helps trigger immediate action

---

## ⚙️ System Architecture

### Transmitter (Wearable Node)

* Collects sensor data (temp, heart rate, SPO2, GPS)
* Sends data via LoRa to receiver
* Emergency alert via button and ISD1820
* Displays local data on LCD

### Receiver (Monitoring Base Station)

* Receives LoRa data
* Parses and displays data on LCD
* Uploads parsed data to ThingSpeak via ESP8266
* Activates buzzer if emergency signal is received

---

## 🔁 Data Flow

1. Sensors → Arduino Nano → LoRa Transmission
2. Receiver (Nano) → Parses and Displays → Uploads to ThingSpeak
3. Voice alert and buzzer triggered on emergency

---

## 📡 Communication

* **LoRa**: Long-range data transmission
* **WiFi (ESP8266)**: Cloud connection to ThingSpeak

---

## 🖥️ Software Requirements

* Arduino IDE (Sensor + LoRa programming)
* ThingSpeak Cloud Account

---

## 📊 Monitored Parameters

* Ambient Temperature
* Body Temperature
* Humidity
* Heart Rate (via potentiometer)
* SPO2
* GPS Latitude & Longitude
* Emergency Switch Status

---

## 💡 Features

* Real-time monitoring from anywhere
* Lightweight, wearable sensor node
* Voice-based alerts via ISD1820
* Low-power long-range LoRaWAN support
* Cloud-based dashboard and trend tracking

---

## 🔮 Future Improvements

* Replace simulated heart rate with real pulse sensor
* Add SpO2 and blood pressure sensors
* Miniaturize the hardware for better wearability
* Use AI for predictive health alerts
* Solar-powered operation for longer missions
* Integration with military command dashboards

---

## 👨‍💻 Author

**Arjun Vasavan**
B.Tech, Department of Electronics Engineering
College of Engineering Chengannur

---

## 📄 License

MIT License
