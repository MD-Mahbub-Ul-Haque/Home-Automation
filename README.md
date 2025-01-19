# Home-Automation
This is a small Home Automation Project using ESP and Blynk 


# Home Automation and Gas/Fire Alarm System with ESP32

## Purpose
This project aims to create a comprehensive home automation system using the ESP32 microcontroller, Blynk IoT platform, and various sensors/actuators. It allows users to control appliances, monitor room conditions, and receive real-time alerts for gas leaks or fire hazards.

---

## Components List
1. **ESP32 Development Board** - Main microcontroller
2. **4-Channel Low-Level Trigger Relay Module** - Controls home appliances
3. **MQ2 Gas/Smoke Sensor** - Detects gas and smoke levels
4. **DHT11 Temperature and Humidity Sensor** - Monitors room temperature and humidity
5. **Buzzer** - Sounds an alarm for gas/smoke detection
6. **Power Supply** - For powering the ESP32 and sensors
7. **Connecting Wires** - For circuit connections
8. **Breadboard or PCB** - For prototyping

---

## Pinout Connections
| Component       | ESP32 Pin | Description             |
|-----------------|-----------|-------------------------|
| Relay 1         | GPIO 25   | Appliance control       |
| Relay 2         | GPIO 26   | Appliance control       |
| Relay 3         | GPIO 27   | Appliance control       |
| Relay 4         | GPIO 14   | Appliance control       |
| MQ2 Gas Sensor  | GPIO 34   | Analog input for gas    |
| Buzzer          | GPIO 12   | Alarm sound             |
| DHT11 Sensor    | GPIO 4    | Digital input for DHT11 |

---

## System Setup Instructions

1. **Circuit Assembly**:
   - Connect the relays to GPIO 25, 26, 27, and 14 on the ESP32.
   - Connect the MQ2 gas sensor's `AO` pin to GPIO 34.
   - Connect the buzzer to GPIO 12.
   - Connect the DHT11 sensor's data pin to GPIO 4.
   - Ensure all components share a common ground.

2. **Software Setup**:
   - Install the latest version of the Arduino IDE.
   - Install the following libraries:
     - `Blynk` (for ESP32)
     - `DHT` (for temperature and humidity)
   - Enter your Blynk `AUTH_TOKEN`, Wi-Fi `SSID`, and `PASSWORD` in the code.

3. **Blynk App Configuration**:
   - Create a Blynk project with widgets:
     - **Button widgets** for controlling each relay on Virtual Pins V1 to V4.
     - **Label widgets** for displaying temperature and humidity on V5 and V6.
     - **Sound/Alarm widget** linked to V7 for gas/smoke alerts.

4. **Upload the Code**:
   - Connect the ESP32 to your computer and upload the provided code.

5. **Operation**:
   - Use the Blynk app to control appliances.
   - Monitor temperature and humidity in real-time.
   - Receive instant gas/smoke alerts with a buzzer alarm and notifications.

---

## Code Summary
- **Relay Control**: Controlled via Blynk buttons.
- **Gas Detection**: Monitors MQ2 sensor values; triggers alarm and notifications when levels exceed a threshold.
- **Room Monitoring**: Uses DHT11 to report temperature and humidity.

---

This system combines IoT-based automation with safety features, offering a practical solution for smart home management.
