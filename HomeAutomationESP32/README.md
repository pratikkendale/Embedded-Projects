# HomeAutomationESP32
Smart Home using ESP32 on IOT
# Home Automation System Using ESP32 over IOT

## Introduction
This project is a comprehensive home automation system implemented using an ESP32 microcontroller. The system integrates various sensors, actuators, and a web interface to provide an interactive, smart home experience. With functionalities like temperature-based fan control, rain detection, door automation, and light management, it is designed to make everyday tasks more convenient and efficient.

---

## Features
1. **Temperature and Humidity Monitoring**
   - DHT11 sensor is used to monitor temperature and humidity.
   - Automatic fan control based on temperature thresholds.

2. **IR Sensor for Door Automation**
   - Detects motion at the door and triggers servo motor to open/close the door.
   - Alerts via buzzer and an LED indicator.

3. **LDR Sensor for Light Control**
   - Automatically turns lights ON/OFF based on ambient light levels.

4. **Rain Sensor**
   - Detects rain and provides alerts using a buzzer.

5. **Web Interface**
   - Control fan, lights, and door through a user-friendly web interface.
   - Displays real-time temperature, humidity, and system status.

6. **Home Security Mode**
   - Secures the home by closing the door and activating the buzzer as a deterrent.

---

## Components Used
### Hardware:
- **ESP32**: Main microcontroller
- **DHT11**: Temperature and humidity sensor
- **IR Sensor**: Motion detection
- **LDR**: Light detection
- **Rain Sensor**: Rain detection
- **Servo Motor**: Door automation
- **12V Fan**: Temperature-based control
- **LiquidCrystal_PCF8574**: I2C LCD for display
- **Buzzer**: Alerts
- **LEDs**: Visual indicators
- **Power Supply**: 5V or 3.3V for ESP32

### Software:
- Arduino IDE
- ESP32 Servo Library
- LiquidCrystal_PCF8574 Library

---

## Circuit Connections
- **IR Sensor**: Signal pin connected to GPIO 23.
- **Servo Motor**: Signal pin connected to GPIO 19.
- **DHT11 Sensor**: Signal pin connected to GPIO 18.
- **Fan Control**: Motor driver pins connected to GPIO 4, 2, and 5.
- **LDR Sensor**: Signal pin connected to GPIO 36.
- **Rain Sensor**: Signal pin connected to GPIO 35.
- **Buzzer**: Signal pin connected to GPIO 13.
- **LCD Display**: Connected via I2C to ESP32.

---

## Code Explanation
### 1. **WiFi Setup**
Connects the ESP32 to a WiFi network using SSID and password.

### 2. **Sensor Handling**
- **Temperature and Humidity**:
  - Reads data from the DHT11 sensor.
  - Automatically controls the fan based on a temperature threshold (29°C).

- **IR Sensor**:
  - Detects motion at the door.
  - Triggers servo motor to open/close the door and activates buzzer/LED.

- **LDR Sensor**:
  - Detects light levels to control the lights.

- **Rain Sensor**:
  - Detects rain and alerts via buzzer.

### 3. **Web Server**
- Hosted on ESP32 to handle HTTP requests.
- Controls fan, lights, and door remotely.
- Displays real-time temperature, humidity, and status messages.

### 4. **HTML Interface**
- Simple web interface with buttons for manual control.
- Automatically updates system status every 3 seconds.

### 5. **Security Mode**
- Activates all security features to safeguard the home.

---

## Code
```cpp
#include <WiFi.h>
#include <ESP32Servo.h>
#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>
#include <DHT.h>

// Full code available in the repository.
```

---

## How to Use
1. **Setup**
   - Connect all components as per the circuit diagram.
   - Upload the code to the ESP32 using Arduino IDE.

2. **WiFi Configuration**
   - Update the SSID and password in the code with your WiFi credentials.

3. **Run**
   - Power on the ESP32.
   - Access the web interface via the IP address displayed on the LCD.

4. **Control**
   - Use the web interface to control the fan, lights, and door.
   - Monitor real-time temperature, humidity, and status updates.

---

## Applications
- Home automation
- Smart security systems
- Weather monitoring and alert systems

---

## Repository
The complete project code, circuit diagram, and documentation are available on [GitHub](https://github.com/pratikkendale/HomeAutomationESP32/blob/main/Source%20Code).

---

## Conclusion
This home automation system combines convenience, security, and efficiency. By leveraging the ESP32 and various sensors, it provides a robust platform for controlling and monitoring your home environment remotely.

